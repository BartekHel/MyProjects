package com.TAB.CarShop.Entities;

import com.fasterxml.jackson.annotation.JsonBackReference;
import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

import java.time.LocalDate;

@Setter
@Getter
@Entity
@Table(name = "vehicles")
public class Vehicle {

	@Id
	@Column(name = "vehicle_id", nullable = false)
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long vehicle_id;

	@Column(name = "brand", nullable = false)
	private String brand;

	@Column(name = "model", nullable = false)
	private String model;

	@Column(name = "modifications")
	private String modifications;

	@Column(name = "next_inspection_date")
	private LocalDate next_inspection_date;

	@Column(name = "price", nullable = false)
	private double price;

	@Column(name = "was_sold")
	private boolean was_sold = false;

    @Column(name = "picture_file_name")
	private String picture_file_name;

	@JsonIgnore
	@OneToOne(mappedBy = "vehicle")
	private Order order;

	@ManyToOne
	@JsonBackReference
	@JoinColumn(name = "showroom_id")
	private Showroom showroom;

	public Vehicle() {
	}

	public Vehicle(String brand, String model, String modifications, double price, Showroom showroom) {
		this.brand = brand;
		this.model = model;
		this.modifications = modifications;
		this.price = price;
		this.showroom = showroom;
		this.was_sold = false;
		this.picture_file_name = brand + model + ".png";
	}

	public Vehicle(String brand, String model, String modifications, double price, String picture_file_name, Showroom showroom) {
		this.brand = brand;
		this.model = model;
		this.modifications = modifications;
		this.price = price;
		this.picture_file_name = picture_file_name;
		this.showroom = showroom;
	}
}
