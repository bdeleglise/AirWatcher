#pragma once
#include <ctime>
#include "../Model/Entity/Sensor.h"
#include "../Model/Model.h"
class Statistics
{
public :
	int CircularMeanAirQuality(double latitude, double longitude, double radius, time_t* time=nullptr);

	// Mode d'emploi :
	// permet de calculer la qualité de l’air selon l’index ATMO dans une zone géographique particulière (paramètres Latitude, Longitude, radius) à un instant précis (paramètre time=nullptr). Toutes les interfaces ont accès à cette méthode.  
	// Contrat :
	// Aucun

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

