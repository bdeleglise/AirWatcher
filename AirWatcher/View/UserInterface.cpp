#include <iostream>
#include <string>
using namespace std;

#include "UserInterface.h"

UserInterface::UserInterface(Model* unModel)
    : model(unModel)
{
}

int UserInterface::GetInput()
//Récuperer le choix de l'utilisateur
{
    int input;
    cin >> input;
    return input;
}

void UserInterface::MenuUI()
//Menu principal
{
    cout << "Bienvenue dans le logiciel AirWatcher \n"
        "Pour naviguer dans les menus du programme, entrez le chiffre correspondant a l'action que vous souhaitez realiser. \n"
        "\n"
        "------------Menu principal-------------"
        "\n"
        "1 - Afficher des statistiques\n"
        "2 - Detecter les fraudes\n"
        "3 - Rechercher un provider\n"
        << endl;
    choice = GetInput();
    switch (choice)
    {
        case 1:
            StatisticsUI();
            break;
        case 2:
            FraudUI();
            break;
        case 3:ProviderUI();
        default:
            MenuUI();
    }
}

void UserInterface::ProviderUI()
{
    int id;
    cout << "------------Rechercher un provider-------------\n"
        "Merci d'entrer l'identifiant du provider dont vous souhaitez afficher les informations\n"
        << endl;
    cin >> id;
    Provider *p = model->SearchProvider(id);
    if (p == nullptr)
    {
        cout << "Impossible de trouver un provider ayant cet identifiant" << endl;
        cout << endl;
        MenuUI();
    }
    else
    {
        cout << "Informations liees au provider :" << endl;
        vector<Cleaner>* cleaners = p->GetCleaners();
        for (auto& cleaner : *cleaners)
        {
            cout << cleaner << endl;
        }
        char buff;
        cout << "Entrez un caractere pour revenir au menu principal." << endl;
        cin >> buff;
        cout << endl;
        MenuUI();
    }


}

void UserInterface::FraudUI()
{
    SensorManagement sm(model);
    vector<pair<Sensor, double>> frauds;
    cout << "------------Detection des Fraudes-------------\n"
        "Voici une liste des capteurs prives potentiellement frauduleux : \n"
    << endl;
    frauds = sm.FraudulentSensorDetection();
    for (const auto& currentPair : frauds)
    {
        cout << "Capteur numero " << currentPair.first.GetID() << "\n"
            "Pourcentage d'erreur  : " << currentPair.second << "\n"
            << endl;
    }
    char buff;
    cout << "Entrez un caractere pour revenir au menu principal." << endl;
    cin >> buff;
    cout << endl;
    MenuUI();
    
}
void UserInterface::StatisticsUI()
//Menu statistiques
{

    Statistics stats(model);
    cout << "------------Affichage des statistiques-------------\n"
        "\n"
        "1 - Afficher la qualite d'air moyenne d'un endroit precis à l'heure actuelle \n"
        "2 - Afficher la qualite d'air moyenne d'un endroit precis à une date precise \n"
        "3 - Afficher la qualite d'air moyenne d'une zone à l'heure actuelle \n"
        "4 - Afficher la qualite d'air moyenne d'une zone à une date precise \n"
        "5 - Retour au menu principal\n"
        << endl;
    choice = GetInput();
    if (choice == 5)
    {
        MenuUI();
        return;
    }
    int x, y, r;
    time_t time;
    double result=0;
    cout << "Merci d'entrer les coordonnees de l'endroit dont vous souhaitez observer la qualite d'air" << endl;
    x = getXcoord();
    y = getYcoord();
    switch (choice)
    {
    case 1:
        r = 0;
        result = stats.CircularMeanAirQuality(x, y, r, nullptr);
        break;
    case 2:
        r = 0;
        time = getTime();
        result = stats.CircularMeanAirQuality(x, y, r, &time);
        break;
    case 3:
        r = getRayon();
        result = stats.CircularMeanAirQuality(x, y, r, nullptr);
        break;
    case 4:
        r = getRayon();
        time = getTime();
        result = stats.CircularMeanAirQuality(x, y, r, &time);
        break;
    }

    cout << "Voici la qualite de l'air calculee avec indice ATMO :" << endl;
    cout << result << endl;

    char buff;
    cout << "Entrez un caractere pour revenir au menu principal." << endl;
    cin >> buff;
    cout << endl;
    MenuUI();
}

int UserInterface::getRayon()
{
    cout << " Merci d'entrer le rayon de la zone à mesurer autour du point fourni precedemment" << endl;
    return GetInput();
}

time_t UserInterface::getTime()
{
    int day, month, year, hour;
    cout << "Merci d'entrer la date au format numerique, en saisissant un numero par ligne" << endl;
    cout << "Entrez le jour" << endl;
    day = GetInput();
    cout << "Entrez le mois";
    month = GetInput();
    cout << " Entrez l'année";
    year = GetInput();
    cout << "Entrez l'heure";
    hour = GetInput();
    tm tmp = tm();
    tmp.tm_mday = day;
    tmp.tm_mon = month - 1;
    tmp.tm_year = year - 1900;
    tmp.tm_hour = hour;
    time_t date = mktime(&tmp);
    return date;
}

int UserInterface::getXcoord()
{
    cout << "x : " << endl;
    return GetInput();
}
int UserInterface::getYcoord()
{
    cout << "y : " << endl;
    return GetInput();
}
