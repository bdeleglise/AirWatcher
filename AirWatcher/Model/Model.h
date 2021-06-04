/*************************************************************************
						   Model  -  description
							 -------------------
	début                : 06/05/2021
	copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
	e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
						   benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/


#if ! defined (MODEL_H)
#define MODEL_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include "Entity/User.h"
#include "Entity/IndividualUser.h"
#include "Entity/GovernmentAgency.h"
#include "Entity/Provider.h"
#include "Entity/Cleaner.h"
#include "Entity/Sensor.h"
#include "../Util/ReaderConfig.h"
using namespace std;

const Config FILE_NAME;


//------------------------------------------------------------------------ 
// R�le de la classe <Model>
// Cette classe Model implémente toute la gestion des objets metiers et des interrations avec les 
// autres couches , elle a les méthodes SearchClass(id) pour chercher l'objet metier à partir de l'id
// elle a aussi les méthodes GetList() pour renvoyer la liste des objets sous forme de map
// elle lit aussi les données des differents fichiers csv et les stocke dans les objets metier 
// elle permet aussi de donner un point supplémentaire à l'utilisateur privé
// elle ermet de récupérer la liste des 4 capteurs (privés) triés selon leur distance croissante 
// aux coordonnées en paramètre du capteur 
// Cette classe contient comme attributs l'ensemble des listes des objets metiers résultant du lien avec 
// les classes entity, et ce sous forme de map
//
//------------------------------------------------------------------------ 


class Model {

public:

	GovernmentAgency* SearchGovernmentAgency(int id);
	/* Mode d'emploi:
		Permet de chercher un objet de la classe GovernmentAgency spécifié par son Id et de la renvoyer en sortie de la méthode.
		Pour les objets de type « user », si l’objet ne se trouve pas dans les listes,
		alors la méthode va interroger la base de données pour récupérer ses informations qu’elle sauvegardera dans un objet métier en cas de besoin jusqu’à la fin de l’utilisation de l’application.
	   Contrat:
		Aucun*/

	IndividualUser* SearchIndividual(int id);
	/* Mode d'emploi:
		Même usage que pour la méthode SearchGovernmentAgency mais pour un objet de type IndividualUser
	   Contrat:
		Aucun*/

	Provider* SearchProvider(int id);
	/* Mode d'emploi:
		Même usage que pour la méthode SearchGovernmentAgency mais pour un objet de type Provider
	   Contrat:
		Aucun*/

	Cleaner* SearchCleaner(int id);
	/* Mode d'emploi:
		Même usage que pour la méthode SearchGovernmentAgency mais pour un objet de type Cleaner
	   Contrat:
		Aucun*/

	Sensor* SearchSensor(int id);
	/* Mode d'emploi:
		Même usage que pour la méthode SearchGovernmentAgency mais pour un objet de type Sensor
	   Contrat:
		Aucun*/

	map<int, Sensor>* GetSensors();
	/* Mode d'emploi:
		La méthode GetSensors permet de retourner la liste des sensors pour permettre leur affichage côté interface
	   Contrat:
		Aucun*/

	map<int, Sensor>* GetPrivateSensors();
	/* Mode d'emploi:
		La méthode GetPrivateSensors permet de retourner la liste des private sensors pour permettre leur affichage côté interface
	   Contrat:
		Aucun*/

	map<int, IndividualUser>* GetIndividuals();
	/* Mode d'emploi:
		La méthode GetIndividuals permet de retourner la liste des IndividualUSers pour permettre leur affichage côté interface
	   Contrat:
		Aucun*/

	map<int, Sensor>* GetMaintenanceSensors();
	/* Mode d'emploi:
		La méthode GetMaintenanceSensors permet de retourner la liste des sensors en maintenance pour permettre leur affichage côté interface
	   Contrat:
		Aucun*/

	map<int, Provider>* GetProviders();
	/* Mode d'emploi:
		La méthode GetProvider permet de retourner la liste des providers pour permettre leur affichage côté interface
	   Contrat:
		Aucun*/

	map<int, Cleaner>* GetCleaners();
	/* Mode d'emploi:
		La méthode GetCleaners permet de retourner la liste des cleaners pour permettre leur affichage côté interface
	   Contrat:
		Aucun*/

	map<int, Sensor>* GetMaliciousIndividualSensors();
	/* Mode d'emploi:
		La méthode GetMaliciousIndividualSensors permet de retourner la liste des sensors appartenant à des Individuals frauduleux pour permettre leur affichage côté interface
	   Contrat:
		Aucun*/

	vector<Sensor*>* GetSensorsOrderByDistance(double latitude, double longitude);
	/* Mode d'emploi:
		La méthode GetSensorsOrderByDistance permet de récupérer la liste des 4 capteurs triés selon leur distance croissante aux coordonnées en paramètre.
	   Contrat:
		Aucun*/

	vector<pair<Sensor,double>>* GetPrivateSensorsOrderByDistance(double latitude, double longitude);
	/* Mode d'emploi:
		La méthode GetPrivateSensorsOrderByDistance permet de récupérer la liste des capteurs privés triés selon leur distance croissante aux coordonnées en paramètre.
	   Contrat:
		Aucun*/

	int LoadData();
	/* Mode d'emploi:
		La méthode LoadData permet de lire les données des différents fichiers spécifiés dans la structure config et de les stocker dans les objets métier pendant la durée de vie de l’application.
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


	Model();

protected:

	map<int, GovernmentAgency> governmentAgencies;
	map<int, Cleaner> cleaners;
	map<int, IndividualUser> individuals;
	map<int, Sensor> sensors;
	map<int, Sensor> maintenanceSensors;
	map<int, Sensor> privateSensors;
	map<int, Sensor> maliciousSensors;
	map<int, Provider> providers;

};
#endif
