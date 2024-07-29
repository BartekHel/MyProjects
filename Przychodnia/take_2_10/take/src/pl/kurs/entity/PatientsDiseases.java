package pl.kurs.entity;

import javax.persistence.*;
import javax.xml.bind.annotation.XmlRootElement;

import com.sun.xml.internal.txw2.annotation.XmlAttribute;

import java.io.Serializable;

@Entity
@XmlRootElement
public class PatientsDiseases implements Serializable {
    private static final long serialVersionUID = 1L;
    int patientsdiseases_id;
    Patient patient;
    Disease disease;

    @Id
    @GeneratedValue
    @XmlAttribute
    public int getPatientsDiseases_id() {
        return patientsdiseases_id;
    }

    public void setPatientsDiseases_id(int patientsdiseases_id) {
        this.patientsdiseases_id = patientsdiseases_id;
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
    public void setDisease(Disease diseases) {
        this.disease = diseases;
    }
}
