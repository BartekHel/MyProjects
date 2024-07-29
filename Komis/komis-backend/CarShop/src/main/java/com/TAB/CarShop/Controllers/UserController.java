package com.TAB.CarShop.Controllers;

import com.TAB.CarShop.Entities.*;
import com.TAB.CarShop.Repositories.*;
import com.TAB.CarShop.Requests.AuthRequest;
import com.TAB.CarShop.Requests.RegRequest;
import com.TAB.CarShop.Responses.AuthResponse;
import com.TAB.CarShop.Responses.RegResponse;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/users")
public class UserController {
	private final UserRepository userRepository;
	private final ClientRepository clientRepository;
	private final DealerRepository dealerRepository;
	private final ManagerRepository managerRepository;
	private final RepairerRepository repairerRepository;

	UserController(UserRepository userRepository, ClientRepository clientRepository, DealerRepository dealerRepository, ManagerRepository managerRepository, RepairerRepository repairerRepository) {
		this.userRepository = userRepository;
		this.clientRepository = clientRepository;
		this.dealerRepository = dealerRepository;
		this.managerRepository = managerRepository;
		this.repairerRepository = repairerRepository;
	}

	@GetMapping
	List<User> getAllUsers() {
		return userRepository.findAll();
	}

	@GetMapping("/{login}")
	User getUserById(@PathVariable String login) {
		List<User> user = userRepository.findByLogin(login);
		if (user.isEmpty()) {
			return null;
		}
		return user.get(0);
	}

	@PostMapping("/reg")
	RegResponse registerUser(@RequestBody RegRequest regRequest) {
		if (!userRepository.findByLogin(regRequest.getLogin()).isEmpty()) {
			return new RegResponse(false, 0, null, null, "Username already exists");
		}
		if (!userRepository.findByEmail(regRequest.getEmail()).isEmpty()) {
			return new RegResponse(false, 0, null, null, "Email already exists");
		}
		try {
			Role role = Role.valueOf(regRequest.getRole().toUpperCase());
			User newUser = new User(regRequest.getLogin(), regRequest.getPassword(), regRequest.getEmail(), role, regRequest.getName(), regRequest.getSurname());
			newUser = userRepository.saveAndFlush(newUser);
			long id;
			switch (role) {
				case CLIENT:
					Client newClient = new Client();
					newClient.setUser(newUser);
					clientRepository.saveAndFlush(newClient);
					id = newClient.getClient_id();
					break;
				case MANAGER:
					Manager newManager = new Manager();
					newManager.setUser(newUser);
					managerRepository.saveAndFlush(newManager);
					id = newManager.getManager_id();
					break;
				case REPAIRER:
					Repairer newRepairer = new Repairer();
					newRepairer.setUser(newUser);
					repairerRepository.saveAndFlush(newRepairer);
					id = newRepairer.getRepairer_id();
					break;
				case DEALER:
					Dealer newDealer = new Dealer();
					newDealer.setUser(newUser);
					dealerRepository.saveAndFlush(newDealer);
					id = newDealer.getDealer_id();
					break;
				default:
					return new RegResponse(false, 0, null, null, "Invalid role");
			}


			return new RegResponse(true, id, newUser.getLogin(), newUser.getRole(), "Registration successful");
		} catch (Exception e) {
			return new RegResponse(false, 0, null, null, e.getMessage());
		}
	}

	@PostMapping("/login")
	AuthResponse loginUser(@RequestBody AuthRequest authRequest) {
		List<User> user = userRepository.findByLogin(authRequest.getLogin());
		if (user.isEmpty()) {
			return new AuthResponse(false, 0, null, null);
		}
		if (user.get(0).getPassword().equals(authRequest.getPassword())) {
			long id = switch (user.get(0).getRole()) {
				case CLIENT -> user.get(0).getClient().getClient_id();
				case MANAGER -> user.get(0).getManager().getManager_id();
				case REPAIRER -> user.get(0).getRepairer().getRepairer_id();
				case DEALER -> user.get(0).getDealer().getDealer_id();
				default -> 0;
			};
			return new AuthResponse(true, id, user.get(0).getLogin(), user.get(0).getRole());
		} else {
			return new AuthResponse(false, 0, null, null);
		}
	}

	@PutMapping("/chngrole/{login}")
	long changeRole(@PathVariable String login, @RequestBody Role role) {
		List<User> user = userRepository.findByLogin(login);
		if (user.isEmpty()) {
			return 0;
		}
		user.get(0).setRole(role);
		long id;
		switch (role) {
			case CLIENT:
				Client newClient = new Client();
				newClient.setUser(user.get(0));
				clientRepository.saveAndFlush(newClient);
				id = newClient.getClient_id();
				break;
			case MANAGER:
				Manager newManager = new Manager();
				newManager.setUser(user.get(0));
				managerRepository.saveAndFlush(newManager);
				id = newManager.getManager_id();
				break;
			case REPAIRER:
				Repairer newRepairer = new Repairer();
				newRepairer.setUser(user.get(0));
				repairerRepository.saveAndFlush(newRepairer);
				id = newRepairer.getRepairer_id();
				break;
			case DEALER:
				Dealer newDealer = new Dealer();
				newDealer.setUser(user.get(0));
				dealerRepository.saveAndFlush(newDealer);
				id = newDealer.getDealer_id();
				break;
			default:
				System.out.println("Invalid role");
				return 0;
		}
		return id;
	}

	@PutMapping("/{id}")
	User replaceUser(@PathVariable Long id, @RequestBody User newUser) {
		return userRepository.findById(id)
				.map(user -> {
					user.setLogin(newUser.getLogin());
					user.setPassword(newUser.getPassword());
					user.setEmail(newUser.getEmail());
					user.setName(newUser.getName());
					user.setSurname(newUser.getSurname());
					return userRepository.save(user);
				})
				.orElseGet(() -> {
					newUser.setUser_id(id);
					return userRepository.save(newUser);
				});
	}

	@DeleteMapping("/{id}")
	void deleteUser(@PathVariable Long id) {
		userRepository.deleteById(id);
	}
}
