#include "Model.h"




// M�thodes publiques 

User Model::SearchUser(int id) {

	User toFind;
	/*bool found = false;

	for (int i=0; i<individuals.size(); i++){
		if (individuals[i]->individualUserID == id){
			toFind = individuals[i];
			found = true;
		}
	}*/

	vector<IndividualUser>::iterator iter;

	iter = find_if(individuals.begin(), individuals.end(), [id](const IndividualUser& user) -> bool {return user.individualUserID == id; })
		toFind = *iter;
	return toFind;


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

GovernmentAgency Model::SearchGovernmentAgency(int id) {
	vector<GovernmentAgency>::iterator iter;
	GovernmentAgency toFind;

	for (iter = governmentAgencies.begin(); iter != governmentAgencies.end(); iter++) {
		if (iter->governementAgencyID == id) {
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
		if (iter->individualUserID == id) {
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
		if (iter->providerID == id) {
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
		if (iter->cleanerID == id) {
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
		if (iter->sensorID == id) {
			toFind = *iter;
		}
	}

	return(toFind);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sensors* Model::GetSensor() {
	Sensors* sensorsArray;
	sensorsArray = &sensors[0];
	return sensorsArray;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sensor* Model::GetPrivateSensors() {
	Sensors* sensorsArray;
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

List<Sensor> Model::GetSensorsOrderByDistance(float latitude, float longitude) {

}

//////////////

void Model::IncrementPointIndividualUser(int idIndividual) {


	for (iter = individuals.begin(); iter != individuals.end(); iter++) {
		if (iter->individualUserID == id) {
			iter->setPoints(iter->GetPoints() + 1);
		}
	}

}


/////////////////

int Model::LoadData() {

}