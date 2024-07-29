package pl.kurs.entity;

import javax.persistence.*;
import javax.xml.bind.annotation.XmlRootElement;

import com.sun.xml.internal.txw2.annotation.XmlAttribute;

import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

@Entity
@XmlRootElement
public class Patient implements Serializable {
    private static final long serialVersionUID = 1L;
    int patient_id;
    String name;
    String surname;
    String address;
    Set<Appointment> appointments = new HashSet<Appointment>();
    Set<PatientsDiseases> patientsDiseases = new HashSet<PatientsDiseases>();

    public Patient() {
    }

    public Patient(String name, String surname, String address) {
        this.name = name;
        this.surname = surname;
        this.address = address;
    }

    @Id
    @GeneratedValue
    @XmlAttribute
    public int getPatient_id() {
        return patient_id;
    }

    public void setPatient_id(int patient_id) {
        this.patient_id = patient_id;
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

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    @OneToMany(fetch = FetchType.EAGER, mappedBy = "patient")
    public Set<Appointment> getAppointments() {
        return appointments;
    }
    public void setAppointments(Set<Appointment> appointments) {
        this.appointments = appointments;
    }

    @OneToMany(fetch = FetchType.EAGER, mappedBy = "patient")
    public Set<PatientsDiseases> getPatientsDiseases() {
        return patientsDiseases;
    }
    public void setPatientsDiseases(Set<PatientsDiseases> patientsDiseases) {
        this.patientsDiseases = patientsDiseases;
    }
}

