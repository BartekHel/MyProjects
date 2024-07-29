package com.TAB.CarShop.Entities;

import com.fasterxml.jackson.annotation.JsonBackReference;
import com.fasterxml.jackson.annotation.JsonManagedReference;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

import java.util.Set;

@Getter
@Setter
@Entity
@Table(name = "repairers")
public class Repairer {
	@Id
	@Column(name = "repairer_id", nullable = false)
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long repairer_id;

	@OneToOne
	@JoinColumn(name = "user_id", referencedColumnName = "user_id")
	private User user;

	@ManyToOne
	@JsonBackReference
	@JoinColumn(name = "manager_id")
	private Manager manager;

	@OneToMany(mappedBy = "repairer")
	@JsonManagedReference
	private Set<Service> services;
}
