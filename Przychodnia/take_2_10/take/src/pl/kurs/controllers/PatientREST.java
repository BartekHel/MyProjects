package pl.kurs.controllers;

import pl.kurs.EJB.AppointmentEJB;
import pl.kurs.EJB.PatientEJB;
import pl.kurs.EJB.PatientsDiseasesEJB;
import pl.kurs.entity.Appointment;
import pl.kurs.entity.Patient;
import pl.kurs.entity.PatientsDiseases;

import javax.ejb.EJB;
import javax.ws.rs.*;
import javax.ws.rs.core.Response;
import java.util.ArrayList;
import java.util.List;

@Path("/patient")
@Consumes({ "application/json" })
@Produces({ "application/json" })

//@Consumes({ "application/xml" })
//@Produces({ "application/xml" })
public class PatientREST {
    @EJB
    PatientEJB bean;
    @EJB
    AppointmentEJB appointmentBean;
    @EJB
    PatientsDiseasesEJB patientsDiseasesEJB;

    //@POST
    @GET
    @Path("/{name}/{surname}/{address}")
    public Response create(@PathParam("name") String name, @PathParam("surname") String surname, @PathParam("address") String address) {
        Patient patient = new Patient(name, surname, address);
        bean.create(patient);
        return Response
                .status(200)
                .header("Access-Control-Allow-Origin", "*")
                .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                .header("Access-Control-Allow-Credentials", "true")
                .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                .header("Access-Control-Max-Age", "1209600")
                .entity("Patient created!")
                .build();    }

    @GET
    @Path("/{patient_id}")
    public Response find(@PathParam("patient_id") int patient_id) {
        Patient patient = bean.find(patient_id);
        return Response
                .status(200)
                .header("Access-Control-Allow-Origin", "*")
                .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                .header("Access-Control-Allow-Credentials", "true")
                .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                .header("Access-Control-Max-Age", "1209600")
                .entity(patient.getName() + " " + patient.getSurname() + " " + patient.getAddress())
                .build();
    }

    @GET
    @Path("/listpatients")
    public Response get() {
        List<Patient> lpatients = bean.get();
        List<String> patients = new ArrayList<String>();
        for(Patient patient : lpatients) {
            patients.add(patient.getPatient_id() + " " + patient.getName() + " " + patient.getSurname() + " " + patient.getAddress());
        }
        return Response
                .status(200)
                .header("Access-Control-Allow-Origin", "*")
                .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                .header("Access-Control-Allow-Credentials", "true")
                .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                .header("Access-Control-Max-Age", "1209600")
                .entity(patients)
                .build();
    }

    @GET
    @Path("/listapp/{patient_id}")
    public Response getAppointments(@PathParam("patient_id") int patientId) {
        Patient patient = bean.find(patientId);
        List<String> patientAppointments = new ArrayList<String>();
        for (Appointment appointment : patient.getAppointments()) {
            patientAppointments.add(appointment.getAppointment_id() + " " + appointment.getDate().toString().substring(0, 16) + " " + appointment.getRoom_number() + " " + appointment.getPrescription() +
                    " Pacjent: " + appointment.getPatient().getName() + " " + appointment.getPatient().getSurname() +
                    " Doktor: " + appointment.getDoctor().getName() + " " + appointment.getDoctor().getSurname() +
                    " Diagnoza: " + appointment.getDisease().getName());
        }
        return Response
                .status(200)
                .header("Access-Control-Allow-Origin", "*")
                .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                .header("Access-Control-Allow-Credentials", "true")
                .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                .header("Access-Control-Max-Age", "1209600")
                .entity(patientAppointments)
                .build();
    }

    @GET
    @Path("/listdis/{patient_id}")
    public Response getDiseases(@PathParam("patient_id") int patientId) {
        try {
            Patient patient = bean.find(patientId);
            List<String> patientDiseases = new ArrayList<String>();
            for (PatientsDiseases disease : patient.getPatientsDiseases()) {
                patientDiseases.add(disease.getDisease().getDisease_id() + " " + disease.getDisease().getName());
            }
            return Response
                    .status(200)
                    .header("Access-Control-Allow-Origin", "*")
                    .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                    .header("Access-Control-Allow-Credentials", "true")
                    .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                    .header("Access-Control-Max-Age", "1209600")
                    .entity(patientDiseases)
                    .build();
        } catch (Exception e) {
            return Response
                    .status(200)
                    .header("Access-Control-Allow-Origin", "*")
                    .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                    .header("Access-Control-Allow-Credentials", "true")
                    .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                    .header("Access-Control-Max-Age", "1209600")
                    .entity("Brak chorób")
                    .build();
        }
    }

    @PUT
    public String update(Patient patient) {
        try {
            bean.update(patient);
            return "patient updated!";
        } catch (Exception e) {
            e.printStackTrace();
            return "patient not updated :(";
        }
    }


    @GET
    @Path("/del/{patient_id}")
    public Response delete(@PathParam("patient_id") int patient_id) {
        try {
            for(Appointment app : appointmentBean.get()) {
                if(app.getPatient().getPatient_id() == patient_id) {
                    appointmentBean.delete(app.getAppointment_id());
                }
            }
            for(PatientsDiseases patientsDiseases : patientsDiseasesEJB.get()) {
                if(patientsDiseases.getPatient().getPatient_id() == patient_id) {
                    patientsDiseasesEJB.delete(patientsDiseases.getPatientsDiseases_id());
                }
            }
            bean.delete(patient_id);
            return Response
                    .status(200)
                    .header("Access-Control-Allow-Origin", "*")
                    .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                    .header("Access-Control-Allow-Credentials", "true")
                    .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                    .header("Access-Control-Max-Age", "1209600")
                    .entity("Sukses")
                    .build();
        } catch (Exception e) {
            return Response
                    .status(200)
                    .header("Access-Control-Allow-Origin", "*")
                    .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                    .header("Access-Control-Allow-Credentials", "true")
                    .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                    .header("Access-Control-Max-Age", "1209600")
                    .entity(e)
                    .build();
        }

    }
}
