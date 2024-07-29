package com.TAB.CarShop.Entities;

import com.fasterxml.jackson.annotation.JsonManagedReference;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

import java.time.LocalDate;
import java.util.Set;

@Getter
@Setter
@Entity
@Table(name = "clients")
public class Client {

	@Id
	@Column(name = "client_id", nullable = false)
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long client_id;

	@OneToOne
	@JoinColumn(name = "user_id", referencedColumnName = "user_id")
	private User user;

	@OneToMany(fetch = FetchType.LAZY, mappedBy = "client")
	@JsonManagedReference
	private Set<Order> orders;

	@Column(name = "token")
	private String token;
}
