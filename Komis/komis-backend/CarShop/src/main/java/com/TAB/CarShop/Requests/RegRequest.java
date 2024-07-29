package com.TAB.CarShop.Requests;

import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
public class RegRequest {
	private String login;
	private String password;
	private String email;
	private String role;
	private String name;
	private String surname;

	public RegRequest() {
	}

	public RegRequest(String login, String password, String email, String name, String surname) {
		this.login = login;
		this.password = password;
		this.email = email;
		this.name = name;
		this.surname = surname;
	}

}
