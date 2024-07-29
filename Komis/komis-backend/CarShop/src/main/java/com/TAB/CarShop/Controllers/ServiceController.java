package com.TAB.CarShop.Controllers;

import com.TAB.CarShop.Entities.Repairer;
import com.TAB.CarShop.Entities.Service;
import com.TAB.CarShop.Entities.Vehicle;
import com.TAB.CarShop.Repositories.RepairerRepository;
import com.TAB.CarShop.Repositories.ServiceRepository;
import com.TAB.CarShop.Repositories.VehicleRepository;
import com.TAB.CarShop.Requests.ServiceRequest;
import org.springframework.web.bind.annotation.*;

import java.time.DayOfWeek;
import java.time.LocalDate;
import java.util.List;

@RestController
@RequestMapping("/services")
public class ServiceController {
	private final ServiceRepository serviceRepository;
	private final VehicleRepository vehicleRepository;
	private final RepairerRepository repairerRepository;

	ServiceController(ServiceRepository serviceRepository, VehicleRepository vehicleRepository, RepairerRepository repairerRepository) {
		this.serviceRepository = serviceRepository;
		this.vehicleRepository = vehicleRepository;
		this.repairerRepository = repairerRepository;
	}

	@GetMapping
	List<Service> getAllServices() {
		return serviceRepository.findAll();
	}

	@GetMapping("/{id}")
	Service getServiceById(@PathVariable Long id) {
		return serviceRepository.findById(id).orElse(null);
	}

	@PostMapping
	Boolean addService(@RequestBody ServiceRequest serviceRequest) {
		try {
			Vehicle vehicle = vehicleRepository.findById(serviceRequest.getVehicleId()).orElse(null);
			Repairer repairer = repairerRepository.findById(serviceRequest.getRepairerId()).orElse(null);
			if (vehicle == null || repairer == null) {
				return false;
			}
			LocalDate admissionDate = LocalDate.now();
			if (admissionDate.getDayOfWeek() == DayOfWeek.SATURDAY) {
				admissionDate = admissionDate.plusDays(2);
			} else if (admissionDate.getDayOfWeek() == DayOfWeek.SUNDAY) {
				admissionDate = admissionDate.plusDays(1);
			}
			Service newService = new Service(vehicle, repairer, serviceRequest.getDescription(), admissionDate);
			serviceRepository.saveAndFlush(newService);
			return true;
		} catch (Exception e) {
			return false;
		}
	}

	@PostMapping("/{id}/setdate")
	void setExecutionDate(@PathVariable Long id, @RequestBody LocalDate executionDate) {
		Service service = serviceRepository.findById(id).orElse(null);
		if (service == null) {
			return;
		}
		service.setExecution_date(executionDate);
		serviceRepository.saveAndFlush(service);
	}

	@PostMapping("/{id}/setprice")
	void setPrice(@PathVariable Long id, @RequestBody double price) {
		Service service = serviceRepository.findById(id).orElse(null);
		if (service == null) {
			return;
		}
		service.setPrice(price);
		serviceRepository.saveAndFlush(service);
	}

	@PutMapping("/{id}")
	Service replaceService(@PathVariable Long id, @RequestBody Service newService) {
		return serviceRepository.findById(id)
				.map(service -> {
					service.setVehicle_id(newService.getVehicle_id());
					service.setRepairer(newService.getRepairer());
					service.setDescription(newService.getDescription());
					service.setExecution_date(newService.getExecution_date());
					service.setPrice(newService.getPrice());
					return serviceRepository.save(service);
				})
				.orElseGet(() -> {
					newService.setService_id(id);
					return serviceRepository.save(newService);
				});
	}

	@DeleteMapping("/{id}")
	void deleteService(@PathVariable Long id) {
		serviceRepository.deleteById(id);
	}
}
