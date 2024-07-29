package com.TAB.CarShop.Controllers;

import com.TAB.CarShop.Entities.Client;
import com.TAB.CarShop.Entities.Order;
import com.TAB.CarShop.Entities.Vehicle;
import com.TAB.CarShop.Repositories.ClientRepository;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
import java.util.Random;
import java.util.Set;

@RestController
@RequestMapping("/client")
public class ClientController {
	private final ClientRepository clientRepository;

	public ClientController(ClientRepository clientRepository) {
		this.clientRepository = clientRepository;
	}

	@GetMapping
	List<Client> getAllClients() {
		return clientRepository.findAll();
	}

	@GetMapping("/{id}")
	Client getRepairerById(@PathVariable Long id) {
		return clientRepository.findById(id).orElse(null);
	}

	@GetMapping("/{id}/listvehicles")
	List<Vehicle> getClientVehicles(@PathVariable Long id) {
		Client client = clientRepository.findById(id).orElse(null);
		if (client == null) {
			return null;
		}
		return client.getOrders().stream().map(Order::getVehicle).toList();
	}

	@GetMapping("/{id}/listorders")
	Set<Order> getClientOrders(@PathVariable Long id) {
		Client client = clientRepository.findById(id).orElse(null);
		if (client == null) {
			return null;
		}
		return client.getOrders();
	}

	@GetMapping("/{id}/generatetoken")
	String generateToken(@PathVariable Long id) {
		Client client = clientRepository.findById(id).orElse(null);
		if (client == null) {
			return null;
		}
		String characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
		Random random = new Random();
		int length = 8;
		StringBuilder sb = new StringBuilder(length);
		for (int i = 0; i < length; i++) {
			sb.append(characters.charAt(random.nextInt(characters.length())));
		}
		String token = sb.toString();
		client.setToken(token);
		clientRepository.save(client);
		return token;
	}
}
