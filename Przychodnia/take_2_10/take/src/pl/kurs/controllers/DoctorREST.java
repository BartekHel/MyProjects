package pl.kurs.controllers;

import pl.kurs.EJB.AppointmentEJB;
import pl.kurs.EJB.DoctorEJB;
import pl.kurs.entity.Appointment;
import pl.kurs.entity.Doctor;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

import javax.ejb.EJB;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Path("/doctor")
@Consumes({ "application/json" })
@Produces({ "application/json" })

//@Consumes({ "application/xml" })
//@Produces({ "application/xml" })
public class DoctorREST {
    @EJB
    DoctorEJB bean;
    @EJB
    AppointmentEJB appointmentBean;

    //@POST
    @GET
    @Path("/{name}/{surname}/{specialization}")
    public Response create(@PathParam("name") String name, @PathParam("surname") String surname, @PathParam("specialization")String specialization) {
        Doctor doctor = new Doctor(name, surname, specialization);
        bean.create(doctor);
        //Appointment app1=new Appointment(1,"przeziebienie");
        //Appointment app2=new Appointment(2,"zdrowy");

        //app1.setDoctor(doctor);
        //app2.setDoctor(doctor);

        //appointmentBean.create(app1);
        //appointmentBean.create(app2);

        //doctor.getAppointments().add(app1);
        //doctor.getAppointments().add(app2);
        return Response
                .status(200)
                .header("Access-Control-Allow-Origin", "*")
                .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                .header("Access-Control-Allow-Credentials", "true")
                .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                .header("Access-Control-Max-Age", "1209600")
                .entity("Doctor created!")
                .build();
    }

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    @Path("/{doctor_id}")
    public Response find(@PathParam("doctor_id") int doctor_id) {
        Doctor doctor = bean.find(doctor_id);
        //return doctor.getName() + " " + doctor.getSurname()+" "+
        //        doctor.getAppointments().toString();
        return Response
                .status(200)
                .header("Access-Control-Allow-Origin", "*")
                .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                .header("Access-Control-Allow-Credentials", "true")
                .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                .header("Access-Control-Max-Age", "1209600")
                .entity(doctor.getName() + " " + doctor.getSurname() + " " + doctor.getSpecialization())
                .build();
    }

    @GET
    @Path("/listdoctors")
    public Response get() {
        try {
            List<Doctor> ldoctors = bean.get();
            List<String> doctors = new ArrayList<String>();
            for (Doctor doctor : ldoctors) {
                doctors.add(doctor.getDoctor_id() + " " + doctor.getName() + " " + doctor.getSurname() + " " + doctor.getSpecialization());
            }
            //return doctors;
            return Response
                    .status(200)
                    .header("Access-Control-Allow-Origin", "*")
                    .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                    .header("Access-Control-Allow-Credentials", "true")
                    .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                    .header("Access-Control-Max-Age", "1209600")
                    .entity(doctors)
                    .build();
        } catch (Exception e) {
            return Response
                    .status(200)
                    .header("Access-Control-Allow-Origin", "*")
                    .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                    .header("Access-Control-Allow-Credentials", "true")
                    .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                    .header("Access-Control-Max-Age", "1209600")
                    .entity("Brak doktorów")
                    .build();
        }
    }

    @GET
    @Path("/listapp/{doctor_id}")
    public Response getAppointments(@PathParam("doctor_id") int doctorId) {
        Doctor doctor = bean.find(doctorId);
        List<String> doctorAppointments = new ArrayList<String>();
        for (Appointment appointment : doctor.getAppointments()) {
            doctorAppointments.add(appointment.getAppointment_id() + " " + appointment.getDate().toString().substring(0, 16) + " " + appointment.getRoom_number() + " " + appointment.getPrescription() +
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
                .entity(doctorAppointments)
                .build();
    }

    @PUT
    public String update(Doctor doctor) {
        try {
            bean.update(doctor);
            return "doctor updated!";
        } catch (Exception e) {
            e.printStackTrace();
            return "doctor not updated :(";
        }
    }


    @GET
    @Path("/del/{doctor_id}")
    public Response delete(@PathParam("doctor_id") int doctor_id) {
        try {
            for(Appointment appointment : appointmentBean.get()) {
                if(appointment.getDoctor().getDoctor_id() == doctor_id) {
                    appointmentBean.delete(appointment.getAppointment_id());
                }
            }
            bean.delete(doctor_id);
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