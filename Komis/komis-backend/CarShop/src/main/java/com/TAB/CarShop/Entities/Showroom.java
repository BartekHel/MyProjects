package com.TAB.CarShop.Entities;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonManagedReference;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

import java.util.Set;

@Getter
@Setter
@Entity
@Table(name = "showrooms")
public class Showroom {

	@Id
	@Column(name = "showroom_id", nullable = false)
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long showroom_id;

	@Column(name = "address", nullable = false)
	private String address;

	@OneToMany(mappedBy = "showroom")
	@JsonIgnore
	private Set<Order> orders;

	@OneToMany(mappedBy = "showroom")
	@JsonIgnore
	private Set<Vehicle> vehicles;

	@OneToOne(mappedBy = "showroom")
	@JsonIgnore
	private Manager manager;
}
