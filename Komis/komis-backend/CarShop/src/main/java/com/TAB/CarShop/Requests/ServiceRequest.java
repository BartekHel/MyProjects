package com.TAB.CarShop.Requests;

import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
public class ServiceRequest {
	private Long vehicleId;
	private Long repairerId;
	private String description;

	ServiceRequest(Long vehicleId, Long repairerId, String description) {
		this.vehicleId = vehicleId;
		this.repairerId = repairerId;
		this.description = description;
	}

}
