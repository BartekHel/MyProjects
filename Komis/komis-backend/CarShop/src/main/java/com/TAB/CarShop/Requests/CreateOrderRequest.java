package com.TAB.CarShop.Requests;

import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
public class CreateOrderRequest {
	private double price;
	private Long client_id;
	private Long dealer_id;
	private Long showroom_id;
	private Long vehicle_id;

	public CreateOrderRequest() {
	}

	public CreateOrderRequest(double price, Long client_id, Long dealer_id, Long showroom_id, Long vehicle_id) {
		this.price = price;
		this.client_id = client_id;
		this.dealer_id = dealer_id;
		this.showroom_id = showroom_id;
		this.vehicle_id = vehicle_id;
	}
}
