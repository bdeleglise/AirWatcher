#pragma once
#include <ctime>
#include "../Model/Entity/Sensor.h"
#include "../Model/Model.h"
class Statistics
{
public :
	int CircularMeanAirQuality(double latitude, double longitude, double radius, time_t* time=nullptr);

	// Mode d'emploi :
	// permet de calculer la qualit� de l�air selon l�index ATMO dans une zone g�ographique particuli�re (param�tres Latitude, Longitude, radius) � un instant pr�cis (param�tre time=nullptr). Toutes les interfaces ont acc�s � cette m�thode.  
	// Contrat :
	// Aucun

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

