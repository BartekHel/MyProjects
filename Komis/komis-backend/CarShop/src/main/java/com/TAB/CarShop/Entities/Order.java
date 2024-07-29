package com.TAB.CarShop.Entities;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;

import java.time.LocalDate;

@Getter
@Setter
@Entity
@AllArgsConstructor
@Table(name = "orders")
public class Order {

	@Id
	@Column(name = "order_id")
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long order_id;

	@Column(name = "submission_date", nullable = false)
	private LocalDate submission_date;

	@Column(name = "delivery_date")
	private LocalDate delivery_date;

	@Column(name = "price", nullable = false)
	private double price;

	@JsonIgnore
	@ManyToOne
	@JoinColumn(name = "client_id")
	private Client client;

	@JsonIgnore
	@ManyToOne
	@JoinColumn(name = "showroom_id")
	private Showroom showroom;

	@JsonIgnore
	@OneToOne
	@JoinColumn(name = "vehicle_id", referencedColumnName = "vehicle_id")
	private Vehicle vehicle;

	@JsonIgnore
	@ManyToOne
	@JoinColumn(name = "dealer_id")
	private Dealer dealer;

	public Order() {
	}

	public Order(LocalDate submission_date, LocalDate delivery_date, double price) {
		this.submission_date = submission_date;
		this.delivery_date = delivery_date;
		this.price = price;
	}

	public Order(LocalDate submission_date, LocalDate delivery_date, double price, Client client, Showroom showroom, Vehicle vehicle, Dealer dealer) {
		this.submission_date = submission_date;
		this.delivery_date = delivery_date;
		this.price = price;
		this.client = client;
		this.showroom = showroom;
		this.vehicle = vehicle;
		this.dealer = dealer;
	}
}
