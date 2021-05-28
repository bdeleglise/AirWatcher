#include "Model.h"
#include <fstream>
#include <string>
#include "../Controller/System.h"




///////////////////////////////////////////////////////////////////////////////////////////////////////////////

GovernmentAgency* Model::SearchGovernmentAgency(int id) {
	
	for (auto& pair : governmentAgencies) {
		const int idGov = pair.first;
		if (idGov == id) {
			GovernmentAgency* user = &pair.second;
			return user;
		}
	}

	return(nullptr);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

IndividualUser* Model::SearchIndividual(int id) {
	
	for (auto& pair : individuals) {
		const int idUser = pair.first;
		if (idUser == id) {
			IndividualUser* user = &pair.second;
			return user;
		}
	}

	return(nullptr);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Provider* Model::SearchProvider(int id) {
	
	for (auto& pair : providers) {
		const int idUser = pair.first;
		if (idUser == id) {
			Provider* user = &pair.second;
			return user;
		}
	}

	return(nullptr);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////


Cleaner* Model::SearchCleaner(int id) {
	
	for (auto& pair : cleaners) {
		const int idCleaner = pair.first;
		if (idCleaner == id) {
			Cleaner* cleaner = &pair.second;
			return cleaner;
		}
	}

	return(nullptr);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sensor* Model::SearchSensor(int id) {
	for (auto& pair : sensors) {
		const int idSensor = pair.first;
		if (idSensor == id) {
			Sensor* sensor = &pair.second;
			return sensor;
		}
	}
	for (auto& pair : maintenanceSensors) {
		const int idSensor = pair.first;
		if (idSensor == id) {
			Sensor* sensor = &pair.second;
			return sensor;
		}
	}
	for (auto& pair : maliciousSensors) {
		const int idSensor = pair.first;
		if (idSensor == id) {
			Sensor* sensor = &pair.second;
			return sensor;
		}
	}

	return(nullptr);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

map<int, Sensor>* Model::GetSensors() {
	return &sensors;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

map<int, Sensor>* Model::GetPrivateSensors() {
	return &privateSensors;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

map<int, IndividualUser>* Model::GetIndividuals() {
	return &individuals;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

map<int, Sensor>* Model::GetMaintenanceSensors() {
	return &maintenanceSensors;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////


map<int, Provider>* Model::GetProviders() {
	return &providers;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

map<int, Cleaner>* Model::GetCleaners() {
	return &cleaners;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

map<int, Sensor>* Model::GetMaliciousIndividualSensors() {
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

		for (auto& pair : sensors) {
			SensorsVector->push_back(pair.second);
		}

		vector<Sensor>::iterator it;

		partial_sort_copy(SensorsVector->begin(), SensorsVector->end(), nearSensors->begin(), nearSensors->end(), [latitude, longitude](Sensor& s1, Sensor& s2) {
			double d1 = pow(latitude - s1.GetLatitude(), 2) + pow(longitude - s1.GetLongitude(), 2);
			double d2 = pow(latitude - s2.GetLatitude(), 2) + pow(longitude - s2.GetLongitude(), 2);
			return (d1 < d2);
			});

		int index = 0;

		for (it = nearSensors->begin(); it != nearSensors->end(); ++it) {
			double distance = sqrt(pow(latitude - it->GetLatitude(), 2) + pow(longitude - it->GetLongitude(), 2));
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

		for (auto& pair : privateSensors) {
			PrivateSensorsVector->push_back(pair.second);
		}
		vector<Sensor>::iterator it;

		partial_sort_copy(PrivateSensorsVector->begin(), PrivateSensorsVector->end(), nearSensors->begin(), nearSensors->end(), [latitude, longitude](Sensor& s1, Sensor& s2) {
			double d1 = pow(latitude - s1.GetLatitude(), 2) + pow(longitude - s1.GetLongitude(), 2);
			double d2 = pow(latitude - s2.GetLatitude(), 2) + pow(longitude - s2.GetLongitude(), 2);
			return (d1 < d2);
			});

		int index = 0;

		for (it = nearSensors->begin(); it != nearSensors->end(); ++it) {
			double distance = sqrt(pow(latitude - it->GetLatitude(), 2) + pow(longitude - it->GetLongitude(), 2));
			privateSensorsOrderedByDistance->push_back(make_pair(*it, distance));
			index++;
		}

		return(privateSensorsOrderedByDistance);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////




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

			cleaners[cleanerID] = Cleaner(cleanerID, -1, latitude, longitude, start, end);
		}

		file.close();

		system.EndMeasurement();
		cout << "Etape cleaner en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
		system.InitializedMeasurement();
		//lecture des providers --------------------------------------------------------------------------
		file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.PROVIDERSFILE);
		cout << "Loading of providers" << endl;
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

			itCleaner = cleaners.find(cleanerID);
			if (itCleaner == cleaners.end()) {
				return 2; //erreur de lecture
			}
			itCleaner->second.SetProviderID(providerID);
			it = providers.find(providerID);
			if (it != providers.end()) {
				it->second.AddCleaner(itCleaner->second);
			}
			else {
				providers[providerID] = Provider(providerID, itCleaner->second);
			}
		}
		file.close();
		

		system.EndMeasurement();
		cout << "Etape provider en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
		system.InitializedMeasurement();
		//lecture des sensors --------------------------------------------------------------------------
		file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.SENSORFILE);
		cout << "Loading of sensors" << endl;
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
			sensors[sensorID] = sensor;
		}
		file.close();

		system.EndMeasurement();
		cout << "Etape sensor en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
		system.InitializedMeasurement();
		//lecture des mesures --------------------------------------------------------------------------
		file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.MEASUREMENTSFILE);
		cout << "Loading of measurements" << endl;

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
			sensors[sensorID].AddMeasurement(measure);
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

			itSensor = sensors.find(sensorID);
			if (itSensor == sensors.end()) {
				return 2;
			}
			itSensor->second.SetUser(userID);
			itUser = bufferUser.find(userID);
			if (itUser != bufferUser.end()) {
				itUser->second.AddSensor(itSensor->second);
			}
			else {
				individuals[userID] = IndividualUser(userID, itSensor->second);
			}
			privateSensors[sensorID]=itSensor->second;
		}
		file.close();
		system.EndMeasurement();
		cout << "Etape user en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
		return 0;
	}
	 else {
	 return 3;  //Données déjà chargé
	}
}


//////////////

void Model::IncrementPointIndividualUser(int idIndividual) {
	individuals[idIndividual].SetPoints(individuals[idIndividual].GetPoints() + 1);
}

void Model::UpdateSensorState(int idSensor) 
{
	
	bool find = false;
	map<int, Sensor>::iterator iter = sensors.find(idSensor);
	if (iter != sensors.end())
	{
		Sensor* sensor = &iter->second;
		sensor->SetState(false);
		if (sensor->GetUserID() != -1)
		{
			maliciousSensors[sensor->GetID()] = *sensor;
			sensors.erase(iter);
			UpdateIndividualState(sensor->GetUserID());
		}
		else 
		{
			maintenanceSensors[sensor->GetID()] = *sensor;
			sensors.erase(iter);
		}
		return;
	}

	iter = maintenanceSensors.find(idSensor);
	if (iter != maintenanceSensors.end()) {
		Sensor* sensor = &iter->second;
		sensor->SetState(true);
		sensors[sensor->GetID()] = *sensor;
		maintenanceSensors.erase(iter);
		return;
	}

	iter = maliciousSensors.find(idSensor);
	if (iter != maliciousSensors.end()) {
		Sensor* sensor = &iter->second;
		sensor->SetState(true);
		sensors[sensor->GetID()] = *sensor;
		privateSensors[sensor->GetID()] = *sensor;
		maliciousSensors.erase(iter);
		UpdateIndividualState(sensor->GetUserID());
		return;
	}
	
}



void Model::UpdateIndividualState(int idIndividual) {
	IndividualUser* individualPtr = SearchIndividual(idIndividual);
	if (individualPtr != nullptr) {
		individualPtr->SetReliable(!individualPtr->GetReliable());
		bool reliable = individualPtr->GetReliable();
		// if the individual user is not reliable, then : 
		// move its sensors from privateSensors list to malicious
		vector<Sensor>* individualSensors = individualPtr->GetSensors();
		if (!reliable) {
			for (auto& currentSensor : *individualSensors) {
				sensors.erase(currentSensor.GetID());
				privateSensors.erase(currentSensor.GetID());
				maliciousSensors[currentSensor.GetID()] = currentSensor;
			}
		}
		// if not
		// move its sensors from malicious to private
		else {
			for (auto& currentSensor : *individualSensors) {
				maliciousSensors.erase(currentSensor.GetID());
				privateSensors[currentSensor.GetID()] = currentSensor;
				sensors[currentSensor.GetID()] = currentSensor;
			}
		}
	}
	else {
		exit(1);
	}
}


Model::Model()	
	: governmentAgencies(), cleaners(), individuals(), sensors(), maintenanceSensors(), privateSensors(), maliciousSensors(), providers()
{}


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

