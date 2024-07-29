package com.TAB.CarShop.Controllers;

import com.TAB.CarShop.Entities.Repairer;
import com.TAB.CarShop.Entities.Service;
import com.TAB.CarShop.Repositories.ManagerRepository;
import com.TAB.CarShop.Repositories.RepairerRepository;
import com.TAB.CarShop.Repositories.ServiceRepository;
import com.TAB.CarShop.Requests.SetServicePriceRequest;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDate;
import java.util.Comparator;
import java.util.List;

@RestController
@RequestMapping("/repairer")
public class RepairerController {

	private final RepairerRepository repairerRepository;
	private final ManagerRepository managerRepository;
	private final ServiceRepository serviceRepository;

	public RepairerController(RepairerRepository repairerRepository, ManagerRepository managerRepository, ServiceRepository serviceRepository) {
		this.repairerRepository = repairerRepository;
		this.managerRepository = managerRepository;
		this.serviceRepository = serviceRepository;
	}

	@GetMapping
	List<Repairer> getAllRepairers() {
		return repairerRepository.findAll();
	}

	@GetMapping("/{id}")
	Repairer getRepairerById(@PathVariable Long id) {
		return repairerRepository.findById(id).orElse(null);
	}

	@GetMapping("/{id}/listservices")
	List<Service> getRepairerServices(@PathVariable Long id) {
		Repairer repairer = repairerRepository.findById(id).orElse(null);
		if (repairer == null) {
			return null;
		}

		Comparator<Service> comp = Comparator.comparing(Service::getService_id);

		return repairer.getServices().stream().sorted(comp).toList();
	}

	@GetMapping("/{id}/activeservices")
	int getRepairerActiveServices(@PathVariable Long id) {
		Repairer repairer = repairerRepository.findById(id).orElse(null);
		if (repairer == null) {
			return -1;
		}
		int activeServices = 0;
		LocalDate currentDate = LocalDate.now();
		for (Service service : repairer.getServices()) {
			if (currentDate.isAfter(service.getAdmission_date()) && (service.getExecution_date() == null || currentDate.isBefore(service.getExecution_date()))) {
				activeServices++;
			}
		}
		return activeServices;
	}

	@GetMapping("/leastoccupied")
	Repairer getLeastOccupiedRepairer() {
		List<Repairer> repairers = repairerRepository.findAll();
		if (repairers.isEmpty()) {
			return null;
		}
		int leastOccupied = this.getRepairerActiveServices(repairers.get(0).getRepairer_id());
		int index = 0;
		for (int i = 1; i < repairers.size(); i++) {
			int numberOfActiveServices = this.getRepairerActiveServices(repairers.get(i).getRepairer_id());
			if (numberOfActiveServices < leastOccupied) {
				leastOccupied = numberOfActiveServices;
				index = i;
			}
		}
		return repairers.get(index);
	}

	@PutMapping("/{id}/setmanager")
	void setManager(@PathVariable long id, @RequestBody long managerId) {
		Repairer repairer = repairerRepository.findById(id).orElse(null);
		if (repairer == null)
			return;
		repairer.setManager(managerRepository.findById(managerId).orElse(null));
		repairerRepository.save(repairer);
	}

	@PutMapping("/{id}/setserviceprice")
	Service setServicePrice(@PathVariable long id, @RequestBody SetServicePriceRequest request) {
		Repairer repairer = repairerRepository.findById(id).orElse(null);
		if (repairer == null) return null;
		for (Service service : repairer.getServices()) {
			if (service.getService_id() == request.getServiceId()) {
				service.setPrice(request.getPrice());
				return serviceRepository.saveAndFlush(service);
			}
		}
		return null;
	}
}
