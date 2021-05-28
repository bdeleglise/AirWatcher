#include "SensorManagement.h"
#include <fstream>
#include <string>
#include "../Controller/System.h"
#include <iostream>
#include <vector>

#include "../Model/Entity/User.h"
#include "../Model/Entity/IndividualUser.h"

#include "../Controller/Statistics.h"

vector<pair<Sensor, int>> SensorManagement::FraudulentSensorDetection() {
	Model model;
	Statistics stats;

	vector<Sensor>* privateSensors;
	privateSensors = model.GetPrivateSensors();

	vector<Sensor>::iterator iter;

	double atmoCourant;
	double atmoAlentourMoyen;
	vector<pair<Sensor, double>>* neighbors;

	for (iter = privateSensors->begin(); iter != privateSensors->end(); iter++) {
		// idk if the parameter of AirQualitySensor is correct (ie &(*iter))?
		atmoCourant = stats.AirQualitySensor(&(*iter));
		atmoAlentourMoyen = 0;
		neighbors = model.GetPrivateSensorsOrderByDistance(iter->GetLatitude(), iter->GetLongitude());

		// j=0 will be the sensor we study 
		for (int j = 1; j <= 3; j++) {
			atmoAlentourMoyen += stats.AirQualitySensor(neighbors)
		}
	}




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
			for (iter = listSensors->begin(); iter != listSensors->end(); iter++) {
				model.UpdateSensorState(iter->GetID());
			}
			model.UpdateIndividualState(individualId);
		}
		return(true);
	}
	else {
		return (false);
	}
	
}