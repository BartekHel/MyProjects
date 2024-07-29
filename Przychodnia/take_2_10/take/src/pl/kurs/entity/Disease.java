package pl.kurs.entity;

import javax.persistence.*;
import javax.xml.bind.annotation.XmlRootElement;

import com.sun.xml.internal.txw2.annotation.XmlAttribute;

import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

@Entity
@XmlRootElement
public class Disease implements Serializable {
    private static final long serialVersionUID = 1L;
    int disease_id;
    String name;
    Set<Appointment> appointments = new HashSet<Appointment>();
    Set<PatientsDiseases> patientsDiseases = new HashSet<PatientsDiseases>();

    public Disease() {
    }

    public Disease(String name) {
        this.name = name;
    }

    @Id
    @GeneratedValue
    @XmlAttribute
    public int getDisease_id() {
        return disease_id;
    }

    public void setDisease_id(int disease_id) {
        this.disease_id = disease_id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @OneToMany(fetch = FetchType.EAGER, mappedBy = "disease")
    public Set<Appointment> getAppointments() {
        return appointments;
    }
    public void setAppointments(Set<Appointment> appointments) {
        this.appointments = appointments;
    }

    @OneToMany(fetch = FetchType.EAGER, mappedBy = "disease")
    public Set<PatientsDiseases> getPatientsDiseases() {
        return patientsDiseases;
    }
    public void setPatientsDiseases(Set<PatientsDiseases> patientsDiseases) {
        this.patientsDiseases = patientsDiseases;
    }
}

