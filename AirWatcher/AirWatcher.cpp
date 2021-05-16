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
int main()
{
    cout << "Hello World!\n";
    System system;
    system.InitializedMeasurement();
    cout << "Chargement des données ..." << endl;
    
    int res = Model::LoadData();
    cout << res << endl;
    cout << "Données chargées" << endl;
    system.EndMeasurement();
    cout << "Données chargées en : " << system.GetAlgorithmEfficiency()<< " secondes" << endl;

    if (res == 0) {
        system.InitializedMeasurement();
        cout << "List of sensors : " << endl;
        vector<Sensor>* sensors = Model::GetSensors();
        vector<Sensor>::iterator i;
        i = sensors->begin();
        for (i = sensors->begin(); i != sensors->end(); ++i) {
            cout << *i <<endl;
           
        }

        cout << endl;

        cout << "List of cleaners : " << endl;
        vector<Cleaner>::iterator itCleaner = Model::GetCleaners()->begin();
        for (itCleaner; itCleaner != Model::GetCleaners()->end(); ++itCleaner) {
            cout << *itCleaner << endl;
        }

        cout << endl;

        cout << "List of providers : " << endl;
        vector<Provider>::iterator itProvider = Model::GetProviders()->begin();
        for (itProvider; itProvider != Model::GetProviders()->end(); ++itProvider) {
            cout << *itProvider << endl;
        }

        cout << endl;

        cout << "List of users : " << endl;
        vector<IndividualUser>::iterator itIndividualUser = Model::GetIndividuals()->begin();
        for (itIndividualUser; itIndividualUser != Model::GetIndividuals()->end(); ++itIndividualUser) {
            cout << *itIndividualUser << endl;
        }

        cout << endl;
        system.EndMeasurement();
        cout << "Données afichées en : " << system.GetAlgorithmEfficiency() << " secondes"<<endl;
    }

    cout << "Stat date NULL" << endl;
    system.InitializedMeasurement();
    double test = Statistics::CircularMeanAirQuality(44, 0, 0, nullptr);
    cout << "Qualité de l'air (attendu 2): " <<test << endl;
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
    test = Statistics::CircularMeanAirQuality(44, 0, 0, &date);
    cout << "Qualité de l'air (attendu 2): " << test << endl;
    system.EndMeasurement();
    cout << "Données afichées en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;

    cout << "Stat rayon non null" << endl;
    system.InitializedMeasurement();
    test = Statistics::CircularMeanAirQuality(44, 0, 0.4, nullptr);
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
    test = Statistics::CircularMeanAirQuality(44, 0, 0.4, &date);
    cout << "Qualité de l'air (attendu à calculer): " << test << endl;
    system.EndMeasurement();
    cout << "Données afichées en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;

   

    cout << endl;
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
