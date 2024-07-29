package com.TAB.CarShop.Requests;

import lombok.*;

@Setter
@Getter
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class VehicleRequest {
	private String brand;
	private String model;
	private String modifications;
	private double price;
	private long showroomId;
}
