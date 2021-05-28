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
		vector<Sensor>* nearSensors = new vector<Sensor>(3);
		vector<Sensor>* SensorsVector = new vector<Sensor>;
		map<Sensor>* sensors = GetSensors();

		map<Sensor>::iterator iter;
		for (iter = sensors->begin(); iter != sensors->end(); iter++) {
			SensorsVector->push_back(iter*);
		}

		vector<Sensor>::iterator it;

		partial_sort_copy(SensorsVector->begin(), SensorsVector->end(), nearSensors->begin(), nearSensors->end(), [latitude, longitude](Sensor& s1, Sensor& s2) {
			double d1 = pow(latitude - s1.GetLatitude(), 2) + pow(longitude - s1.GetLongitude(), 2);
			double d2 = pow(latitude - s2.GetLatitude(), 2) + pow(longitude - s2.GetLongitude(), 2);
			return (d1 < d2);
			});

		int index = 0;

		for (it = nearSensors->begin(); it != nearSensors->end(); ++it) {
			double distance = sqrt(pow(latitude - it->GetLatitude(), 2) + pow(longitude - it->GetLongitude(), 2)) - radius;
			SensorsOrderedByDistance->push_back(make_pair(*it, distance));
			index++;
		}

		return(SensorsOrderedByDistance);

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	vector<pair<Sensor, double>>* Model::GetPrivateSensorsOrderByDistance(double latitude, double longitude) {
		vector<pair<Sensor, double>>* privateSensorsOrderedByDistance = new vector<pair<Sensor, double>>;
		vector<Sensor>* nearSensors = new vector<Sensor>(3);
		vector<Sensor>* PrivateSensorsVector = new vector<Sensor>;
		map<Sensor>* privateSensors = GetPrivateSensors();

		map<Sensor>::iterator iter;
		for (iter = privateSensors->begin(); iter != privateSensors->end(); iter++) {
			PrivateSensorsVector->push_back(iter*);
		}
		vector<Sensor>::iterator it;

		partial_sort_copy(PrivateSensorsVector->begin(), PrivateSensorsVector->end(), nearSensors->begin(), nearSensors->end(), [latitude, longitude](Sensor& s1, Sensor& s2) {
			double d1 = pow(latitude - s1.GetLatitude(), 2) + pow(longitude - s1.GetLongitude(), 2);
			double d2 = pow(latitude - s2.GetLatitude(), 2) + pow(longitude - s2.GetLongitude(), 2);
			return (d1 < d2);
			});

		int index = 0;

		for (it = nearSensors->begin(); it != nearSensors->end(); ++it) {
			double distance = sqrt(pow(latitude - it->GetLatitude(), 2) + pow(longitude - it->GetLongitude(), 2)) - radius;
			privateSensorsOrderedByDistance->push_back(make_pair(*it, distance));
			index++;
		}

		return(privateSensorsOrderedByDistance);
	}






int Model::LoadData()
{
	static bool call = false;
	if (!call) {
		call = true;

		System system;
		system.InitializedMeasurement();
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

		system.EndMeasurement();
		cout << "Etape attribut en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;

		system.InitializedMeasurement();
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

		system.EndMeasurement();
		cout << "Etape cleaner en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
		system.InitializedMeasurement();
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

			itCleaner = bufferCleaner.find(cleanerID);
			if (itCleaner == bufferCleaner.end()) {
				return 2; //erreur de lecture
			}
			itCleaner->second.SetProviderID(providerID);
			it = bufferProvider.find(providerID);
			if (it != bufferProvider.end()) {
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

		system.EndMeasurement();
		cout << "Etape provider en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
		system.InitializedMeasurement();
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
			bufferSensor[sensorID] = sensor;
		}
		file.close();

		system.EndMeasurement();
		cout << "Etape sensor en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
		system.InitializedMeasurement();
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
			tmp->tm_year = stoi(buffer.substr(0, 4)) - 1900;
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
			Measurement measure(timestamp, value, attribute);
			bufferSensor[sensorID].AddMeasurement(measure);
		}
		file.close();


		system.EndMeasurement();
		cout << "Etape mesures en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
		system.InitializedMeasurement();
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
				bufferUser[userID] = IndividualUser(userID, itSensor->second);
			}
			privateSensors.push_back(itSensor->second);
		}
		file.close();
		system.EndMeasurement();
		cout << "Etape user en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
		system.InitializedMeasurement();

		for (itUser = bufferUser.begin(); itUser != bufferUser.end(); ++itUser) {
			individuals.push_back(itUser->second);
		}
		system.EndMeasurement();
		cout << "Etape copie user en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
		system.InitializedMeasurement();
		for (itSensor = bufferSensor.begin(); itSensor != bufferSensor.end(); ++itSensor) {
			sensors.push_back(itSensor->second);
		}
		system.EndMeasurement();
		cout << "Etape copie sensor en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;




		return 0;
	}
	 else {
	 return 3;  //Données déjà chargé
	}
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





void Model::UpdateSensorState(int idSensor) 
{
	vector<Sensor>::iterator iter;
	bool find = false;
	for (iter = sensors.begin(); iter != sensors.end(); iter++) {

		if (iter->GetID() == idSensor) {
			find = true;
			Sensor* toFind = &(*iter);

			// dysfunction it
			toFind->SetState(false);


			// First look if it's a private sensor 
			if (toFind->GetUserID() != -1) {    

				// add to list of malicious sensors
				
				maliciousSensors.push_back(*toFind);
				//erase from list of sensors
				sensors.erase(iter);
				UpdateIndividualState(toFind->GetUserID());
			}

			// if not, then it's a government sensor
			else {
				// add it to list of maintenance srnsors 
				maintenanceSensors.push_back(*toFind);
				//erase from list of sensors
				sensors.erase(iter);
			}
			return;
		}
	}
	if (!find) {
		for (iter = maintenanceSensors.begin(); iter != maintenanceSensors.end(); iter++) {
			if (iter->GetID() == idSensor) {
				cout << *iter << endl;
				find = true;
				Sensor* toFind = &(*iter);
				toFind->SetState(true);
				sensors.push_back(*toFind);
				maintenanceSensors.erase(iter);
				return;
			}
		}
	}
	if (!find) {
		for (iter = maliciousSensors.begin(); iter != maliciousSensors.end(); iter++) {
			if (iter->GetID() == idSensor) {
				find = true;
				Sensor* toFind = &(*iter);
				toFind->SetState(true);
				privateSensors.push_back(*toFind);
				sensors.push_back(*toFind);
				maintenanceSensors.erase(iter);
				UpdateIndividualState(toFind->GetUserID());
				return;
			}
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
			for (iter = privateSensors.begin(); iter != privateSensors.end(); iter++) {
				if (idIndividual == iter->GetUserID())
				{
					iter->SetState(false);
					maliciousSensors.push_back(*iter);
					privateSensors.erase(iter);
					
				}
			}

			for (iter = sensors.begin(); iter != sensors.end(); iter++) {
				if (idIndividual == iter->GetUserID())
				{
					sensors.erase(iter);
				}
			}
		}
		// if not
		// move its sensors from malicious to private
		else {
			for (iter = maliciousSensors.begin(); iter != maliciousSensors.end(); iter++) {
				if (iter->GetUserID() == idIndividual) {
					iter->SetState(true);
					privateSensors.push_back(*iter);
					sensors.push_back(*iter);
					// erase it from the list we run through 
					maliciousSensors.erase(iter);
				}
			}
		}
	}
	else {
		exit(1);
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

