/*************************************************************************
						   Statistics  -  description
							 -------------------
	d�but                : 06/05/2021
	copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
	e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
						   benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/


#pragma once
#include <ctime>
#include "../Model/Entity/Sensor.h"
#include "../Model/Model.h"

// Role de classe <Statistics>
// Cette classe appartient � la couche Controlleur du modele MVC, elle g�re les calculs des qualit�s de l'air 
// sur une zone particuli�re � u_n instant pr�cis, ou sur la derni�re semaine 
// Elle permet aussi de calculer l indice ATMO de la qualit� de l'air 


class Statistics
{
public :
	int CircularMeanAirQuality(double latitude, double longitude, double radius, time_t* time=nullptr);

	// Mode d'emploi :
	// permet de calculer la qualit� de l�air selon l�index ATMO dans une zone g�ographique particuli�re (param�tres Latitude, Longitude, radius) � un instant pr�cis (param�tre time=nullptr). Toutes les interfaces ont acc�s � cette m�thode.
	// le rayon, la latitude et la longitude sont en degr�  
	// Contrat :
	// On fait l�approximation qu�on peut ramener les valeurs angulaires de la latitude et de la longitude � des valeurs cart�siennes car on reste sur le territoire de l�agence gouvernementale Fran�aise.
	// On fait donc l�hypoth�se que le r�f�rentiel est plat

	double AirQualitySensor(Sensor* sensor, time_t* end = nullptr);

	// Mode d'emploi :
	// permet de r�cup�rer la qualit� de l�air sur la derni�re semaine si l�attribut est nul du capteur en param�tre.  
	// Contrat :
	// Aucun

	Statistics(Model* unModel);

private :
	int atmoIndex(double O3, double So2, double No2, double Pm10);

	// Mode d'emploi :
	// permet de calculer l��indice ATMO de la qualit� de l�air selon la nouvelle �chelle de valeur 
	// Contrat :
	// ne peut �tre utilis�e que dans la classe Statistics.

	Model* model;
};

