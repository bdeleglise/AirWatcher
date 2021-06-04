/*************************************************************************
						   SensorManegement  -  description
							 -------------------
	début                : 06/05/2021
	copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
	e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
						   benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/

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

vector<pair<Sensor*, Confidence>>* SensorManagement::FraudulentSensorDetection()
//Algorithme : 
{
	Statistics stats(model);

	map<int, Sensor>* privateSensors;
	privateSensors = model->GetPrivateSensors();

	
	
	double atmoCourant;
	double atmoAlentourMoyen;
	double atmoNeigbors[3];
	vector<Sensor*>* neighbors;
	vector<Sensor*>::iterator mapIter;

	vector<pair<Sensor*, Confidence>>* falseSensors = new vector<pair<Sensor*, Confidence>>;

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
		int index = 0;
		// on calcule l'indice ATMO moyen pour les voisins du capteur parcouru
		for (mapIter; mapIter != (neighbors->begin()) + 4;mapIter++) {
			atmoNeigbors[index]= stats.AirQualitySensor(*mapIter);
			atmoAlentourMoyen += atmoNeigbors[index];
			index++;
		}
		atmoAlentourMoyen = atmoAlentourMoyen/3;
		// on calcule l'écart type de ATMO
		double atmoEcratType = sqrt((pow(atmoNeigbors[0] - atmoAlentourMoyen, 2) + pow(atmoNeigbors[1] - atmoAlentourMoyen, 2) + pow(atmoNeigbors[2] - atmoAlentourMoyen, 2)) / 3);
		// on calcule le coeffitient de confiance 
		double trust = atmoEcratType / sqrt(3);
		// on met à jour falseSensors en donnant le % de chance que le capteur soit frauduleux 
		// et ce en se bansant sur la loi de l'intervalle de confiance 
		if (abs(atmoCourant - atmoAlentourMoyen) > 3*trust)
		{
			falseSensors->push_back(make_pair(&pair.second, make_pair(99.7,(abs(atmoAlentourMoyen - atmoCourant) / atmoAlentourMoyen) * 100)));
		}
		else if (abs(atmoCourant - atmoAlentourMoyen) > 2 * trust)
		{
			falseSensors->push_back(make_pair(&pair.second, make_pair(95, (abs(atmoAlentourMoyen - atmoCourant) / atmoAlentourMoyen) * 100)));
		}
		else if (abs(atmoCourant - atmoAlentourMoyen) > 1.645 * trust)
		{
			falseSensors->push_back(make_pair(&(pair.second), make_pair(90, (abs(atmoAlentourMoyen - atmoCourant) / atmoAlentourMoyen) * 100)));
		}
	}
	return falseSensors;
}

bool SensorManagement::ClassifyAsUnreliable(int individualId)
//Algorithme : on récupère l'individu associé à l'id en paramètre et s'il est dans la liste des fiables, on met à jour son statut comme non fiable.
{

	IndividualUser* individualPtr = model->SearchIndividual(individualId);
	
	if (individualPtr != nullptr && individualPtr->GetReliable()) {
		model->UpdateIndividualState(individualId);
		return(true);
	}
	else {
		return (false);
	}
	
}