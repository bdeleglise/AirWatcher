
/*************************************************************************
						   Model  -  description
							 -------------------
	début                : 06/05/2021
	copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
	e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
						   benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/

//---------- Realisation de la classe <Model> (fichier Model.cpp) --
#include "Model.h"
#include <fstream>
#include <string>
#include "../Controller/System.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

GovernmentAgency* Model::SearchGovernmentAgency(int id) 
//Algorithme : Renvoie nullptr si l'ID n'a pas été trouvé, un pointeur vers un utilisateur de type GovernmentAgency correspondant sinon.
{
	GovernmentAgency* user = nullptr;
	if (governmentAgencies.find(id) != governmentAgencies.end())
	{
		user = &governmentAgencies[id];
	}
	
	return user;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

IndividualUser* Model::SearchIndividual(int id)
//Algorithme : Renvoie nullptr si l'ID n'a pas été trouvé, un pointeur vers un utilisateur de type IndividualUser correspondant sinon.
{
	IndividualUser* user = nullptr;
	if (individuals.find(id) != individuals.end())
	{
		user = &individuals[id];
	}
	return user;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Provider* Model::SearchProvider(int id)
//Algorithme : Renvoie nullptr si l'ID n'a pas été trouvé, un pointeur vers un utilisateur de type Provider correspondant sinon.
{
	Provider* user = nullptr;
	if (providers.find(id) != providers.end())
	{
		user = &providers[id];
	}

	return user;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////


Cleaner* Model::SearchCleaner(int id)
//Algorithme : Renvoie nullptr si l'ID n'a pas été trouvé, un pointeur vers le cleaner correspondant sinon.
{
	Cleaner* cleaner = nullptr;
	if (cleaners.find(id) != cleaners.end())
	{
		cleaner = &cleaners[id];
	}

	return cleaner;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sensor* Model::SearchSensor(int id)
//Algorithme : Renvoie nullptr si l'ID n'a pas été trouvé, un pointeur vers le capteur correspondant sinon.
{
	map<int, Sensor>::iterator iter = sensors.find(id);
	bool find = false;
	Sensor* res = nullptr;
	if (iter != sensors.end()) {
		find = true;
		res = &iter->second;
	}
	if (!find) {
		iter = maliciousSensors.find(id);
		if (iter != maliciousSensors.end()) {
			find = true;
			res = &iter->second;
		}
	}
	if (!find) {
		iter = maintenanceSensors.find(id);
		if (iter != maintenanceSensors.end()) {
			find = true;
			res = &iter->second;
		}
	}
	return res;

	
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

	vector<Sensor*>* Model::GetSensorsOrderByDistance(double latitude, double longitude)
	//Algorithme : Renvoie un pointeur vers un vector de Sensor* qui contient les 4 capteurs les plus proches du point passé en parametre
	{

		vector<Sensor*>* nearSensors = new vector<Sensor*>(4);
		vector<Sensor*> SensorsVector;


		for (auto& pair : sensors) {
			SensorsVector.push_back(&(pair.second));
		}


		partial_sort_copy(SensorsVector.begin(), SensorsVector.end(), nearSensors->begin(), nearSensors->end(), [latitude, longitude](Sensor* s1, Sensor* s2) {
			double d1 = pow(latitude - s1->GetLatitude(), 2) + pow(longitude - s1->GetLongitude(), 2);
			double d2 = pow(latitude - s2->GetLatitude(), 2) + pow(longitude - s2->GetLongitude(), 2);
			return (d1 < d2);
			});

		return nearSensors;

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	vector<pair<Sensor, double>>* Model::GetPrivateSensorsOrderByDistance(double latitude, double longitude)
	//Algorithme : Renvoie un pointeur vers un vector de Sensor* qui contient les 3 capteurs privés les plus proches du point passé en parametre
	{
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
//Algorithme : Permet de charger les données dans l'application en allant lire dans les fichiers .csv du dataset
{
	static bool call = false;
	if (!call) {
		call = true;

		//lecture des attributs --------------------------------------------------------
		ifstream file;
		file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.ATTRIBUTESFILE);

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


		//lecture des cleaner --------------------------------------------------------------------------
		file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.CLEANERSFILE);

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

		//lecture des providers --------------------------------------------------------------------------
		file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.PROVIDERSFILE);
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
		
		//lecture des sensors --------------------------------------------------------------------------
		file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.SENSORFILE);
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

		//lecture des mesures --------------------------------------------------------------------------
		file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.MEASUREMENTSFILE);

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


		//lecture des users --------------------------------------------------------------------------
		file.open(FILE_NAME.DIRECTORYPATH + FILE_NAME.USERSFILE);
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
			itUser = individuals.find(userID);
			if (itUser != individuals.end()) {
				itUser->second.AddSensor(itSensor->second);
			}
			else {
				individuals[userID] = IndividualUser(userID, itSensor->second);
			}
			privateSensors[sensorID]=itSensor->second;
		}
		file.close();
		return 0;
	}
	 else {
	 return 3;  //Données déjà chargé
	}
}


//////////////

void Model::IncrementPointIndividualUser(int idIndividual)
//Algorithme : incremente les points d'un Individu identifié par son ID
{
	individuals[idIndividual].SetPoints(individuals[idIndividual].GetPoints() + 1);
}

void Model::UpdateSensorState(int idSensor) 
//Algorithme : On recherche le capteur passé en paramètre pour mettre à jour son statut selon qu'il soit actuellement classé en état normal, maintenance ou frauduleux.
{
	
	bool find = false;
	map<int, Sensor>::iterator iter = sensors.find(idSensor);
	if (iter != sensors.end())
	{
		Sensor* sensor = &iter->second;
		if (sensor->GetUserID() != -1)
		{
			UpdateIndividualState(sensor->GetUserID());
		}
		else 
		{
			sensor->SetState(false);
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
		UpdateIndividualState(sensor->GetUserID());
		return;
	}
	
}



void Model::UpdateIndividualState(int idIndividual)
//Algorithme : Mettre à jour le statut de l'individu en parametre pour l'ajouter/retirer de la liste des frauduleux
{
	if (individuals.find(idIndividual) != individuals.end())
	// On recupere un pointeur vers l'individu
	{
		IndividualUser* individualPtr = &individuals[idIndividual];
		//On modifie l'etat de son attribut reliable
		individualPtr->SetReliable(!individualPtr->GetReliable());
		bool reliable = individualPtr->GetReliable();
		// S'il n'est pas de confiance, on bouge ses capteurs de la liste de privateSensors vers maliciousSensors
		vector<Sensor>* individualSensors = individualPtr->GetSensors();
		if (!reliable) {
			for (auto& currentSensor : *individualSensors) {
				sensors.erase(currentSensor.GetID());
				privateSensors.erase(currentSensor.GetID());
				maliciousSensors[currentSensor.GetID()] = currentSensor;
			}
		}
		// Sinon, on bouge ses capteurs de maliciousSensors vers privateSensors
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




