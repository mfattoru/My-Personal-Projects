CREATE DATABASE  IF NOT EXISTS `Agenda` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `Agenda`;
-- MySQL dump 10.13  Distrib 5.5.28, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: Agenda
-- ------------------------------------------------------
-- Server version	5.5.28-0ubuntu0.12.04.3

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Rubrica`
--

DROP TABLE IF EXISTS `Rubrica`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Rubrica` (
  `Proprietario` varchar(45) NOT NULL,
  `Nome` varchar(45) DEFAULT NULL,
  `Cognome` varchar(45) DEFAULT NULL,
  `Indirizzo` varchar(45) DEFAULT NULL,
  `Email` varchar(45) NOT NULL,
  `Telefono` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`Proprietario`,`Email`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Rubrica`
--

LOCK TABLES `Rubrica` WRITE;
/*!40000 ALTER TABLE `Rubrica` DISABLE KEYS */;
INSERT INTO `Rubrica` VALUES ('Ferdinand','marco','grazioso','via plinio 209','mar.grazioso@libero.it','3337888123'),('gigi','ciro','Esposito','via mezzocannone 30','merdaccia20@hotmail.it','5678111111'),('kollins','michele','fattoruso','via san nicola del vaglio 4','juventino990@hotmail.it','3337888123'),('kollins','gigi','bove','via carminiello 46','luig.bove@gmail.com','3367899990'),('michelef','Anita','Alicante','via cinthia 50','anita.alicante@unina.it','1234567890'),('michelef','ernesto','esposito','via fasulo 12','ernesto@hotmail.com','3333333333'),('michelef','Antonio','Rispettoso','via nullo 21','hahaha@gmail.com','3337888002');
/*!40000 ALTER TABLE `Rubrica` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-01-12 21:32:32
