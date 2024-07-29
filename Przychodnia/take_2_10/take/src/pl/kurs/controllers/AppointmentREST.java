package pl.kurs.controllers;

import pl.kurs.EJB.*;
import pl.kurs.entity.*;
import pl.kurs.requests.AppointmentRequest;

import javax.ejb.EJB;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

@Path("/appointment")
@Consumes({ "application/json" })
@Produces({ "application/json" })

//@Consumes({ "application/xml" })
//@Produces({ "application/xml" })
public class AppointmentREST {
    @EJB
    AppointmentEJB bean;

    @EJB
    DoctorEJB doctorBean;

    @EJB
    PatientEJB patientBean;

    @EJB
    DiseaseEJB diseaseBean;

    @EJB
    PatientsDiseasesEJB patientsDiseasesEJB;

//    @POST
//    @Path("/add/")
//    @Consumes(MediaType.APPLICATION_JSON)
//    @Produces(MediaType.APPLICATION_JSON)
//    public Response create(AppointmentRequest appointmentRequest) {
//        Appointment appointment = new Appointment(Integer.parseInt(appointmentRequest.getRoom_number()), appointmentRequest.getPrescription());
//        bean.create(appointment);
//        return Response
//                .status(200)
//                .header("Access-Control-Allow-Origin", "*")
//                .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
//                .header("Access-Control-Allow-Credentials", "true")
//                .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
//                .header("Access-Control-Max-Age", "1209600")
//                .entity("Appointment created")
//                .build();
//    }

    @GET
    @Path("/{date}/{room_number}/{prescription}/{choose-patient}/{choose-doctor}/{choose-disease}")
    public Response create(@PathParam("date") String date, @PathParam("room_number") String roomNumber,
                           @PathParam("prescription") String prescription, @PathParam("choose-patient") String patientID,
                           @PathParam("choose-doctor") String doctorID, @PathParam("choose-disease") String diseaseID) {
        Appointment appointment = new Appointment(date, Integer.parseInt(roomNumber), prescription);

        Patient patient = patientBean.find(Integer.parseInt(patientID));
        Doctor doctor = doctorBean.find(Integer.parseInt(doctorID));
        Disease disease = diseaseBean.find(Integer.parseInt(diseaseID));

        appointment.setPatient(patient);
        appointment.setDoctor(doctor);
        appointment.setDisease(disease);

        PatientsDiseases patientsDiseases = new PatientsDiseases();
        patientsDiseases.setPatient(patient);
        patientsDiseases.setDisease(disease);
        patientsDiseasesEJB.create(patientsDiseases);

        bean.create(appointment);
        return Response
                .status(200)
                .header("Access-Control-Allow-Origin", "*")
                .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                .header("Access-Control-Allow-Credentials", "true")
                .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                .header("Access-Control-Max-Age", "1209600")
                .entity("Appointment created")
                .build();
    }

    @GET
    @Path("/{appointment_id}")
    public Response find(@PathParam("appointment_id") int appointment_id) {
        Appointment appointment = bean.find(appointment_id);
        return Response
                .status(200)
                .header("Access-Control-Allow-Origin", "*")
                .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                .header("Access-Control-Allow-Credentials", "true")
                .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                .header("Access-Control-Max-Age", "1209600")
                .entity(appointment.getAppointment_id() + " " + appointment.getRoom_number() + " " + appointment.getPrescription())
                .build();
    }

    @GET
    @Path("/listappointments")
    public Response get() {
        List<Appointment> lappointments = bean.get();
        List<String> appointments = new ArrayList<String>();
        for(Appointment appointment : lappointments) {
            appointments.add(appointment.getAppointment_id() + " " + appointment.getDate().toString().substring(0, 16) + " " + appointment.getRoom_number() + " " + appointment.getPrescription() +
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
                .entity(appointments)
                .build();
    }

    @PUT
    public String update(Appointment appointment) {
        try {
            bean.update(appointment);
            return "appointment updated!";
        } catch (Exception e) {
            e.printStackTrace();
            return "appointment not updated :(";
        }
    }


    @GET
    @Path("/del/{appointment_id}")
    public Response delete(@PathParam("appointment_id") int appointment_id) {
        try {
            bean.delete(appointment_id);
            return Response
                    .status(200)
                    .header("Access-Control-Allow-Origin", "*")
                    .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                    .header("Access-Control-Allow-Credentials", "true")
                    .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                    .header("Access-Control-Max-Age", "1209600")
                    .entity("Sukces")
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