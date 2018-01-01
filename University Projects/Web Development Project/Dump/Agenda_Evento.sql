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
-- Table structure for table `Evento`
--

DROP TABLE IF EXISTS `Evento`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Evento` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Nome` varchar(45) NOT NULL,
  `OraInizio` time NOT NULL,
  `Data` date NOT NULL,
  `Descrizione` varchar(500) DEFAULT NULL,
  `Luogo` varchar(45) NOT NULL,
  `OraFine` time DEFAULT NULL,
  `Proprietario` varchar(45) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=60 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Evento`
--

LOCK TABLES `Evento` WRITE;
/*!40000 ALTER TABLE `Evento` DISABLE KEYS */;
INSERT INTO `Evento` VALUES (36,'Riunione','20:00:00','2013-01-04','Riunione Di Lavoro','Via Cinthia 20','22:00:00','michelef'),(37,'Visita Medica','17:00:00','2013-01-06','Visita medica mensile','Santa Maria la Carità NA, Italia','18:00:00','michelef'),(38,'Pizza Con Gli Amici','18:00:00','2013-01-05','Finalmente Incontro I miei vecchi amici','Boscotrecase NA','20:00:00','michelef'),(49,'Appuntamento con la ragazza','18:00:00','2013-01-10','','80050 San Nicola NA, Italia','20:00:00','Ferdinand'),(50,'Andare all\'aereoporto','18:00:00','2013-01-16','andare a prendere mio fratelo all\'aereoporto','80050 San Nicola NA, Italia','20:00:00','Ferdinand'),(51,'Pagamento Tasse','19:00:00','2013-01-18','Compilare i bollettini e andare a pagare le tasse','Italia','20:00:00','gigi'),(52,'caffè con il capo','19:00:00','2013-01-22','','Italia','20:00:00','gigi'),(59,'caffè con un amico','20:00:00','2013-01-30','','castellammare di stabia','22:00:00','kollins');
/*!40000 ALTER TABLE `Evento` ENABLE KEYS */;
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
