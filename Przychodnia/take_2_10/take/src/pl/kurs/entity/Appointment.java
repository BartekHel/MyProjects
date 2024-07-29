package pl.kurs.entity;

import javax.persistence.*;
import javax.xml.bind.annotation.XmlRootElement;

import com.sun.xml.internal.txw2.annotation.XmlAttribute;

import java.io.Serializable;
import java.util.Date;

@Entity
@XmlRootElement
public class Appointment implements Serializable {
    private static final long serialVersionUID = 1L;
    int appointment_id;
    Date date;
    int room_number;
    String prescription;
    Doctor doctor;
    Patient patient;
    Disease disease;

    public Appointment() {
    }

    public Appointment(String date, int room_number, String prescription) {
        String year = date.substring(0, 4);
        String month = date.substring(5, 7);
        String day = date.substring(8, 10);
        String hour = date.substring(11, 13);
        String min = date.substring(14);
        this.date = new Date(Integer.parseInt(year) - 1900, Integer.parseInt(month), Integer.parseInt(day), Integer.parseInt(hour), Integer.parseInt(min));
        this.room_number = room_number;
        this.prescription = prescription;
    }

    @Id
    @GeneratedValue
    @XmlAttribute
    public int getAppointment_id() {
        return appointment_id;
    }

    public void setAppointment_id(int appointment_id) {
        this.appointment_id = appointment_id;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public int getRoom_number() {
        return room_number;
    }

    public void setRoom_number(int room_number) {
        this.room_number = room_number;
    }

    public String getPrescription() {
        return prescription;
    }

    public void setPrescription(String prescription) {
        this.prescription = prescription;
    }

    @ManyToOne
    public Doctor getDoctor() {
        return doctor;
    }
    public void setDoctor(Doctor doctor) {
        this.doctor = doctor;
    }

    @ManyToOne
    public Patient getPatient() {
        return patient;
    }
    public void setPatient(Patient patient) {
        this.patient = patient;
    }

    @ManyToOne
    public Disease getDisease() {
        return disease;
    }
    public void setDisease(Disease disease) {
        this.disease = disease;
    }
}
