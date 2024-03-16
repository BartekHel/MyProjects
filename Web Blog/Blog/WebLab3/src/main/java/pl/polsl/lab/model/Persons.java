package pl.polsl.lab.model;

import java.util.ArrayList;
import java.util.List;

public class Persons {
    
    private final List<Person> data = new ArrayList<>();

    public Persons() {        
        data.add(new Person("Jacob", "Smith", "jacob.smith@example.com"));
        data.add(new Person("Isabella", "Johnson", "isabella.johnson@example.com"));
        data.add(new Person("Ethan", "Williams", "ethan.williams@example.com"));
        data.add(new Person("Emma", "Jones", "emma.jones@example.com"));
        data.add(new Person("Michael", "Brown", "michael.brown@example.com"));
    }

    public List<Person> getData() {
        return data;
    }
    
    public void add(Person person){
        data.add(person);
    }
    
}
