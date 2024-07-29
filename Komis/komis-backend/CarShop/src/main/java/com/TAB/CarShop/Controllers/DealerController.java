package com.TAB.CarShop.Controllers;

import com.TAB.CarShop.Entities.*;
import com.TAB.CarShop.Repositories.DealerRepository;
import com.TAB.CarShop.Repositories.ManagerRepository;
import org.springframework.data.util.Pair;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/dealer")
public class DealerController {
	private final DealerRepository dealerRepository;
	private final ManagerRepository managerRepository;

	public DealerController(DealerRepository dealerRepository, ManagerRepository managerRepository) {
		this.dealerRepository = dealerRepository;
		this.managerRepository = managerRepository;
	}

	@GetMapping
	List<Dealer> getAllDealers() {
		return dealerRepository.findAll();
	}

	@GetMapping("/{id}")
	Dealer getDealerById(@PathVariable Long id) {
		return dealerRepository.findById(id).orElse(null);
	}

	/*
	@GetMapping("/{id}/listorders")
	Set<Order> listDealerOrders(@PathVariable Long id) {
		Dealer dealer = dealerRepository.findById(id).orElse(null);
		if (dealer == null) return null;
		return dealer.getOrders();
	}*/

	@GetMapping("/{id}/listorders")
	List<Pair<Order, Vehicle>> listDealerOrdersTest(@PathVariable Long id) {
		Dealer dealer = dealerRepository.findById(id).orElse(null);
		if (dealer == null) return null;
		return dealer.getOrders().stream().map(order -> Pair.of(order, order.getVehicle())).toList();
	}

	@GetMapping("/{id}/getshowroom")
	Showroom getDealerShowroom(@PathVariable Long id) {
		Dealer dealer = dealerRepository.findById(id).orElse(null);
		if (dealer == null) return null;
		return dealer.getManager().getShowroom();
	}

	@GetMapping("/{id}/getmanager")
	Manager getDealerManager(@PathVariable Long id) {
		Dealer dealer = dealerRepository.findById(id).orElse(null);
		if (dealer == null) return null;
		return dealer.getManager();
	}

	@PutMapping("/{id}/setmanager/{managerid}")
	Dealer setManager(@PathVariable Long id, @PathVariable Long managerid) {
		Dealer dealer = dealerRepository.findById(id).orElse(null);
		Manager manager = managerRepository.findById(managerid).orElse(null);
		if (dealer == null || manager == null) {
			return null;
		}
		dealer.setManager(manager);
		return dealerRepository.save(dealer);
	}
}
