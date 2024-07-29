package com.TAB.CarShop;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public record CarShopUtils() {

    public static List<String> brands = List.of("Toyota", "BMW", "Honda", "Ford");

    public static Map<Integer, List<String>> carModels = Map.of(
            0, List.of("Corolla", "Camry", "RAV4", "Prius", "Highlander"),
            1, List.of("E60", "X5", "M3", "X3", "5Series"),
            2, List.of("Civic", "Accord", "CR-V", "Fit", "Pilot"),
            3, List.of("Focus", "Mustang", "Escape", "Explorer", "F-150"));


}
