package com.TAB.CarShop.Responses;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class ShowroomListResponse {
    private long showroom_id;
    private String address;
    private double profitLastMonth;

    public ShowroomListResponse(long showroom_id, String address, double profitLastMonth) {
        this.showroom_id = showroom_id;
        this.address = address;
        this.profitLastMonth = profitLastMonth;
    }
}
