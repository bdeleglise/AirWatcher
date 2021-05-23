#include "Model.h"
#include <fstream>
#include <string>
#include "../Controller/System.h"


// M�thodes publiques 

vector<GovernmentAgency> Model::governmentAgencies = {};
vector<Cleaner> Model::cleaners = {};
vector<IndividualUser> Model::individuals = {};
vector<Sensor> Model::sensors = {};
vector<Sensor> Model::maintenanceSensors = {};
vector<Sensor> Model::privateSensors = {};
vector<Sensor> Model::maliciousSensors = {};
vector<Provider> Model::providers = {};

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

	bool testSort(Sensor& a, Sensor& b, double latitude, double longitude) {
		double da = pow(latitude - a.GetLatitude(), 2) + pow(longitude - a.GetLongitude(), 2);
		double db = pow(latitude - b.GetLatitude(), 2) + pow(longitude - b.GetLongitude(), 2);
		return (da < db);
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<pair<Sensor, double>>* Model::GetSensorsOrderByDistance(double latitude, double longitude) {
	vector<pair<Sensor, double>>* SensorsOrderedByDistance = new vector<pair<Sensor, double>>;
	double distance;
	vector<Sensor>::iterator iter;
	for (iter = sensors.begin(); iter != sensors.end(); ++iter) {
		distance = sqrt(pow(latitude-iter->GetLatitude(),2)+pow(longitude-iter->GetLongitude(),2));
		SensorsOrderedByDistance->push_back(make_pair(*iter, distance));
	}

	partial_sort(SensorsOrderedByDistance->begin(), SensorsOrderedByDistance->begin()+ SensorsOrderedByDistance->size()/2,SensorsOrderedByDistance->end(),sortByValue);
	

	return SensorsOrderedByDistance;
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
	


	//lecture des attributs --------------------------------------------------------
	ifstream file;
	file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.ATTRIBUTESFILE);
	cout << "Loading of attributs" << endl;
	
	map<string, Attribute> bufferAttributes;

	if (!file) {
		cerr << FILE_NAME.DIRECTORYPATH + FILE_NAME.ATTRIBUTESFILE << " n'existe pas" << endl;
		return 1;   //le fichier n'existe pas
	}

	string buffer;
	getline(file, buffer);  //Ligne de description

	while (getline(file, buffer, ';')) {
		//lecture au format csv
		string attributeID = buffer;
		getline(file, buffer, ';');
		string unit = buffer;
		getline(file, buffer, ';');
		string description = buffer;
		file.ignore(); //ignorer le \n

		bufferAttributes[attributeID] = Attribute(attributeID, unit, description);
	}
	file.close();
	
	//lecture des mesures --------------------------------------------------------------------------
	file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.MEASUREMENTSFILE);
	cout << "Loading of measurements" << endl;
	map<int, vector<Measurement>> bufferMeasurement;

	if (!file) {
		cerr << FILE_NAME.DIRECTORYPATH + FILE_NAME.MEASUREMENTSFILE << " n'existe pas" << endl;
		return 1;
	}
	
	while (getline(file, buffer, ';')) { //lecture au format csv
		tm* tmp = new tm();
		tmp->tm_year = stoi(buffer.substr(0, 4))-1900;
		tmp->tm_mon = stoi(buffer.substr(5, 2)) - 1;
		tmp->tm_mday = stoi(buffer.substr(8, 2));
		tmp->tm_hour = stoi(buffer.substr(11, 2));
		tmp->tm_min = stoi(buffer.substr(14, 2));
		tmp->tm_sec = stoi(buffer.substr(17, 2));
		time_t timestamp = mktime(tmp);
		delete tmp;
		getline(file, buffer, ';');
		int sensorID = stoi(buffer.substr(6));
		getline(file, buffer, ';');
		Attribute attribute = bufferAttributes[buffer];
		getline(file, buffer, ';');
		double value = stod(buffer);
		file.ignore(); //ignorer le \n
		
		bufferMeasurement[sensorID].push_back(Measurement(timestamp, value, attribute));
	}
	file.close();
	//lecture des cleaner --------------------------------------------------------------------------
	file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.CLEANERSFILE);
	cout << "Loading of cleaners" << endl;
	map<int, Cleaner> bufferCleaner;

	if (!file) {
		cerr << FILE_NAME.DIRECTORYPATH + FILE_NAME.CLEANERSFILE << " n'existe pas" << endl;
		return 1;
	} 

	
	while (getline(file, buffer, ';')) {
		int cleanerID = stoi(buffer.substr(7));
		getline(file, buffer, ';');
		double latitude = stod(buffer);
		getline(file, buffer, ';');
		double longitude = stod(buffer);

		getline(file, buffer, ';');
		tm* tmp = new tm();
		tmp->tm_year = stoi(buffer.substr(0, 4)) - 1900;
		tmp->tm_mon = stoi(buffer.substr(5, 2)) - 1;
		tmp->tm_mday = stoi(buffer.substr(8, 2));
		tmp->tm_hour = stoi(buffer.substr(11, 2));
		tmp->tm_min = stoi(buffer.substr(14, 2));
		tmp->tm_sec = stoi(buffer.substr(17, 2));
		time_t start = mktime(tmp);
		delete tmp;
		getline(file, buffer, ';');
		tmp = new tm();
		tmp->tm_year = stoi(buffer.substr(0, 4)) - 1900;
		tmp->tm_mon = stoi(buffer.substr(5, 2)) - 1;
		tmp->tm_mday = stoi(buffer.substr(8, 2));
		tmp->tm_hour = stoi(buffer.substr(11, 2));
		tmp->tm_min = stoi(buffer.substr(14, 2));
		tmp->tm_sec = stoi(buffer.substr(17, 2));
		time_t end = mktime(tmp);
		delete tmp;
		file.ignore(); //ignorer le \n
		
		bufferCleaner[cleanerID] = Cleaner(cleanerID, -1, latitude, longitude, start, end);
	}
	
	file.close();

	//lecture des providers --------------------------------------------------------------------------
	file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.PROVIDERSFILE);
	cout << "Loading of providers" << endl;
	map<int, Provider> bufferProvider;
	map<int, Provider>::iterator it;
	map<int, Cleaner>::iterator itCleaner;
	if (!file) {
		cerr << FILE_NAME.DIRECTORYPATH + FILE_NAME.PROVIDERSFILE << " n'existe pas" << endl;
		return 1;
	}

	while (getline(file, buffer, ';')) {
		int providerID = stoi(buffer.substr(8));
		getline(file, buffer, ';');
		int cleanerID = stoi(buffer.substr(7));
		file.ignore(); //ignorer le \n

		itCleaner= bufferCleaner.find(cleanerID);
		if (itCleaner == bufferCleaner.end()) {
			return 2; //erreur de lecture
		}
		itCleaner->second.SetProviderID(providerID);
		it = bufferProvider.find(providerID);
		if (it!= bufferProvider.end()) {
			it->second.AddCleaner(itCleaner->second);
		}
		else {
			bufferProvider[providerID] = Provider(providerID, itCleaner->second);
		}
		cleaners.push_back(itCleaner->second);
	}
	file.close();
	for (it = bufferProvider.begin(); it != bufferProvider.end(); ++it) {
		providers.push_back(it->second);
	}

	//lecture des sensors --------------------------------------------------------------------------
	file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.SENSORFILE);
	cout << "Loading of sensors" << endl;
	map<int, Sensor> bufferSensor;
	map<int, vector<Measurement>>::iterator itMeasure;
	if (!file) {
		cerr << FILE_NAME.DIRECTORYPATH + FILE_NAME.SENSORFILE << " n'existe pas" << endl;
		return 1;
	}

	while (getline(file, buffer, ';')) {
		int sensorID = stoi(buffer.substr(6));
		getline(file, buffer, ';');
		double latitude = stod(buffer);
		getline(file, buffer, ';');
		double longitude = stod(buffer);
		file.ignore(); //ignorer le \n

		Sensor sensor(sensorID, latitude, longitude);
		itMeasure = bufferMeasurement.find(sensorID);
		if (itMeasure != bufferMeasurement.end()) {
			vector<Measurement>::iterator itM;
			for (itM = itMeasure->second.begin(); itM != itMeasure->second.end(); ++itM) {
				sensor.AddMeasurement(*itM);
			}
		}
		bufferSensor[sensorID] = sensor;
	}
	file.close();
	
	//lecture des users --------------------------------------------------------------------------
	cout << "Loading of users" << endl;
	file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.USERSFILE);
	map<int, IndividualUser> bufferUser;
	map<int, IndividualUser>::iterator itUser;
	map<int, Sensor>::iterator itSensor;

	if (!file) {
		cerr << FILE_NAME.DIRECTORYPATH + FILE_NAME.USERSFILE << " n'existe pas" << endl;
		return 1;
	}

	while (getline(file, buffer, ';')) {
		int userID = stoi(buffer.substr(4));
		getline(file, buffer, ';');
		int sensorID = stoi(buffer.substr(6));
		file.ignore(); //ignorer le \n

		itSensor = bufferSensor.find(sensorID);
		if (itSensor == bufferSensor.end()) {
			return 2;
		}
		itSensor->second.SetUser(userID);
		itUser = bufferUser.find(userID);
		if (itUser != bufferUser.end()) {
			itUser->second.AddSensor(itSensor->second);
		}
		else {
			bufferUser[userID] = IndividualUser(userID,itSensor->second);
		}
		privateSensors.push_back(itSensor->second);
	}
	file.close();

	for (itUser = bufferUser.begin(); itUser != bufferUser.end(); ++itUser) {
		individuals.push_back(itUser->second);
	}
	for (itSensor = bufferSensor.begin(); itSensor != bufferSensor.end(); ++itSensor) {
		sensors.push_back(itSensor->second);
	}
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





