package com.TAB.CarShop.Requests;

import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
public class CreateOrderByTokenRequest {
    private double price;
    private String client_token;
    private Long dealer_id;
    private Long showroom_id;
    private Long vehicle_id;

    public CreateOrderByTokenRequest() {
    }

    public CreateOrderByTokenRequest(double price, String client_token, Long dealer_id, Long showroom_id, Long vehicle_id) {
        this.price = price;
        this.client_token = client_token;
        this.dealer_id = dealer_id;
        this.showroom_id = showroom_id;
        this.vehicle_id = vehicle_id;
    }
}