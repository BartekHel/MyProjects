package com.TAB.CarShop.Responses;

public class CreateOrderResponse {
    public boolean success;
    public long order_id;
    public String message;

    public CreateOrderResponse(boolean success, long order_id, String message) {
        this.success = success;
        this.order_id = order_id;
        this.message = message;
    }
}
