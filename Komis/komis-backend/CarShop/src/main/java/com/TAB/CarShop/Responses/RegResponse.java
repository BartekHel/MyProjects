package com.TAB.CarShop.Responses;

import com.TAB.CarShop.Entities.Role;

public class RegResponse {
    public boolean success;
    public long id;
    public String login;
    public Role role;
    public String message;

    public RegResponse(boolean success, long id, String login, Role role, String message) {
        this.success = success;
        this.id = id;
        this.login = login;
        this.role = role;
        this.message = message;
    }
}
