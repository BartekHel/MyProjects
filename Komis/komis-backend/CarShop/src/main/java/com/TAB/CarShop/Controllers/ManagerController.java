package com.TAB.CarShop.Controllers;

import com.TAB.CarShop.Entities.Manager;
import com.TAB.CarShop.Entities.Order;
import com.TAB.CarShop.Entities.Role;
import com.TAB.CarShop.Entities.User;
import com.TAB.CarShop.Repositories.ManagerRepository;
import com.TAB.CarShop.Repositories.OrderRepository;
import com.TAB.CarShop.Repositories.ShowroomRepository;
import com.TAB.CarShop.Repositories.UserRepository;
import com.TAB.CarShop.Responses.EmployeeWithEarnings;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDate;
import java.time.Month;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/manager")
public class ManagerController {
	private final ManagerRepository managerRepository;
	private final UserRepository userRepository;
	private final ShowroomRepository showroomRepository;
	private final OrderRepository orderRepository;

	public ManagerController(ManagerRepository managerRepository, UserRepository userRepository, ShowroomRepository showroomRepository, OrderRepository orderRepository) {
		this.managerRepository = managerRepository;
		this.userRepository = userRepository;
		this.showroomRepository = showroomRepository;
		this.orderRepository = orderRepository;
	}

	@GetMapping("/{id}/employees")
	List<User> getEmployees(@PathVariable long id) {
		Manager manager = managerRepository.findById(id).orElse(null);
		if (manager == null)
			return null;

		return userRepository.findAll().stream().filter(user ->
				(user.getRole() == Role.DEALER && user.getDealer().getManager() == manager)
						|| (user.getRole() == Role.REPAIRER && user.getRepairer().getManager() == manager)
		).toList();
	}

	@GetMapping("/{id}/employees/money")
	List<EmployeeWithEarnings> getMoneyMade(@PathVariable long id,
												   @RequestParam(value = "year", defaultValue = "-1") int y,
												   @RequestParam(value = "month", defaultValue = "-1") int m) {
		Manager manager = managerRepository.findById(id).orElse(null);
		if (manager == null)
			return null;

		int year;
		Month month;
		if ((y < 0) || (m < 0) || (m >= 12)) { //idk można zmienić na string
			LocalDate now = LocalDate.now();
			year = now.getYear();
			month = now.getMonth();
		} else {
			year = y;
			month = Month.of(m);
		}

		Map<User, Double> result = orderRepository.findAll().stream()
				.filter(order -> order.getDelivery_date().getMonth() == month
						&& order.getDelivery_date().getYear() == year)
				.collect(Collectors.groupingBy(order -> order.getDealer().getUser(),
						Collectors.summingDouble(Order::getPrice)));

		return result.entrySet().stream().map(entry->new EmployeeWithEarnings(
				entry.getKey().getName()+" "+entry.getKey().getSurname(),
				entry.getKey().getEmail(),
				entry.getValue().toString()
		)).toList();

	}

	@PutMapping("/{id}/setshow")
	void setShowroom(@PathVariable long id, @RequestBody long showroomId) {
		Manager manager = managerRepository.findById(id).orElse(null);
		if (manager == null)
			return;
		manager.setShowroom(showroomRepository.findById(showroomId).orElse(null));
		managerRepository.save(manager);
	}
}
