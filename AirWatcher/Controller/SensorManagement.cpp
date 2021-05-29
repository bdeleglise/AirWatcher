#include "SensorManagement.h"
#include <fstream>
#include <string>
#include "../Controller/System.h"
#include <iostream>
#include <vector>

#include "../Model/Entity/User.h"
#include "../Model/Entity/IndividualUser.h"

#include "../Controller/Statistics.h"

SensorManagement::SensorManagement(Model* unModel) : model(unModel)
{
}

vector<pair<Sensor, double>> SensorManagement::FraudulentSensorDetection() {
	Statistics stats(model);

	map<int, Sensor>* privateSensors;
	privateSensors = model->GetPrivateSensors();

	//map<int, Sensor>::iterator iter;
	
	double atmoCourant;
	double atmoAlentourMoyen;
	vector<pair<Sensor, double>>* neighbors;
	vector<pair<Sensor, double>>::iterator mapIter;

	vector<pair<Sensor, double>> falseSensors;

	for (auto & pair : *privateSensors)
	//Boucle sur chaque capteur détenu par un individu privé
	{
		//On récupère la valeur de l'indice atmo renvoyé par le capteur
		atmoCourant = stats.AirQualitySensor(&(pair.second));
		atmoAlentourMoyen = 0;
		//On récupère la liste des voisins de ce capteur, triée par distance croissante
		neighbors = model->GetSensorsOrderByDistance(pair.second.GetLatitude(), pair.second.GetLongitude());
		//On prend en compte les 3 plus proches voisins pour le calcul de l'indice atmo alentour moyen
		//Attention a ne pas prendre comme premier neighbors->begin() qui est le capteur lui même avec utilisation de la methode GetSensorsOrderByDistance
		mapIter = neighbors->begin();
		mapIter++;
		for (mapIter; mapIter != (neighbors->begin()) + 4;mapIter++) {
			atmoAlentourMoyen += stats.AirQualitySensor(&(mapIter->first));
		}
		atmoAlentourMoyen = atmoAlentourMoyen/3;
		if (abs(atmoCourant - atmoAlentourMoyen) > 0.1 * atmoAlentourMoyen)
		//Seuil d'acceptabilité : on considère un capteur frauduleux lorsque le pourcentage d'erreur
		//mesuré avec ses voisins dépasse 10%
		{
			falseSensors.push_back(make_pair(pair.second, (abs(atmoAlentourMoyen - atmoCourant) / atmoAlentourMoyen) * 100));
		}
	}
	return falseSensors;
}

bool SensorManagement::ClassifyAsUnreliable(int individualId) {


	Model model;
	IndividualUser* individualPtr = model.SearchIndividual(individualId);
	vector<Sensor>::iterator iter;
	//declaring a pointer of listSensors 
	vector<Sensor>* listSensors;
	
	if (individualPtr != nullptr) {
		listSensors = individualPtr->GetSensors();

		if (individualPtr->GetReliable()) {
			/*for (iter = listSensors->begin(); iter != listSensors->end(); iter++) {
				model.UpdateSensorState(iter->GetID());
			}*/
			model.UpdateIndividualState(individualId);
		}
		return(true);
	}
	else {
		return (false);
	}
	
}