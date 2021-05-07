﻿#if ! defined (MODEL_H)
#define MODEL_H

#include <iostream>
#include <vector>

class Model {

public:

	User SearchUser(int id);
	/* Mode d'emploi:
		Permet de chercher un objet de la classe User spécifié par son Id et de la renvoyer en sortie de la méthode.
		Pour les objets de type « user », si l’objet ne se trouve pas dans les listes,
		alors la méthode va interroger la base de données pour récupérer ses informations qu’elle sauvegardera dans un objet métier en cas de besoin jusqu’à la fin de l’utilisation de l’application.
	   Contrat:
		Aucun*/

	GovernmentAgency SearchGovernmentAgency(int id);
	/* Mode d'emploi:
		Même usage que pour la méthode SearchUser mais pour un objet de type GovernmentAgency
	   Contrat:
		Aucun*/

	IndividualUser SearchIndividual(int id);
	/* Mode d'emploi:
		Même usage que pour la méthode SearchUser mais pour un objet de type IndividualUser
	   Contrat:
		Aucun*/

	Provider SearchProvider(int id);
	/* Mode d'emploi:
		Même usage que pour la méthode SearchUser mais pour un objet de type Provider
	   Contrat:
		Aucun*/

	Cleaner SearchCleaner(int id);
	/* Mode d'emploi:
		Même usage que pour la méthode SearchUser mais pour un objet de type Cleaner
	   Contrat:
		Aucun*/

	Sensor SearchSensor(int id);
	/* Mode d'emploi:
		Même usage que pour la méthode SearchUser mais pour un objet de type Sensor
	   Contrat:
		Aucun*/

	Sensor* GetSensors();
	/* Mode d'emploi:
		La méthode GetSensors permet de retourner la liste des sensors pour permettre leur affichage côté interface
	   Contrat:
		Aucun*/

	Sensor* GetPrivateSensors();
	/* Mode d'emploi:
		La méthode GetPrivateSensors permet de retourner la liste des private sensors pour permettre leur affichage côté interface
	   Contrat:
		Aucun*/

	IndividualUser* GetIndividuals();
	/* Mode d'emploi:
		La méthode GetIndividuals permet de retourner la liste des IndividualUSers pour permettre leur affichage côté interface
	   Contrat:
		Aucun*/

	Sensor* GetMaintenanceSensors();
	/* Mode d'emploi:
		La méthode GetMaintenanceSensors permet de retourner la liste des sensors en maintenance pour permettre leur affichage côté interface
	   Contrat:
		Aucun*/

	Provider* GetProviders();
	/* Mode d'emploi:
		La méthode GetProvider permet de retourner la liste des providers pour permettre leur affichage côté interface
	   Contrat:
		Aucun*/

	Cleaner* GetCleaners();
	/* Mode d'emploi:
		La méthode GetCleaners permet de retourner la liste des cleaners pour permettre leur affichage côté interface
	   Contrat:
		Aucun*/

	Sensor* GetMaliciousIndividualSensors();
	/* Mode d'emploi:
		La méthode GetMaliciousIndividualSensors permet de retourner la liste des sensors appartenant à des Individuals frauduleux pour permettre leur affichage côté interface
	   Contrat:
		Aucun*/

	List<Sensor> GetSensorsOrderByDistance(float latitude, float longitude);
	/* Mode d'emploi:
		La méthode GetSensorsOrderByDistance permet de récupérer la liste des capteurs triés selon leur distance croissante aux coordonnées en paramètre.
	   Contrat:
		Aucun*/

	List<Sensor> GetPrivateSensorsOrderByDistance(float latitude, float longitude);
	/* Mode d'emploi:
		La méthode GetPrivateSensorsOrderByDistance permet de récupérer la liste des capteurs privés triés selon leur distance croissante aux coordonnées en paramètre.
	   Contrat:
		Aucun*/

	int LoadData();
	/* Mode d'emploi:
		La méthode LoadData permet de lire les données des différents fichiers spécifiés dans la structure config et de les stocker dans les objets métier pendant la durée de vie de l’application.
	   Contrat:
		Aucun*/

	boolean SaveDataOnDatabase();
	/* Mode d'emploi:
		La méthode SaveDataOnDatabase permet de sauvegarder la dernière version des données qui ont été chargées dans la base de données locales et de mettre à jour les profils utilisateurs qui auraient été modifiés pendant l’exécution de l’application.
	   Contrat:
		Aucun*/

	void IncrementPointIndividualUser(int idIndividual);
	/* Mode d'emploi:
		La méthode IncrementPointindividualUser permet de donner un point supplémentaire à l’utilisateur privé dont l’id est passé en paramètre.
	   Contrat:
		Aucun*/

	void UpdateSensorState(int idSensor);
	/* Mode d'emploi:
		La méthode UpdateSensorState permet de passer un capteur dont l’id est en paramètre en mode de fonctionnement ou de dysfonctionnement et donc en capteur fonctionnel, en capteur en réparation si le capteur appartient à l’agence ou en capteur malhonnête si le capteur appartient à un particulier.
	   Contrat:
		Aucun*/

	void UpdateIndividualState(int idIndividual);
	/* Mode d'emploi:
		La méthode UpdateIndividualState permet de changer l’état d’un utilisateur privé et de changer ses capteurs de liste.
	   Contrat:
		Aucun*/

	void UpdateProfileGovernmentAgency(GovernmentAgency NewProfile);
	/* Mode d'emploi:
		La méthode UpdateProfileGovernmentAgency permet de mettre à jour les informations du profil passé en paramètre.
	   Contrat:
		Aucun*/

	void UpdateProfileProvider(Provider NewProfile);
	/* Mode d'emploi:
		La méthode UpdateProfileProvider permet de mettre à jour les informations du profil passé en paramètre.
	   Contrat:
		Aucun*/

	void UpdateProfileIndividualUser(IndividualUser NewProfile);
	/* Mode d'emploi:
		La méthode UpdateProfileIndividualUser permet de mettre à jour les informations du profil passé en paramètre.
	   Contrat:
		Aucun*/





private:
	std::vector<GovernmentAgency> governmentAgencies;
	std::vector<Cleaner> cleaners;
	std::vector<IndividualUser> individuals;
	std::vector<Sensor> sensors;
	std::vector<Sensor> maintenanceSensors;
	std::vector<Sensor> privateSensors;
	std::vector<Sensor> maliciousSensors;
	std::vector<Provider> providers

};
