package com.TAB.CarShop.Entities;

import com.fasterxml.jackson.annotation.JsonBackReference;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

import java.time.LocalDate;

@Getter
@Setter
@Entity
@Table(name = "services")
public class Service {
	@Id
	@Column(name = "service_id", nullable = false)
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long service_id;

	@ManyToOne
	@JsonBackReference
	@JoinColumn(name = "vehicle_id")
	private Vehicle vehicle_id;

	@ManyToOne
	@JsonBackReference
	@JoinColumn(name = "repairer_id")
	private Repairer repairer;

	@Column(name = "description")
	private String description;

	@Column(name = "admission_date", nullable = false)
	private LocalDate admission_date;

	@Column(name = "execution_date")
	private LocalDate execution_date;

	@Column(name = "price")
	private double price;

	public Service(Vehicle vehicle_id, Repairer repairer, String description, LocalDate admission_date) {
		this.vehicle_id = vehicle_id;
		this.repairer = repairer;
		this.description = description;
		this.admission_date = admission_date;
	}

	public Service() {

	}
}
