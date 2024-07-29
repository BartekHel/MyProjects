package pl.kurs.entity;


import javax.persistence.*;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;
import javax.print.Doc;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlRootElement;

@Entity
@XmlRootElement
public class Doctor implements Serializable {
    private static final long serialVersionUID = 1L;
    int doctor_id;
    String name;
    String surname;
    String specialization;
    Set<Appointment> appointments = new HashSet<Appointment>();

    public Doctor() {
    }

    public Doctor(String name, String surname, String specialization) {
        this.name = name;
        this.surname = surname;
        this.specialization = specialization;
    }

    public Doctor(String name, String surname, Set<Appointment> appointments) {
        this.name = name;
        this.surname = surname;
        this.specialization = "";
        this.appointments = appointments;
    }

    @Id
    @GeneratedValue
    @XmlAttribute
    public int getDoctor_id() {
        return doctor_id;
    }

    public void setDoctor_id(int doctor_id) {
        this.doctor_id = doctor_id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public String getSpecialization() {
        return specialization;
    }

    public void setSpecialization(String specialization) {
        this.specialization = specialization;
    }

    @OneToMany(fetch = FetchType.EAGER, mappedBy = "doctor")
    public Set<Appointment> getAppointments() {
        return appointments;
    }
    public void setAppointments(Set<Appointment> appointments) {
        this.appointments = appointments;
    }
}
