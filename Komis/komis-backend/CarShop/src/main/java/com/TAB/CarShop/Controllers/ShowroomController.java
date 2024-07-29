package com.TAB.CarShop.Controllers;

import com.TAB.CarShop.Entities.Manager;
import com.TAB.CarShop.Entities.Order;
import com.TAB.CarShop.Entities.Showroom;
import com.TAB.CarShop.Entities.Vehicle;
import com.TAB.CarShop.Repositories.ManagerRepository;
import com.TAB.CarShop.Repositories.ShowroomRepository;
import com.TAB.CarShop.Requests.ShowroomRequest;
import com.TAB.CarShop.Responses.ShowroomListResponse;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

@RestController
@RequestMapping("/showrooms")
public class ShowroomController {
	private final ShowroomRepository showroomRepository;
	private final ManagerRepository managerRepository;

	public ShowroomController(ShowroomRepository showroomRepository, ManagerRepository managerRepository) {
		this.showroomRepository = showroomRepository;
		this.managerRepository = managerRepository;
	}

	@GetMapping("/{id}/profits")
	double getProfits(@PathVariable long id) {
		Showroom showroom = showroomRepository.findById(id).orElse(null);
		if (showroom == null) return -1;
//		LocalDate lastMonth = LocalDate.now().minusMonths(1);
		double profitLastMonth = 0;
		for (Order order : showroom.getOrders()) {
//			if (lastMonth.getMonth() == order.getSubmission_date().getMonth() && lastMonth.getYear() == order.getSubmission_date().getYear()) {
				profitLastMonth += order.getPrice();
//			}
		}
		return profitLastMonth;
	}

	@GetMapping
	List<ShowroomListResponse> getAllShowrooms() {
		List<Showroom> showroomList = showroomRepository.findAll();
		List<ShowroomListResponse> showroomListResponse = new ArrayList<>();
		for (Showroom showroom : showroomList) {
			double profitLastMonth = this.getProfits(showroom.getShowroom_id());
			showroomListResponse.add(new ShowroomListResponse(
					showroom.getShowroom_id(),
					showroom.getAddress(),
					profitLastMonth
			));
		}
		return showroomListResponse;
	}

	@GetMapping("/{id}")
	Showroom getShowroomById(@PathVariable Long id) {
		return showroomRepository.findById(id).orElse(null);
	}

	@PostMapping
	Showroom addShowroom(@RequestBody ShowroomRequest showroomRequest) {
		Showroom showroom = new Showroom();
		showroom.setAddress(showroomRequest.getAddress());
		if (showroomRequest.getManagerId() > 0) {
			Manager manager = managerRepository.findById(showroomRequest.getManagerId()).orElse(null);
			if (manager != null) {
				showroom.setManager(manager);
			}
		}
		return showroomRepository.saveAndFlush(showroom);
	}

	@GetMapping("/{id}/listorders")
	Set<Order> getShowroomOrders(@PathVariable Long id) {
		Showroom showroom = showroomRepository.findById(id).orElse(null);
		if (showroom == null) {
			return null;
		}
		return showroom.getOrders();
	}

	@GetMapping("/{id}/listvehicles")
	Set<Vehicle> getShowroomVehicles(@PathVariable Long id) {
		Showroom showroom = showroomRepository.findById(id).orElse(null);
		if (showroom == null) return null;
		return showroom.getVehicles();
	}

	@GetMapping("/{id}/getmanager")
	Manager getShowroomManager(@PathVariable Long id) {
		Showroom showroom = showroomRepository.findById(id).orElse(null);
		if (showroom == null) return null;
		return showroom.getManager();
	}
}
