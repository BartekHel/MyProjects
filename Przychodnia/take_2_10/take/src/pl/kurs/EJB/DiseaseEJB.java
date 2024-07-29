package pl.kurs.EJB;

import pl.kurs.entity.Disease;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
import java.util.List;

@Stateless
public class DiseaseEJB {
    @PersistenceContext(name="disease")
    EntityManager manager;


    public void create(Disease disease) {
        System.out.println("Creating disease!");
        manager.persist(disease);
    }

    public void delete(int disease_id) {
        Disease disease = manager.find(Disease.class, disease_id);
        manager.remove(disease);
    }

    //public List<Car> findByMake(String make) {
    //    Query q = manager.createQuery("select c from Car c where c.make like :make");
    //    q.setParameter("make", make);
    //    @SuppressWarnings("unchecked")
    //    List<Car> lista =q.getResultList();
    //    return lista;
    //}

    public Disease find(int disease_id) {
        return manager.find(Disease.class, disease_id);
    }

    public List<Disease> get() {
        Query q = manager.createQuery("select d from Disease d");
        @SuppressWarnings("unchecked")
        List<Disease> list = q.getResultList();
        return list;
    }

    public void update(Disease disease) {
        disease = manager.merge(disease);
    }
}