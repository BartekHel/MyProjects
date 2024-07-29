package com.TAB.CarShop.Repositories;

import com.TAB.CarShop.Entities.Manager;
import com.TAB.CarShop.Entities.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface ManagerRepository extends JpaRepository<Manager, Long> {
	void deleteByUser(User user);
}
