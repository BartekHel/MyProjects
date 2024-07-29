-- MySQL dump 10.13  Distrib 8.0.36, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: car_shop
-- ------------------------------------------------------
-- Server version	8.0.37

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `clients`
--

DROP TABLE IF EXISTS `clients`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `clients` (
  `client_id` bigint NOT NULL AUTO_INCREMENT,
  `user_id` bigint DEFAULT NULL,
  `token` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`client_id`),
  UNIQUE KEY `UK_smrp6gi0tckq1w5rnd7boyowu` (`user_id`),
  CONSTRAINT `FKtiuqdledq2lybrds2k3rfqrv4` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `clients`
--

LOCK TABLES `clients` WRITE;
/*!40000 ALTER TABLE `clients` DISABLE KEYS */;
INSERT INTO `clients` VALUES (1,10,NULL),(2,11,NULL),(3,12,NULL),(4,13,NULL),(5,14,NULL),(6,15,NULL),(7,16,NULL);
/*!40000 ALTER TABLE `clients` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dealers`
--

DROP TABLE IF EXISTS `dealers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `dealers` (
  `dealer_id` bigint NOT NULL AUTO_INCREMENT,
  `manager_id` bigint DEFAULT NULL,
  `user_id` bigint DEFAULT NULL,
  PRIMARY KEY (`dealer_id`),
  UNIQUE KEY `UK_10jndvam70sjubvckk4l6cvxr` (`user_id`),
  KEY `FKocxses6vlpt0hrrv8a1tp4anh` (`manager_id`),
  CONSTRAINT `FKocxses6vlpt0hrrv8a1tp4anh` FOREIGN KEY (`manager_id`) REFERENCES `managers` (`manager_id`),
  CONSTRAINT `FKqoq67umfy4ce8rtk8872opdpp` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `dealers`
--

LOCK TABLES `dealers` WRITE;
/*!40000 ALTER TABLE `dealers` DISABLE KEYS */;
INSERT INTO `dealers` VALUES (1,1,6),(2,1,7),(3,2,8),(4,2,9);
/*!40000 ALTER TABLE `dealers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `managers`
--

DROP TABLE IF EXISTS `managers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `managers` (
  `manager_id` bigint NOT NULL AUTO_INCREMENT,
  `showroom_id` bigint DEFAULT NULL,
  `user_id` bigint DEFAULT NULL,
  PRIMARY KEY (`manager_id`),
  UNIQUE KEY `UK_1ckf1cflviafpcqluwjrpmrp2` (`showroom_id`),
  UNIQUE KEY `UK_6sl3ig444d4qy4c2kq6ju96pf` (`user_id`),
  CONSTRAINT `FK15075knvq6w78g82uhxp0cot7` FOREIGN KEY (`showroom_id`) REFERENCES `showrooms` (`showroom_id`),
  CONSTRAINT `FKsp1db43yf1nqhswrpbwmlnhb9` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `managers`
--

LOCK TABLES `managers` WRITE;
/*!40000 ALTER TABLE `managers` DISABLE KEYS */;
INSERT INTO `managers` VALUES (1,1,1),(2,2,2);
/*!40000 ALTER TABLE `managers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `orders`
--

DROP TABLE IF EXISTS `orders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `orders` (
  `order_id` bigint NOT NULL AUTO_INCREMENT,
  `delivery_date` date DEFAULT NULL,
  `price` double NOT NULL,
  `submission_date` date NOT NULL,
  `client_id` bigint DEFAULT NULL,
  `dealer_id` bigint DEFAULT NULL,
  `showroom_id` bigint DEFAULT NULL,
  `vehicle_id` bigint DEFAULT NULL,
  PRIMARY KEY (`order_id`),
  UNIQUE KEY `UK_dcur7gfd2j79cffe5lh8exv7k` (`vehicle_id`),
  KEY `FKm2dep9derpoaehshbkkatam3v` (`client_id`),
  KEY `FKc174cj48olwptv2nlqy2iuiy4` (`dealer_id`),
  KEY `FKmnt30htq2m1fo9q06giu3q3gv` (`showroom_id`),
  CONSTRAINT `FKc174cj48olwptv2nlqy2iuiy4` FOREIGN KEY (`dealer_id`) REFERENCES `dealers` (`dealer_id`),
  CONSTRAINT `FKm2dep9derpoaehshbkkatam3v` FOREIGN KEY (`client_id`) REFERENCES `clients` (`client_id`),
  CONSTRAINT `FKmnt30htq2m1fo9q06giu3q3gv` FOREIGN KEY (`showroom_id`) REFERENCES `showrooms` (`showroom_id`),
  CONSTRAINT `FKov6eiiyhqkasfj9jlt2s6wj5p` FOREIGN KEY (`vehicle_id`) REFERENCES `vehicles` (`vehicle_id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `orders`
--

LOCK TABLES `orders` WRITE;
/*!40000 ALTER TABLE `orders` DISABLE KEYS */;
INSERT INTO `orders` VALUES (3,'2024-06-14',35000,'2024-06-14',5,3,2,2),(4,'2024-06-28',30340,'2024-06-14',7,4,1,17),(5,'2024-06-28',20220,'2024-06-14',6,4,1,19),(6,'2024-06-28',26100,'2024-06-14',5,3,2,29),(7,'2024-06-14',21110,'2024-06-14',1,1,2,21),(8,'2024-06-14',40000,'2024-06-14',2,1,1,22),(9,'2024-06-28',32000,'2024-06-14',3,4,2,12),(10,'2024-06-28',22500,'2024-06-14',4,3,2,39),(11,'2024-06-28',27500,'2024-06-14',4,3,2,3),(12,'2024-06-14',35500,'2024-06-14',6,2,1,6);
/*!40000 ALTER TABLE `orders` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `repairers`
--

DROP TABLE IF EXISTS `repairers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `repairers` (
  `repairer_id` bigint NOT NULL AUTO_INCREMENT,
  `manager_id` bigint DEFAULT NULL,
  `user_id` bigint DEFAULT NULL,
  PRIMARY KEY (`repairer_id`),
  UNIQUE KEY `UK_jir7kgfmhixhol7e9nsdrfnvs` (`user_id`),
  KEY `FK26cm5ppabkxw37cb0ryhgjckg` (`manager_id`),
  CONSTRAINT `FK26cm5ppabkxw37cb0ryhgjckg` FOREIGN KEY (`manager_id`) REFERENCES `managers` (`manager_id`),
  CONSTRAINT `FK6hhbhf0kh2tys42uvkjhlfnx3` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `repairers`
--

LOCK TABLES `repairers` WRITE;
/*!40000 ALTER TABLE `repairers` DISABLE KEYS */;
INSERT INTO `repairers` VALUES (1,1,3),(2,1,4),(3,2,5);
/*!40000 ALTER TABLE `repairers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `services`
--

DROP TABLE IF EXISTS `services`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `services` (
  `service_id` bigint NOT NULL AUTO_INCREMENT,
  `admission_date` date NOT NULL,
  `description` varchar(255) DEFAULT NULL,
  `execution_date` date DEFAULT NULL,
  `price` double NOT NULL,
  `repairer_id` bigint DEFAULT NULL,
  `vehicle_id` bigint DEFAULT NULL,
  PRIMARY KEY (`service_id`),
  KEY `FKbk7kf7ncfovb4yrnofvjdb6bh` (`repairer_id`),
  KEY `FKlph60ok9q3oibqawro4eawrj` (`vehicle_id`),
  CONSTRAINT `FKbk7kf7ncfovb4yrnofvjdb6bh` FOREIGN KEY (`repairer_id`) REFERENCES `repairers` (`repairer_id`),
  CONSTRAINT `FKlph60ok9q3oibqawro4eawrj` FOREIGN KEY (`vehicle_id`) REFERENCES `vehicles` (`vehicle_id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `services`
--

LOCK TABLES `services` WRITE;
/*!40000 ALTER TABLE `services` DISABLE KEYS */;
INSERT INTO `services` VALUES (1,'2023-01-09','Wymiana opon','2023-01-11',500,1,5),(2,'2023-02-08','Wymiana opon','2023-02-11',600,2,11),(3,'2023-03-07','Wymiana drzwi','2023-03-11',200,3,7),(4,'2023-04-06','Wymiana oleju','2023-04-11',100,2,13),(5,'2023-05-05','Wymiana opon','2023-05-11',700,1,2),(6,'2023-06-04','Wymiana silnika','2023-06-11',800,3,4),(7,'2023-07-03','Wymiana szyby','2023-07-11',300,3,18),(8,'2023-08-02','Wymiana śrób w kołach','2023-08-11',900,1,16),(9,'2023-09-01','Wymiana opon','2023-09-11',400,2,14);
/*!40000 ALTER TABLE `services` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `showrooms`
--

DROP TABLE IF EXISTS `showrooms`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `showrooms` (
  `showroom_id` bigint NOT NULL AUTO_INCREMENT,
  `address` varchar(255) NOT NULL,
  PRIMARY KEY (`showroom_id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `showrooms`
--

LOCK TABLES `showrooms` WRITE;
/*!40000 ALTER TABLE `showrooms` DISABLE KEYS */;
INSERT INTO `showrooms` VALUES (1,'Akademicka 16 Gliwice'),(2,'Zadupie 300 kilometrów stąd');
/*!40000 ALTER TABLE `showrooms` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `user_id` bigint NOT NULL AUTO_INCREMENT,
  `email` varchar(255) NOT NULL,
  `login` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `role` enum('ADMIN','CLIENT','MANAGER','REPAIRER','DEALER') DEFAULT NULL,
  `surname` varchar(255) NOT NULL,
  PRIMARY KEY (`user_id`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'manager1@gmail.com','manager1','Janusz','1234','MANAGER','Managier'),(2,'manager2@gmail.com','manager2','Grzegorz','1234','MANAGER','Managier'),(3,'repairer1@gmail.com','repairer1','Złota','1234','REPAIRER','Ronczka'),(4,'repairer2@gmail.com','repairer2','Srebrna','1234','REPAIRER','Ronczka'),(5,'repairer3@gmail.com','repairer3','Plastikowa','1234','REPAIRER','Ronczka'),(6,'dealer1@gmail.com','dealer1','Handlarz','1234','DEALER','Autami'),(7,'dealer2@gmail.com','dealer2','Handlarz','1234','DEALER','Samochodami'),(8,'dealer3@gmail.com','dealer3','Handlarz','1234','DEALER','Pojazdami'),(9,'dealer4@gmail.com','dealer4','Handlarz','1234','DEALER','Wehiklami'),(10,'client1@gmail.com','client1','Kupie','1234','CLIENT','Honde'),(11,'client2@gmail.com','client2','NieKupie','1234','CLIENT','Hondy'),(12,'client3@gmail.com','client3','Wojciech','1234','CLIENT','Wójcik'),(13,'client4@gmail.com','client4','Pan','1234','CLIENT','Prezydent'),(14,'client5@gmail.com','client5','James','1234','CLIENT','LeBron'),(15,'client6@gmail.com','client6','imie','1234','CLIENT','ZMałej'),(16,'client7@gmail.com','client7','Vehiclepilled','1234','CLIENT','Carbuyer'),(17,'admin1@gmail.com','admin1','Zdzisław','1234','ADMIN','Admin');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vehicles`
--

DROP TABLE IF EXISTS `vehicles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `vehicles` (
  `vehicle_id` bigint NOT NULL AUTO_INCREMENT,
  `brand` varchar(255) NOT NULL,
  `model` varchar(255) NOT NULL,
  `modifications` varchar(255) DEFAULT NULL,
  `next_inspection_date` date DEFAULT NULL,
  `price` double NOT NULL,
  `was_sold` bit(1) DEFAULT NULL,
  `showroom_id` bigint DEFAULT NULL,
  `picture_file_name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`vehicle_id`),
  KEY `FKlegrvmc28emrbwdsg0ow8b4m8` (`showroom_id`),
  CONSTRAINT `FKlegrvmc28emrbwdsg0ow8b4m8` FOREIGN KEY (`showroom_id`) REFERENCES `showrooms` (`showroom_id`)
) ENGINE=InnoDB AUTO_INCREMENT=42 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vehicles`
--

LOCK TABLES `vehicles` WRITE;
/*!40000 ALTER TABLE `vehicles` DISABLE KEYS */;
INSERT INTO `vehicles` VALUES (2,'Honda','Fit','płyn do bulbulatora','2025-06-14',28761,_binary '',2,'HondaFit.png'),(3,'Ford','Explorer',NULL,'2025-06-28',12315,_binary '',1,'FordExplorer.png'),(4,'Ford','Mustang',NULL,NULL,20410,_binary '\0',1,'FordMustang.png'),(5,'Honda','Fit',NULL,NULL,18032,_binary '\0',2,'HondaFit.png'),(6,'Toyota','Corolla',NULL,'2025-06-14',15848,_binary '',1,'ToyotaCorolla.png'),(7,'Honda','CR-V',NULL,NULL,25962,_binary '\0',2,'HondaCR-V.png'),(8,'Ford','Mustang',NULL,NULL,10570,_binary '\0',2,'FordMustang.png'),(9,'Ford','F-150',NULL,NULL,13907,_binary '\0',2,'FordF-150.png'),(10,'BMW','X3',NULL,NULL,14432,_binary '\0',2,'BMWX3.png'),(11,'BMW','X5',NULL,NULL,17946,_binary '\0',2,'BMWX5.png'),(12,'Honda','CR-V',NULL,'2025-06-28',12354,_binary '',1,'HondaCR-V.png'),(13,'BMW','5Series',NULL,NULL,21316,_binary '\0',2,'BMW5Series.png'),(14,'BMW','X5',NULL,NULL,17702,_binary '\0',2,'BMWX5.png'),(15,'Ford','Focus',NULL,NULL,18024,_binary '\0',1,'FordFocus.png'),(16,'BMW','5Series',NULL,NULL,27922,_binary '\0',2,'BMW5Series.png'),(17,'Ford','F-150',NULL,'2025-06-28',20612,_binary '',2,'FordF-150.png'),(18,'Honda','Pilot',NULL,NULL,12899,_binary '\0',2,'HondaPilot.png'),(19,'Ford','Mustang',NULL,'2025-06-28',29403,_binary '',2,'FordMustang.png'),(20,'Ford','Escape',NULL,NULL,19678,_binary '\0',2,'FordEscape.png'),(21,'Ford','Explorer',NULL,'2025-06-14',11374,_binary '',2,'FordExplorer.png'),(22,'Ford','Escape',NULL,'2025-06-14',12497,_binary '',1,'FordEscape.png'),(23,'Ford','Focus',NULL,NULL,15020,_binary '\0',2,'FordFocus.png'),(24,'Honda','Fit',NULL,NULL,20246,_binary '\0',1,'HondaFit.png'),(25,'Ford','Explorer',NULL,NULL,24454,_binary '\0',1,'FordExplorer.png'),(26,'Honda','Accord',NULL,NULL,15841,_binary '\0',2,'HondaAccord.png'),(27,'Toyota','RAV4',NULL,NULL,23596,_binary '\0',2,'ToyotaRAV4.png'),(28,'Ford','Escape',NULL,NULL,18602,_binary '\0',2,'FordEscape.png'),(29,'Ford','Explorer',NULL,'2025-06-28',10176,_binary '',1,'FordExplorer.png'),(30,'Toyota','RAV4',NULL,NULL,21449,_binary '\0',2,'ToyotaRAV4.png'),(31,'BMW','E60',NULL,NULL,26793,_binary '\0',2,'BMWE60.png'),(32,'Ford','Mustang',NULL,NULL,27832,_binary '\0',1,'FordMustang.png'),(33,'Honda','Accord',NULL,NULL,26377,_binary '\0',1,'HondaAccord.png'),(34,'BMW','X3',NULL,NULL,25486,_binary '\0',1,'BMWX3.png'),(35,'Toyota','Corolla',NULL,NULL,29355,_binary '\0',2,'ToyotaCorolla.png'),(36,'Ford','Mustang',NULL,NULL,24797,_binary '\0',2,'FordMustang.png'),(37,'BMW','X5',NULL,NULL,16223,_binary '\0',2,'BMWX5.png'),(38,'Honda','Accord',NULL,NULL,15899,_binary '\0',2,'HondaAccord.png'),(39,'Ford','Escape',NULL,'2025-06-28',27817,_binary '',1,'FordEscape.png'),(40,'Ford','Escape',NULL,NULL,16261,_binary '\0',1,'FordEscape.png'),(41,'Honda','Pilot',NULL,NULL,17820,_binary '\0',2,'HondaPilot.png');
/*!40000 ALTER TABLE `vehicles` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-06-14 11:29:39
