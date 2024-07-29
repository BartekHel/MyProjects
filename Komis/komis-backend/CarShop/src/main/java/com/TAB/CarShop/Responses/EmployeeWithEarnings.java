package com.TAB.CarShop.Responses;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;

@AllArgsConstructor
@Getter
@Setter
public class EmployeeWithEarnings {
    String name;
    String email;
    String earnings;
}
