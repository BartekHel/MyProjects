package com.TAB.CarShop.Responses;

import com.TAB.CarShop.Entities.Role;

public class AuthResponse {
    public boolean success;
    public long id;
    public String login;
    public Role role;

    public AuthResponse(boolean success, long id, String login, Role role) {
        this.success = success;
        this.id = id;
        this.login = login;
        this.role = role;
    }
}
