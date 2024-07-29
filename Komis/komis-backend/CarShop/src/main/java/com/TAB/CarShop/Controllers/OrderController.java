package com.TAB.CarShop.Controllers;

import com.TAB.CarShop.Entities.*;
import com.TAB.CarShop.Repositories.*;
import com.TAB.CarShop.Requests.CreateOrderByTokenRequest;
import com.TAB.CarShop.Requests.CreateOrderRequest;
import com.TAB.CarShop.Responses.CreateOrderResponse;
import com.github.javafaker.Faker;
import lombok.AllArgsConstructor;
import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.*;

import java.time.DayOfWeek;
import java.time.LocalDate;
import java.util.List;

@RestController
@RequestMapping("/orders")
@RequiredArgsConstructor
public class OrderController {
	private final OrderRepository orderRepository;
	private final ClientRepository clientRepository;
	private final ShowroomRepository showroomRepository;
	private final VehicleRepository vehicleRepository;
	private final DealerRepository dealerRepository;
	private final UserRepository userRepository;
	private final ManagerRepository managerRepository;



	LocalDate calculateDeliveryDate(LocalDate submission_date, Showroom showroom, Vehicle vehicle) {
		if (showroom.getShowroom_id() == vehicle.getShowroom().getShowroom_id()) {
			return submission_date;
		}
		LocalDate deliveryDate = submission_date.plusDays(14);
		if (deliveryDate.getDayOfWeek() == DayOfWeek.SATURDAY) {
			deliveryDate = deliveryDate.plusDays(2);
		} else if (deliveryDate.getDayOfWeek() == DayOfWeek.SUNDAY) {
			deliveryDate = deliveryDate.plusDays(1);
		}
		return deliveryDate;
	}

	@GetMapping
	List<Order> getAllOrders() {
		return orderRepository.findAll();
	}

	@GetMapping("/{id}")
	Order getOrderById(@PathVariable Long id) {
		return orderRepository.findById(id).orElse(null);
	}


	@PostMapping("/generate/{number}")
	String generateOrder(@PathVariable int number){
		Faker faker=new Faker();
		generateNewDealers(30);
		List<Vehicle> vehicles = vehicleRepository.findAll();
		List<Client> clients = clientRepository.findAll();
		List<Dealer> dealers = dealerRepository.findAll();
		List<Showroom> showrooms = showroomRepository.findAll();

		for (int i = 0; i < number; i++) {
			Vehicle vehicle = vehicles.get(faker.number().numberBetween(0, vehicles.size()));
			var order=new CreateOrderRequest(
					vehicle.getPrice(),
					clients.get(faker.number().numberBetween(0,clients.size())).getClient_id(),
					dealers.get(faker.number().numberBetween(0,dealers.size())).getDealer_id(),
					showrooms.get(faker.number().numberBetween(0,showrooms.size())).getShowroom_id(),
					vehicle.getVehicle_id()
			);
			createOrder(order);
		}
		return "success";
	}

	private void generateNewDealers(int number) {
		Faker faker=new Faker();
		List<Manager> managers = managerRepository.findAll();
		for (int j = 0; j < number; j++) {
			User user=new User();
			user.setLogin(faker.name().username());
			user.setPassword(faker.internet().password());
			user.setName(faker.name().firstName());
			user.setSurname(faker.name().lastName());
			user.setEmail(faker.internet().emailAddress());
			user.setRole(Role.DEALER);
			userRepository.saveAndFlush(user);

			Dealer dealer=new Dealer();
			dealer.setUser(user);
			dealer.setManager(managers.get(faker.number().numberBetween(0,managers.size())));

			dealerRepository.saveAndFlush(dealer);
		}
	}

