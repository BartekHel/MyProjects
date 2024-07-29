package com.TAB.CarShop.Entities;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

import java.util.Set;

@Getter
@Setter
@Entity
@Table(name = "dealers")

public class Dealer {
	@Id
	@Column(name = "dealer_id", nullable = false)
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long dealer_id;

	@OneToOne
	@JsonIgnore
	@JoinColumn(name = "user_id", referencedColumnName = "user_id")
	private User user;

	@ManyToOne
	@JsonIgnore
	@JoinColumn(name = "manager_id")
	private Manager manager;

	@OneToMany(fetch = FetchType.LAZY, mappedBy = "dealer")
	@JsonIgnore
	private Set<Order> orders;

}
