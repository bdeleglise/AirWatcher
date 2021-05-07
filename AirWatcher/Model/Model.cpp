#include "Model.h"




// M�thodes publiques 



///////////////////////////////////////////////////////////////////////////////////////////////////////////////

GovernmentAgency Model::SearchGovernmentAgency(int id) {
	vector<GovernmentAgency>::iterator iter;
	GovernmentAgency toFind;

	for (iter = governmentAgencies.begin(); iter != governmentAgencies.end(); iter++) {
		if (iter->GetID() == id) {
			toFind = *iter;
		}
	}

	return(toFind);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

IndividualUser Model::SearchIndividual(int id) {
	vector<IndividualUser>::iterator iter;
	IndividualUser toFind;

	for (iter = individuals.begin(); iter != individuals.end(); iter++) {
		if (iter->GetID() == id) {
			toFind = *iter;
		}
	}

	return(toFind);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Provider Model::SearchProvider(int id) {
	vector<Provider>::iterator iter;
	Provider toFind;

	for (iter = providers.begin(); iter != providers.end(); iter++) {
		if (iter->GetID() == id) {
			toFind = *iter;
		}
	}

	return(toFind);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////


Cleaner Model::SearchCleaner(int id) {
	vector<Cleaner>::iterator iter;
	Cleaner toFind;

	for (iter = cleaners.begin(); iter != cleaners.end(); iter++) {
		if (iter->GetID() == id) {
			toFind = *iter;
		}
	}

	return(toFind);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sensor Model::SearchSensor(int id) {
	vector<Sensor>::iterator iter;
	Sensor toFind;

	for (iter = sensors.begin(); iter != sensors.end(); iter++) {
		if (iter->GetID() == id) {
			toFind = *iter;
		}
	}

	return(toFind);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sensor* Model::GetSensors() {
	Sensor* sensorsArray;
	sensorsArray = &sensors[0];
	return sensorsArray;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sensor* Model::GetPrivateSensors() {
	Sensor* sensorsArray;
	sensorsArray = &privateSensors[0];
	return sensorsArray;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

IndividualUser* Model::GetIndividuals() {
	IndividualUser* individualUserArray;
	individualUserArray = &individuals[0];
	return(individualUserArray);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sensor* Model::GetMaintenanceSensors() {
	Sensor* maintenanceSensorArray;
	maintenanceSensorArray = &maintenanceSensors[0];
	return(maintenanceSensorArray);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////


Provider* Model::GetProviders() {
	Provider* providerArray;
	providerArray = &providers[0];
	return(providerArray);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Cleaner* Model::GetCleaners() {
	Cleaner* cleanerArray;
	cleanerArray = &cleaners[0];
	return(cleanerArray);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sensor* Model::GetMaliciousIndividualSensors() {
	Sensor* maliciousIndividualSensorsArray;
	maliciousIndividualSensorsArray = &maliciousSensors[0];
	return(maliciousIndividualSensorsArray);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool sortByValue( const pair<Sensor,int> &a, const pair<Sensor,int> &b){
      return (a.second < b.second);
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<pair<Sensor,int>> Model::GetSensorsOrderByDistance(float latitude, float longitude) {
	Sensor* sensorArray = GetSensors();
	vector<pair<Sensor,int>> SensorsOrderedByDistance;
	float distance;
	int tabLength = sizeof(sensorArray) / sizeof(sensorArray[0]);
	for(int i=0;i<tabLength;i++){
		distance = sqrt(pow(sensorArray[i].GetLatitude()-latitude,2)+pow(sensorArray[i].GetLongitude()-longitude,2));
		SensorsOrderedByDistance.push_back(make_pair(sensorArray[i], distance));
	}
	sort(SensorsOrderedByDistance.begin(), SensorsOrderedByDistance.end(),sortByValue);
	return(SensorsOrderedByDistance);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<pair<Sensor,int>> Model::GetPrivateSensorsOrderByDistance(float latitude, float longitude){
	Sensor* privateSensorArray = GetPrivateSensors();
	vector<pair<Sensor,int>> privateSensorsOrderedByDistance;
	float distance;
	int tabLength = sizeof(privateSensorArray) / sizeof(privateSensorArray[0]);

	for(int i=0;i<tabLength;i++){
		distance = sqrt(pow(privateSensorArray[i].GetLatitude()-latitude,2)+pow(privateSensorArray[i].GetLongitude()-longitude,2));
		privateSensorsOrderedByDistance.push_back(make_pair(privateSensorArray[i], distance));
	}
	sort(privateSensorsOrderedByDistance.begin(),privateSensorsOrderedByDistance.end(),sortByValue);
	return(privateSensorsOrderedByDistance);
}


//////////////

void Model::IncrementPointIndividualUser(int idIndividual) {
	vector<IndividualUser>::iterator iter;
	for (iter = individuals.begin(); iter != individuals.end(); iter++) {
		if (iter->GetID() == idIndividual) {
			iter->SetPoints(iter->GetPoints() + 1);
		}
	}
}


/////////////////

int Model::UpdateSensorState(int idSensor) {

	Sensor* privateSensorsArray;
	privateSensorsArray = GetPrivateSensors();
	int tabLength = sizeof(privateSensorArray) / sizeof(privateSensorArray[0]);

	for (int i=0; i<tabLength; i++){
		
	}

	vector<Sensor>::iterator iter;
	for (iter = sensors.begin(); iter != sensors.end(); iter++) {
		if (iter->GetID() == id) {
			
		}
	}
}