	@PostMapping("/createorder")
	CreateOrderResponse createOrder(@RequestBody CreateOrderRequest createOrderRequest) {
		try {
			Client client = clientRepository.findById(createOrderRequest.getClient_id()).orElse(null);
			Showroom showroom = showroomRepository.findById(createOrderRequest.getShowroom_id()).orElse(null);
			Vehicle vehicle = vehicleRepository.findById(createOrderRequest.getVehicle_id()).orElse(null);
			Dealer dealer = dealerRepository.findById(createOrderRequest.getDealer_id()).orElse(null);
			if (client == null || showroom == null || vehicle == null || dealer == null) {
				return new CreateOrderResponse(false, 0, "Foreign key entity not found");
			}
			if (vehicle.isWas_sold()) {
				return new CreateOrderResponse(false, 0, "This vehicle is already sold");
			}
			LocalDate deliveryDate = calculateDeliveryDate(LocalDate.now(), showroom, vehicle);
			Order newOrder = new Order(
					LocalDate.now(),
					deliveryDate,
					createOrderRequest.getPrice(),
					client,
					showroom,
					vehicle,
					dealer
			);
			newOrder = orderRepository.saveAndFlush(newOrder);
			vehicle.setNext_inspection_date(deliveryDate.plusYears(1));
			vehicle.setWas_sold(true);
			vehicleRepository.saveAndFlush(vehicle);
			return new CreateOrderResponse(true, newOrder.getOrder_id(), "order created successfully");
		} catch (Exception e) {
			return new CreateOrderResponse(false, 0, e.getMessage());
		}
	}

	@PostMapping("/createorderbytoken")
	CreateOrderResponse createOrderByToken(@RequestBody CreateOrderByTokenRequest createOrderByTokenRequest) {
		try {
			Client client = clientRepository.findByToken(createOrderByTokenRequest.getClient_token()).orElse(null);
			Showroom showroom = showroomRepository.findById(createOrderByTokenRequest.getShowroom_id()).orElse(null);
			Vehicle vehicle = vehicleRepository.findById(createOrderByTokenRequest.getVehicle_id()).orElse(null);
			Dealer dealer = dealerRepository.findById(createOrderByTokenRequest.getDealer_id()).orElse(null);
			if (client == null || showroom == null || vehicle == null || dealer == null) {
				return new CreateOrderResponse(false, 0, "Foreign key entity not found");
			}
			if (vehicle.isWas_sold()) {
				return new CreateOrderResponse(false, 0, "This vehicle is already sold");
			}
			LocalDate deliveryDate = calculateDeliveryDate(LocalDate.now(), showroom, vehicle);
			Order newOrder = new Order(
					LocalDate.now(),
					deliveryDate,
					createOrderByTokenRequest.getPrice(),
					client,
					showroom,
					vehicle,
					dealer
			);
			newOrder = orderRepository.saveAndFlush(newOrder);
			vehicle.setNext_inspection_date(deliveryDate.plusYears(1));
			vehicle.setWas_sold(true);
			vehicleRepository.saveAndFlush(vehicle);
			return new CreateOrderResponse(true, newOrder.getOrder_id(), "order created successfully");
		} catch (Exception e) {
			return new CreateOrderResponse(false, 0, e.getMessage());
		}
	}

	@PutMapping("/{id}")
	Order replaceOrder(@PathVariable Long id, @RequestBody Order newOrder) {
		return orderRepository.findById(id)
				.map(order -> {
					order.setDelivery_date(newOrder.getDelivery_date());
					order.setPrice(newOrder.getPrice());
					order.setSubmission_date(newOrder.getSubmission_date());
					order.setClient(newOrder.getClient());
					order.setShowroom(newOrder.getShowroom());
					order.setDealer(newOrder.getDealer());
					order.setVehicle(newOrder.getVehicle());
					return orderRepository.save(order);
				})
				.orElseGet(() -> {
					newOrder.setOrder_id(id);
					return orderRepository.save(newOrder);
				});
	}

	@PutMapping("/{id}/setdelivery")
	Order setDeliveryDate(@PathVariable Long id, @RequestBody LocalDate deliveryDate) {
		Order order = orderRepository.findById(id).orElse(null);
		if (order == null) {
			return new Order();
		}

		order.setDelivery_date(deliveryDate);
		return order;
	}

	@DeleteMapping("/{id}")
	void deleteOrderById(@PathVariable Long id) {
		orderRepository.deleteById(id);
	}
}
