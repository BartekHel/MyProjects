package pl.kurs.EJB;

import pl.kurs.entity.Appointment;
import pl.kurs.entity.Doctor;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
import java.util.List;

@Stateless
public class AppointmentEJB {
    @PersistenceContext(name="appointment")
    EntityManager manager;


    public void create(Appointment appointment) {
        System.out.println("Creating appointment!");
        manager.persist(appointment);
    }

    public void delete(int appointment_id) {
        Appointment appointment = manager.find(Appointment.class, appointment_id);
        manager.remove(appointment);
    }

    //public List<Car> findByMake(String make) {
    //    Query q = manager.createQuery("select c from Car c where c.make like :make");
    //    q.setParameter("make", make);
    //    @SuppressWarnings("unchecked")
    //    List<Car> lista =q.getResultList();
    //    return lista;
    //}

    public Appointment find(int appointment_id) {
        return manager.find(Appointment.class, appointment_id);
    }

    public List<Appointment> get() {
        Query q = manager.createQuery("select a from Appointment a");
        @SuppressWarnings("unchecked")
        List<Appointment> list = q.getResultList();
        return list;
    }

    public void update(Appointment appointment) {
        appointment = manager.merge(appointment);
    }
}

