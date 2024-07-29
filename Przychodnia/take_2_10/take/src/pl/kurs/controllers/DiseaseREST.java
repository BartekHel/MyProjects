package pl.kurs.controllers;

import pl.kurs.EJB.AppointmentEJB;
import pl.kurs.EJB.DiseaseEJB;
import pl.kurs.EJB.PatientsDiseasesEJB;
import pl.kurs.entity.Appointment;
import pl.kurs.entity.Disease;
import pl.kurs.entity.PatientsDiseases;

import javax.ejb.EJB;
import javax.ws.rs.*;
import javax.ws.rs.core.Response;
import java.util.ArrayList;
import java.util.List;

@Path("/disease")
@Consumes({ "application/json" })
@Produces({ "application/json" })

//@Consumes({ "application/xml" })
//@Produces({ "application/xml" })
public class DiseaseREST {
    @EJB
    DiseaseEJB bean;
    @EJB
    AppointmentEJB appointmentBean;
    @EJB
    PatientsDiseasesEJB patientsDiseasesEJB;

    //@POST
    @GET
    @Path("/Add={name}")
    public Response create(@PathParam("name") String name) {
        Disease disease = new Disease(name);
        bean.create(disease);
        return Response
                .status(200)
                .header("Access-Control-Allow-Origin", "*")
                .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                .header("Access-Control-Allow-Credentials", "true")
                .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                .header("Access-Control-Max-Age", "1209600")
                .entity("Disease created!")
                .build();
    }

    @GET
    @Path("/{disease_id}")
    public Response find(@PathParam("disease_id") int disease_id) {
        Disease disease = bean.find(disease_id);
        return Response
                .status(200)
                .header("Access-Control-Allow-Origin", "*")
                .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                .header("Access-Control-Allow-Credentials", "true")
                .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                .header("Access-Control-Max-Age", "1209600")
                .entity(disease.getDisease_id() + " " + disease.getName())
                .build();
    }

    @GET
    @Path("/listdiseases")
    public Response get() {
        List<Disease> ldiseases = bean.get();
        List<String> diseases = new ArrayList<String>();
        for(Disease disease : ldiseases) {
            diseases.add(disease.getDisease_id() + " " + disease.getName());
        }
        return Response
                .status(200)
                .header("Access-Control-Allow-Origin", "*")
                .header("Access-Control-Allow-Headers", "origin, content-type, accept, authorization")
                .header("Access-Control-Allow-Credentials", "true")
                .header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD")
                .header("Access-Control-Max-Age", "1209600")
                .entity(diseases)
                .build();
    }

    @PUT
    public String update(Disease disease) {
        try {
            bean.update(disease);
            return "disease updated!";
        } catch (Exception e) {
            e.printStackTrace();
            return "disease not updated :(";
        }
    }


    @GET
    @Path("/del/{disease_id}")
    public Response delete(@PathParam("disease_id") int disease_id) {
        try {
            for(Appointment appointment : appointmentBean.get()) {
                if(appointment.getDisease().getDisease_id() == disease_id) {
                    appointmentBean.delete(appointment.getAppointment_id());
                }
            }
            for(PatientsDiseases patientsDiseases : patientsDiseasesEJB.get()) {
                if(patientsDiseases.getDisease().getDisease_id() == disease_id) {
                    patientsDiseasesEJB.delete(patientsDiseases.getPatientsDiseases_id());
                }
            }
            bean.delete(disease_id);
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