package com.TAB.CarShop.Repositories;

import com.TAB.CarShop.Entities.Repairer;
import com.TAB.CarShop.Entities.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface RepairerRepository extends JpaRepository<Repairer, Long> {
	void deleteByUser(User user);
}
