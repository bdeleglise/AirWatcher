#include <iostream>
#include <string>
using namespace std;

#include "UserInterface.h"
#include "../Controller/Statistics.h"

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
        "Pour naviguer dans les menus du programme, entrez le chiffre correspondant à l'action que vous souhaitez réaliser. \n"
        "\n"
        "------------Menu principal-------------"
        "\n"
        "1 - Afficher des statistiques\n"
        "2 - Détecter les fraudes\n"
        << endl;
    choice = GetInput();
    switch (choice)
    {
        case 1:
            StatisticsUI();
            break;
    }
}

void UserInterface::StatisticsUI()
//Menu statistiques
{
    cout << "------------Affichage des statistiques-------------\n"
        "\n"
        "1 - Afficher la qualité d'air moyenne d'un endroit précis à l'heure actuelle \n"
        "2 - Afficher la qualité d'air moyenne d'un endroit précis à une date précise \n"
        "3 - Afficher la qualité d'air moyenne d'une zone à l'heure actuelle \n"
        "4 - Afficher la qualité d'air moyenne d'une zone à une date précise \n"
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
    int result;
    cout << "Merci d'entrer les coordonnées de l'endroit dont vous souhaitez observer la qualité d'air" << endl;
    x = getXcoord();
    y = getYcoord();
    switch (choice)
    {
    case 1:
        r = 0;
        time = 0;
        result = Statistics::CircularMeanAirQuality(x, y, r, nullptr);
        break;
    case 2:
        r = 0;
        time = getTime();
        result = Statistics::CircularMeanAirQuality(x, y, r, &time);
        break;
    case 3:
        r = getRayon();
        result = Statistics::CircularMeanAirQuality(x, y, r, nullptr);
        break;
    case 4:
        r = getRayon();
        time = getTime();
        result = Statistics::CircularMeanAirQuality(x, y, r, &time);
        break;
    }

    cout << "Voici la qualité de l'air calculée avec indice ATMO :" << endl;
    cout << result << endl;
}

int UserInterface::getRayon()
{
    cout << " Merci d'entrer le rayon de la zone à mesurer autour du point fourni précedemment" << endl;
    return GetInput();
}

time_t UserInterface::getTime()
{
    int day, month, year, hour;
    cout << "Merci d'entrer la date au format numérique, en saisissant un numéro par ligne" << endl;
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
