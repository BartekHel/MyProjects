package pl.kurs.EJB;

import pl.kurs.entity.Patient;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
import java.util.List;

@Stateless
public class PatientEJB {
    @PersistenceContext(name="patient")
    EntityManager manager;


    public void create(Patient patient) {
        System.out.println("Creating patient!");
        manager.persist(patient);
    }

    public void delete(int patient_id) {
        Patient patient = manager.find(Patient.class, patient_id);
        manager.remove(patient);
    }

    //public List<Car> findByMake(String make) {
    //    Query q = manager.createQuery("select c from Car c where c.make like :make");
    //    q.setParameter("make", make);
    //    @SuppressWarnings("unchecked")
    //    List<Car> lista =q.getResultList();
    //    return lista;
    //}

    public Patient find(int patient_id) {
        return manager.find(Patient.class, patient_id);
    }

    public List<Patient> get() {
        Query q = manager.createQuery("select p from Patient p");
        @SuppressWarnings("unchecked")
        List<Patient> list = q.getResultList();
        return list;
    }

    public void update(Patient patient) {
        patient = manager.merge(patient);
    }
}
