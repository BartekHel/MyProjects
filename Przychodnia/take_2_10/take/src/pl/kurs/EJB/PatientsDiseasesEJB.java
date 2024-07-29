package pl.kurs.EJB;

import pl.kurs.entity.Patient;
import pl.kurs.entity.PatientsDiseases;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
import java.util.List;

@Stateless
public class PatientsDiseasesEJB {
    @PersistenceContext(name="patientsdiseases")
    EntityManager manager;


    public void create(PatientsDiseases patientsDiseases) {
        System.out.println("Creating patientsDiseases!");
        manager.persist(patientsDiseases);
    }

    public void delete(int patientsdiseases_id) {
        PatientsDiseases patientsDiseases = manager.find(PatientsDiseases.class, patientsdiseases_id);
        manager.remove(patientsDiseases);
    }

    //public List<Car> findByMake(String make) {
    //    Query q = manager.createQuery("select c from Car c where c.make like :make");
    //    q.setParameter("make", make);
    //    @SuppressWarnings("unchecked")
    //    List<Car> lista =q.getResultList();
    //    return lista;
    //}

    public PatientsDiseases find(int patientsdiseases_id) {
        return manager.find(PatientsDiseases.class, patientsdiseases_id);
    }

    public List<PatientsDiseases> get() {
        Query q = manager.createQuery("select pd from PatientsDiseases pd");
        @SuppressWarnings("unchecked")
        List<PatientsDiseases> list = q.getResultList();
        return list;
    }

    public void update(PatientsDiseases patientsDiseases) {
        patientsDiseases = manager.merge(patientsDiseases);
    }
}