void Model::UpdateSensorState(int idSensor) {
	
	vector<Sensor>* privateSensorsArray;
	privateSensorsArray = GetPrivateSensors();
	

	vector<Sensor>::iterator iter;
	Sensor* toFind = nullptr;
	vector<IndividualUser>::iterator iterUser;


	// First look if it's a private sensor 
	for (iter = privateSensors.begin(); iter != privateSensors.end(); iter++) {
		if (iter->GetID() == idSensor) {
			toFind = &(*iter);
		}
	}

	if (toFind != nullptr) {
		// add to list of malicious sensors
		maliciousSensors.push_back(*toFind);
		// erase from list of private sensors
		privateSensors.erase(iter);
		// dysfunction it
		toFind->SetState(false);
		// set its individual user as UnReliable
		// erase the sensor from its owner's sensors list 
		int userID = toFind->GetUserID();
		for (iterUser = individuals.begin(); iterUser != individuals.end(); iterUser++) {
			if (iterUser->GetID() == userID) {
				iterUser->SetReliable(false);
				iterUser->GetSensors()->erase(iter);
			}
		}
	} 

	// if not, then it's a government sensor
	else {
		for (iter = sensors.begin(); iter != sensors.end(); iter++) {
			if (iter->GetID() == idSensor) {
				toFind = &(*iter);
			}
		}

		if (toFind != nullptr) {
			// add it to list of maintenance srnsors 
			maintenanceSensors.push_back(*toFind);
			// dysfunction it
			toFind->SetState(false);
		}
	}
}



void Model::UpdateIndividualState(int idIndividual) {
	IndividualUser* individualPtr = SearchIndividual(idIndividual);
	vector<Sensor>::iterator iter;
	if (individualPtr != nullptr) {
		individualPtr->SetReliable(!individualPtr->GetReliable());
		bool reliable = individualPtr->GetReliable();
		// if the individual user is not reliable, then : 
		// move its sensors from privateSensors list to malicious
		if (!reliable) {
			for (iter = individualPtr->GetSensors()->begin(); iter != individualPtr->GetSensors()->end(); iter++) {
				maliciousSensors.push_back(*iter);
				privateSensors.erase(iter);
			}
		}
		// if not
		// move its sensors from malicious to private
		else {
			for (iter = maliciousSensors.begin(); iter != maliciousSensors.end(); iter++) {
				if (iter->GetUserID() == individualPtr->GetID()) {
					privateSensors.push_back(*iter);
					// erase it from the list we run through 
					maliciousSensors.erase(iter);
				}
			}
		}
	}
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

