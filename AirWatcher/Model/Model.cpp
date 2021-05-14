#include "Model.h"




// M�thodes publiques 



///////////////////////////////////////////////////////////////////////////////////////////////////////////////

GovernmentAgency* Model::SearchGovernmentAgency(int id) {
	vector<GovernmentAgency>::iterator iter;
	GovernmentAgency* toFind=nullptr;

	for (iter = governmentAgencies.begin(); iter != governmentAgencies.end(); iter++) {
		if (iter->GetID() == id) {
			toFind = &(*iter);
		}
	}

	return(toFind);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

IndividualUser* Model::SearchIndividual(int id) {
	vector<IndividualUser>::iterator iter;
	IndividualUser* toFind=nullptr;

	for (iter = individuals.begin(); iter != individuals.end(); iter++) {
		if (iter->GetID() == id) {
			toFind = &(*iter);
		}
	}

	return(toFind);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Provider* Model::SearchProvider(int id) {
	vector<Provider>::iterator iter;
	Provider* toFind=nullptr;

	for (iter = providers.begin(); iter != providers.end(); iter++) {
		if (iter->GetID() == id) {
			toFind = &(*iter);
		}
	}

	return(toFind);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////


Cleaner* Model::SearchCleaner(int id) {
	vector<Cleaner>::iterator iter;
	Cleaner* toFind=nullptr;

	for (iter = cleaners.begin(); iter != cleaners.end(); iter++) {
		if (iter->GetID() == id) {
			toFind = &(*iter);
		}
	}

	return(toFind);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sensor* Model::SearchSensor(int id) {
	vector<Sensor>::iterator iter;
	Sensor* toFind=nullptr;

	for (iter = sensors.begin(); iter != sensors.end(); iter++) {
		if (iter->GetID() == id) {
			toFind = &(*iter);
		}
	}
	if (toFind == nullptr) {
		for (iter = maliciousSensors.begin(); iter != maliciousSensors.end(); iter++) {
			if (iter->GetID() == id) {
				toFind = &(*iter);
			}
		}
	}
	if (toFind == nullptr) {
		for (iter = maintenanceSensors.begin(); iter != maintenanceSensors.end(); iter++) {
			if (iter->GetID() == id) {
				toFind = &(*iter);
			}
		}
	}

	return(toFind);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Sensor>* Model::GetSensors() {
	return &sensors;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Sensor>* Model::GetPrivateSensors() {
	return &privateSensors;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<IndividualUser>* Model::GetIndividuals() {
	return &individuals;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Sensor>* Model::GetMaintenanceSensors() {
	return &maintenanceSensors;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////


vector<Provider>* Model::GetProviders() {
	return &providers;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Cleaner>* Model::GetCleaners() {
	return &cleaners;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Sensor>* Model::GetMaliciousIndividualSensors() {
	return &maliciousSensors;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool sortByValue( const pair<Sensor, double> &a, const pair<Sensor, double> &b){
      return (a.second < b.second);
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<pair<Sensor, double>>* Model::GetSensorsOrderByDistance(double latitude, double longitude) {
	static vector<pair<Sensor, double>> SensorsOrderedByDistance;
	double distance;
	vector<Sensor>::iterator iter;
	for (iter = sensors.begin(); iter != sensors.end(); iter++) {
		distance = sqrt(pow(iter->GetLatitude()-latitude,2)+pow(iter->GetLongitude()-longitude,2));
		SensorsOrderedByDistance.push_back(make_pair(*iter, distance));
	}
	sort(SensorsOrderedByDistance.begin(), SensorsOrderedByDistance.end(),sortByValue);
	return &SensorsOrderedByDistance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<pair<Sensor, double>>* Model::GetPrivateSensorsOrderByDistance(double latitude, double longitude){
	static vector<pair<Sensor, double>> privateSensorsOrderedByDistance;
	double distance;
	vector<Sensor>::iterator iter;
	for (iter = privateSensors.begin(); iter != privateSensors.end(); iter++) {
		distance = sqrt(pow(iter->GetLatitude()-latitude,2)+pow(iter->GetLongitude()-longitude,2));
		privateSensorsOrderedByDistance.push_back(make_pair(*iter, distance));
	}
	sort(privateSensorsOrderedByDistance.begin(),privateSensorsOrderedByDistance.end(),sortByValue);
	return &privateSensorsOrderedByDistance;
}



int Model::LoadData()
{
	return 0;
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

Model::Model()
	:governmentAgencies(), cleaners(), individuals(), sensors(), maintenanceSensors(), privateSensors(), maliciousSensors(), providers()
{
}





/////////////////
// TODO : finir 
// Bien faire attention dans les updates les capteurs stockés dans les listes et ceux des individuals sont pas la même mais 
// des copies l'un de l'autre donc prévoir de mettre à jour pour les deux endroits 
//int Model::UpdateSensorState(int idSensor) {
//
//	Sensor* privateSensorsArray;
//	privateSensorsArray = GetPrivateSensors();
//	int tabLength = sizeof(privateSensorArray) / sizeof(privateSensorArray[0]);
//
//	for (int i=0; i<tabLength; i++){
//		
//	}
//
//	vector<Sensor>::iterator iter;
//	for (iter = sensors.begin(); iter != sensors.end(); iter++) {
//		if (iter->GetID() == id) {
//			
//		}
//	}
//}