// AirWatcher.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <fstream>
using namespace std;
#include "Model/Entity/GovernmentAgency.h"
#include "Model/Entity/Cleaner.h"
#include "Model/Entity/Attribute.h"
#include "Model/Entity/Measurement.h"
#include "Model/Entity/Provider.h"
#include "Model/Entity/IndividualUser.h"
#include "Model/Entity/Sensor.h"
#include "Model/Model.h"
#include "Util/ReaderConfig.h"
#include "Controller/System.h"
#include "Controller/Statistics.h"
#include "View/UserInterface.h"



int main()
{
    cout << "Hello World!\n";
    Model model;
    System system;
    Statistics stat(&model);
    system.InitializedMeasurement();
    cout << "Chargement des données ..." << endl;

    int res = model.LoadData();
    cout << res << endl;
    cout << "Données chargées" << endl;
    system.EndMeasurement();
    cout << "Données chargées en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;

    if (res == 0) {
        system.InitializedMeasurement();
        cout << "List of sensors : " << endl;
        map< int, Sensor>* sensors = model.GetSensors();
        map< int, Sensor>::iterator i; //Auto
        i = sensors->begin();
        for (i = sensors->begin(); i != sensors->end(); ++i) {
            cout << i->second << endl;

        }
        //for (const auto & currentSensor : model.sensors) {
        cout << endl;

        cout << "List of cleaners : " << endl;
        map< int, Cleaner>::iterator itCleaner = model.GetCleaners()->begin();
        for (itCleaner; itCleaner != model.GetCleaners()->end(); ++itCleaner) {
            cout << itCleaner->second << endl;
        }

        cout << endl;

        cout << "List of providers : " << endl;
        map< int, Provider>::iterator itProvider = model.GetProviders()->begin();
        for (itProvider; itProvider != model.GetProviders()->end(); ++itProvider) {
            cout << itProvider->second << endl;
        }

        cout << endl;

        cout << "List of users : " << endl;
        map< int, IndividualUser>::iterator itIndividualUser = model.GetIndividuals()->begin();
        for (itIndividualUser; itIndividualUser != model.GetIndividuals()->end(); ++itIndividualUser) {
            cout << itIndividualUser->second << endl;
        }

        cout << endl;
        system.EndMeasurement();
        cout << "Données afichées en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;


        cout << "Stat date NULL" << endl;
        system.InitializedMeasurement();
        double test = stat.CircularMeanAirQuality(44, 0, 0, nullptr);
        cout << "Qualité de l'air (attendu 2): " << test << endl;
        system.EndMeasurement();
        cout << "Données afichées en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;

        cout << "Stat date non null" << endl;
        tm tmp = tm();
        tmp.tm_mday = 28;
        tmp.tm_mon = 3 - 1;
        tmp.tm_year = 2019 - 1900;
        tmp.tm_hour = 12;
        time_t date = mktime(&tmp);
        system.InitializedMeasurement();
        test = stat.CircularMeanAirQuality(44, 0, 0, &date);
        cout << "Qualité de l'air (attendu 2): " << test << endl;
        system.EndMeasurement();
        cout << "Données afichées en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;

        cout << "Stat rayon non null" << endl;
        system.InitializedMeasurement();
        test = stat.CircularMeanAirQuality(44, 0, 0.4, nullptr);
        cout << "Qualité de l'air (attendu 2): " << test << endl;
        system.EndMeasurement();
        cout << "Données afichées en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;

        tmp.tm_mday = 9;
        tmp.tm_mon = 2 - 1;
        tmp.tm_year = 2019 - 1900;
        tmp.tm_hour = 12;
        date = mktime(&tmp);
        cout << "Stat rayon non null et date non null" << endl;
        system.InitializedMeasurement();
        test = stat.CircularMeanAirQuality(44, 0, 0.4, &date);
        cout << "Qualité de l'air (attendu à calculer): " << test << endl;
        system.EndMeasurement();
        cout << "Données afichées en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;



        cout << endl;


        cout << "List of private sensors : " << endl;
        map< int, Sensor>* sensorsPrive = model.GetPrivateSensors();
        i = sensorsPrive->begin();
        for (i = sensorsPrive->begin(); i != sensorsPrive->end(); ++i) {
            cout << i->second << endl;
            cout << "Qualité de l'air évalué par le sensor : " << stat.AirQualitySensor(&i->second) << endl;
        }

        tmp.tm_mday = 3;
        tmp.tm_mon = 12 - 1;
        tmp.tm_year = 2019 - 1900;
        tmp.tm_hour = 12;
        date = mktime(&tmp);
        i = sensorsPrive->begin();
        for (i = sensorsPrive->begin(); i != sensorsPrive->end(); ++i) {
            cout << i->second << endl;
            cout << "Qualité de l'air évalué par le sensor : " << stat.AirQualitySensor(&i->second, &date) << endl;
        }
        system.InitializedMeasurement();
        cout << *model.SearchSensor(1) << endl;
        system.EndMeasurement();
        cout << "Données afichées en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;


        Sensor* sensor = model.SearchSensor(0);
        size_t size1 = model.GetSensors()->size();
        size_t size2 = model.GetMaintenanceSensors()->size();
        cout << size1 << endl;
        cout << size2 << endl;
        cout << *sensor << endl;
        model.UpdateSensorState(0);
        sensor = model.SearchSensor(0);
        size1 = model.GetSensors()->size();
        size2 = model.GetMaintenanceSensors()->size();
        cout << size1 << endl;
        cout << size2 << endl;
        if (sensor == nullptr) {
            cout << "pb" << endl;
            cout << model.GetMaintenanceSensors()->begin()->second << endl;
        }
        else {
            cout << *sensor << endl;

        }
        model.UpdateSensorState(0);
        sensor = model.SearchSensor(0);
        size1 = model.GetSensors()->size();
        size2 = model.GetMaintenanceSensors()->size();
        cout << size1 << endl;
        cout << size2 << endl;
        if (sensor == nullptr) {
            cout << "pb" << endl;
            //cout << *Model::GetMaintenanceSensors()->begin() << endl;
        }
        else {
            cout << *sensor << endl;

        }

        IndividualUser* user = model.SearchIndividual(1);
        size1 = model.GetSensors()->size();
        size2 = model.GetMaliciousIndividualSensors()->size();
        size_t size3 = model.GetPrivateSensors()->size();
        cout << *user << endl;
        cout << size1 << endl;
        cout << size2 << endl;
        cout << size3 << endl;
        model.UpdateIndividualState(user->GetID());
        size1 = model.GetSensors()->size();
        size2 = model.GetMaliciousIndividualSensors()->size();
        size3 = model.GetPrivateSensors()->size();
        cout << *user << endl;
        cout << size1 << endl;
        cout << size2 << endl;
        cout << size3 << endl;

    }

    UserInterface ui(&model);
    ui.MenuUI();



}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
