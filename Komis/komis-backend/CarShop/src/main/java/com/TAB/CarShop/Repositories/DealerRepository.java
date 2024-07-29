package com.TAB.CarShop.Repositories;

import com.TAB.CarShop.Entities.Dealer;
import com.TAB.CarShop.Entities.Manager;
import com.TAB.CarShop.Entities.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface DealerRepository extends JpaRepository<Dealer, Long> {
	void deleteByUser(User user);
}