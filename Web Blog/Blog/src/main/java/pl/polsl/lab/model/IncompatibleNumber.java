package pl.polsl.lab.model;

/**
 * My exception class to handle exceptions
 * @author Bartosz Heliński
 * @version 2.0
 */

public class IncompatibleNumber extends Exception {
    
    /**
     * Default constructor 
     */
    
    public IncompatibleNumber() {
        super("Posts number error exception! ");
    }
    
    /**
     * Constructor with one arguemnt
     * @param message exception message for display
     */

    public IncompatibleNumber(String message) {
        super(message);
    }
}