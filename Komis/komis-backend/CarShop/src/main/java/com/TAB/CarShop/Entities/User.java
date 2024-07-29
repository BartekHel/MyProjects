package com.TAB.CarShop.Entities;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
@Entity
@Table(name = "users")
public class User {

	@Id
	@Column(name = "user_id", nullable = false)
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long user_id; //Or Integer instead of int

	@Column(name = "login", nullable = false)
	private String login;

	@Column(name = "password", nullable = false)
	private String password;

	@Column(name = "email", nullable = false)
	private String email;

	@Column(name = "role")
	@Enumerated(EnumType.STRING)
	private Role role;

	@Column(name = "name", nullable = false)
	private String name;

	@Column(name = "surname", nullable = false)
	private String surname;

	@JsonIgnore
	@OneToOne(mappedBy = "user")
	private Client client;

	@JsonIgnore
	@OneToOne(mappedBy = "user")
	private Dealer dealer;

	@JsonIgnore
	@OneToOne(mappedBy = "user")
	private Manager manager;

	@JsonIgnore
	@OneToOne(mappedBy = "user")
	private Repairer repairer;

	public User() {
	}

	public User(String login, String password, String email, Role role, String name, String surname) {
		this.login = login;
		this.password = password;
		this.email = email;
		this.role = role;
		this.name = name;
		this.surname = surname;
	}

}
