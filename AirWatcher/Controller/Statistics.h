/*************************************************************************
						   Statistics  -  description
							 -------------------
	début                : 06/05/2021
	copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
	e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
						   benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/


#pragma once
#include <ctime>
#include "../Model/Entity/Sensor.h"
#include "../Model/Model.h"

// Role de classe <Statistics>
// Cette classe appartient à la couche Controlleur du modele MVC, elle gère les calculs des qualités de l'air 
// sur une zone particulière à u_n instant précis, ou sur la dernière semaine 
// Elle permet aussi de calculer l indice ATMO de la qualité de l'air 


class Statistics
{
public :
	int CircularMeanAirQuality(double latitude, double longitude, double radius, time_t* time=nullptr);

	// Mode d'emploi :
	// permet de calculer la qualité de l’air selon l’index ATMO dans une zone géographique particulière (paramètres Latitude, Longitude, radius) à un instant précis (paramètre time=nullptr). Toutes les interfaces ont accès à cette méthode.
	// le rayon, la latitude et la longitude sont en degré  
	// Contrat :
	// On fait l’approximation qu’on peut ramener les valeurs angulaires de la latitude et de la longitude à des valeurs cartésiennes car on reste sur le territoire de l’agence gouvernementale Française.
	// On fait donc l’hypothèse que le référentiel est plat

	double AirQualitySensor(Sensor* sensor, time_t* end = nullptr);

	// Mode d'emploi :
	// permet de récupérer la qualité de l’air sur la dernière semaine si l’attribut est nul du capteur en paramètre.  
	// Contrat :
	// Aucun

	Statistics(Model* unModel);

private :
	int atmoIndex(double O3, double So2, double No2, double Pm10);

	// Mode d'emploi :
	// permet de calculer l’’indice ATMO de la qualité de l’air selon la nouvelle échelle de valeur 
	// Contrat :
	// ne peut être utilisée que dans la classe Statistics.

	Model* model;
};

