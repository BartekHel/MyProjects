package pl.kurs.EJB;

import pl.kurs.entity.Doctor;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
import java.util.List;

@Stateless
public class DoctorEJB {
    @PersistenceContext(name="doctor")
    EntityManager manager;


    public void create(Doctor doctor) {
        System.out.println("Creating doctor!");
        manager.persist(doctor);
    }

    public void delete(int doctor_id) {
        Doctor doctor = manager.find(Doctor.class, doctor_id);
        manager.remove(doctor);
    }

    //public List<Car> findByMake(String make) {
    //    Query q = manager.createQuery("select c from Car c where c.make like :make");
    //    q.setParameter("make", make);
    //    @SuppressWarnings("unchecked")
    //    List<Car> lista =q.getResultList();
    //    return lista;
    //}

    public Doctor find(int doctor_id) {
        return manager.find(Doctor.class, doctor_id);
    }

    public List<Doctor> get() {
        Query q = manager.createQuery("select d from Doctor d");
        @SuppressWarnings("unchecked")
        List<Doctor> list = q.getResultList();
        return list;
    }

    public void update(Doctor doctor) {
        doctor = manager.merge(doctor);
    }
}