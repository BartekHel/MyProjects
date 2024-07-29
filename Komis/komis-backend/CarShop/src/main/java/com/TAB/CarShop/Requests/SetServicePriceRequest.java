package com.TAB.CarShop.Requests;

import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
public class SetServicePriceRequest {
	private long serviceId;
	private double price;
}
