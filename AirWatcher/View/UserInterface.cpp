/*************************************************************************
                           UserInterface  -  description
                             -------------------
    début                : 06/05/2021
    copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
    e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
                           benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/

#include <iostream>
#include <string>
using namespace std;

#include "UserInterface.h"

UserInterface::UserInterface(Model* unModel)
    : model(unModel), evalPerformance(false), system()
{
}

int UserInterface::getInput()
//Recuperer le choix de l'utilisateur
{
    int input;
    cin >> input;
    while (cin.fail()) {
        cleanInputBuffer();
        cout << "Veuillez respecter le format :" << endl;
        cin >> input;
    }
    cleanInputBuffer();
    return input;
}

void UserInterface::MenuUI()
//Menu principal
{
    cout << "Bienvenue dans le logiciel AirWatcher \n"
        "Pour naviguer dans les menus du programme, entrez le chiffre correspondant a l'action que vous souhaitez realiser. \n"
        << endl;
    while (1) {
        cout << "------------Menu principal-------------"
            "\n"
            "1 - Afficher des statistiques\n"
            "2 - Afficher la page des capteurs\n"
            "3 - Afficher la page des capteurs prives\n"
            "4 - Afficher la page des air cleaners\n"
            "5 - Passer ou retirer le mode pour evaluer la perforance\n"
            "6 - Quitter\n"
            "---------------------------------------"
            << endl;
        choice = getInput();
        switch (choice)
        {
        case 1:
            statisticsUI();
            break;
        case 2:
            sensorUI();
            break;
        case 3:
            privateSensorsUI();
            break;
        case 4:
            cleanerAnalysisUI();
            break;
        case 5:
            evalPerformance = !evalPerformance;
            if (evalPerformance) {
                cout << "Passage en mode evaluation de la perforamnce" << endl;
            }
            else {
                cout << "Passage en mode sans evaluation de performance" << endl;
            }
            break;
        case 6:
            cout << "A bientot" << endl;
            return;
        default:

            cout << "Veuillez saisir un nombre valide svp" << endl;
        }
    }
}



void UserInterface::sensorUI()
//Menu des capteurs
{
    while (1) {
        cout << "------------Affichage des capteurs-------------\n"
            "\n"
            "1 - Afficher la liste de TOUS les capteurs \n"
            "2 - Afficher la liste des capteurs fonctionnels\n"
            "3 - Afficher la liste des capteurs en maintenance \n"
            "4 - Rechercher un capteur\n"
            "5 - Retour au menu principal\n"
            "-----------------------------------------------------\n"
            << endl;
        choice = getInput();



        switch (choice)
        {
        case 1:
        {
            system.InitializedMeasurement();
            map<int, Sensor>* sensors = model->GetSensors();
            map<int, Sensor>* sensorsMaint = model->GetMaintenanceSensors();
            map<int, Sensor>* sensorsMal = model->GetMaliciousIndividualSensors();
            if (sensors == nullptr || sensorsMaint == nullptr || sensorsMal == nullptr) {
                cout << "Une erreur s'est produite" << endl;
            }
            else {
                for (const auto& pair : *sensors) {
                    cout << pair.second << endl;
                    cout << endl;
                }
                for (const auto& pair : *sensorsMaint) {
                    cout << pair.second << endl;
                    cout << endl;
                }
                for (const auto& pair : *sensorsMal) {
                    cout << pair.second << endl;
                    cout << endl;
                }
            }
            break;
        }
        case 2:
        {
            system.InitializedMeasurement();
            map<int, Sensor>* sensors = model->GetSensors();
            if (sensors == nullptr) {
                cout << "Une erreur s'est produite" << endl;
            }
            else {
                for (const auto& pair : *sensors) {
                    cout << pair.second << endl;
                    cout << endl;
                }

            }
            break;
        }
        case 3:
        {
            system.InitializedMeasurement();
            map<int, Sensor>* sensorsMaint = model->GetMaintenanceSensors();
            if (sensorsMaint == nullptr) {
                cout << "Une erreur s'est produite" << endl;
            }
            else {
                for (const auto& pair : *sensorsMaint) {
                    cout << pair.second << endl;
                    cout << endl;
                }
            }
            break;
        }
        case 4:
        {
            cout << "Entrez l'id du capteur : " << endl;
            int idSensor = getInput();
            Sensor* sensor = model->SearchSensor(idSensor);
            if (sensor != nullptr) {
                cout << "Voulez vous afficher un apercu du capteur (1) ou toutes les mesures (2)" << endl;
                int option = getInput();
                system.InitializedMeasurement();
                if (option == 1) {
                    cout << *sensor << endl;
                    cout << endl;
                }
                else if (option == 2) {
                    cout << "Sensor" << sensor->GetID() << endl;
                    cout << "Etat : " << sensor->GetState() << endl;
                    if (sensor->GetUserID() != -1) {
                        cout << "Sensor de user" << sensor->GetUserID() << endl;
                    }
                    for (const auto& pair : *sensor->GetMeasurements()) {
                        for (const auto& mesure : pair.second)
                        {
                            cout << mesure << endl;
                        }
                    }
                    cout << endl;
                }
                else {
                    cout << "Veuillez saisir un nombre valide" << endl;
                }
            }
            else {
                system.InitializedMeasurement();
                cout << "Le capteur n'existe pas" << endl;
            }
            break;
        }
        case 5:
            return;
        default:
            cout << "Veuillez saisir un nombre valide" << endl;
            break;
        }

        if (evalPerformance) {
            system.EndMeasurement();
            cout << "Requete traitee en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
        }
    }
}

void UserInterface::cleanerAnalysisUI()
//Menu des cleaners
{
    while (1) {
        cout << "------------Affichage des cleaners-------------\n"
            "\n"
            "1 - Afficher la liste de tous les cleaners \n"
            "2 - Afficher la liste de toutes les entreprises\n"
            "3 - Rechercher une entreprise \n"
            "4 - Rechercher un cleaner\n"
            "5 - Retour au menu principal\n"
            "-----------------------------------------------------\n"
            << endl;
        choice = getInput();



        switch (choice)
        {
        case 1:
        {
            system.InitializedMeasurement();
            map<int, Cleaner>* cleaners = model->GetCleaners();
            if (cleaners == nullptr) {
                cout << "Une erreur s'est produite" << endl;
            }
            else {
                for (const auto& pair : *cleaners) {
                    cout << pair.second << endl;
                    cout << endl;
                }

            }
            break;
        }
        case 2:
        {
            system.InitializedMeasurement();
            map<int, Provider>* providers = model->GetProviders();
            if (providers == nullptr) {
                cout << "Une erreur s'est produite" << endl;
            }
            else {
                for (const auto& pair : *providers) {
                    cout << pair.second << endl;
                }

            }
            break;
        }
        case 3:
        {
            cout << "Entrez l'id de l'entreprise : " << endl;
            int idProvider = getInput();
            system.InitializedMeasurement();
            Provider* provider = model->SearchProvider(idProvider);
            if (provider != nullptr) {
                cout << *provider << endl;
            }
            else {
                cout << "L'entreprise n'existe pas" << endl;
            }
            break;
        }
        case 4:
        {
            cout << "Entrez l'id du cleaner : " << endl;
            int idCleaner = getInput();
            system.InitializedMeasurement();
            Cleaner* cleaner = model->SearchCleaner(idCleaner);
            if (cleaner != nullptr) {
                cout << *cleaner << endl;
                cout << endl;
            }
            else {
                cout << "Le cleaner n'existe pas" << endl;
            }
            break;
        }
        case 5:
            return;
        default:
            cout << "Veuillez saisir un nombre valide" << endl;
            break;
        }

        if (evalPerformance) {
            system.EndMeasurement();
            cout << "Requete traitee en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
        }
    }
}

void UserInterface::privateSensorsUI()
//Menu des capteurs privés
{
    while (1) {
        cout << "------------Affichage des capteurs prives-------------\n"
            "\n"
            "1 - Afficher la liste de TOUS les capteurs prives \n"
            "2 - Afficher la liste de TOUS les utilisateurs\n"
            "3 - Afficher la liste des capteurs prives honnêtes\n"
            "4 - Afficher la liste des capteurs prives malhonnetes\n"
            "5 - Detecter les capteurs potentiellement frauduleux\n"
            "6 - Passer un utilisateur comme frauduleux\n"
            "7 - Rechercher un utilisateur \n"
            "8 - Rechercher un capteur prive\n"
            "9 - Retour au menu principal\n"
            "-----------------------------------------------------\n"
            << endl;
        choice = getInput();

        switch (choice)
        {
        case 1:
        {
            system.InitializedMeasurement();
            map<int, Sensor>* sensors = model->GetPrivateSensors();
            map<int, Sensor>* sensorsMal = model->GetMaliciousIndividualSensors();
            if (sensors == nullptr || sensorsMal == nullptr) {
                cout << "Une erreur s'est produite" << endl;
            }
            else {
                for (const auto& pair : *sensors) {
                    cout << pair.second << endl;
                    cout << endl;
                }
                for (const auto& pair : *sensorsMal) {
                    cout << pair.second << endl;
                    cout << endl;
                }

            }
            break;
        }
        case 2:
        {
            system.InitializedMeasurement();
            map<int, IndividualUser>* users = model->GetIndividuals();
            if (users == nullptr) {
                cout << "Une erreur s'est produite" << endl;
            }
            else {
                for (const auto& pair : *users) {
                    cout << pair.second << endl;
                }
            }
            break;
        }
        case 3:
        {
            system.InitializedMeasurement();
            map<int, Sensor>* sensors = model->GetPrivateSensors();
            if (sensors == nullptr) {
                cout << "Une erreur s'est produite" << endl;
            }
            else {
                for (const auto& pair : *sensors) {
                    cout << pair.second << endl;
                    cout << endl;
                }
            }
            break;
        }
        case 4:
        {
            system.InitializedMeasurement();
            map<int, Sensor>* sensorsMal = model->GetMaliciousIndividualSensors();
            if (sensorsMal == nullptr) {
                cout << "Une erreur s'est produite" << endl;
            }
            else {
                for (const auto& pair : *sensorsMal) {
                    cout << pair.second << endl;
                    cout << endl;
                }
            }
            break;
        }
        case 5:
        {
            system.InitializedMeasurement();
            SensorManagement sm(model);
            cout << "------------Detection des Fraudes-------------\n"
                "Voici une liste des capteurs prives potentiellement frauduleux : \n"
                << endl;
            vector<pair<Sensor*, Confidence>>* frauds = sm.FraudulentSensorDetection();
            for (auto& currentPair : *frauds)
            {
                cout << "Capteur numero " << currentPair.first->GetID() << "\n"
                    "Appartient a user" << currentPair.first->GetUserID() << "\n"
                    "Le capteur a " << currentPair.second.first << "% de chance d'etre frauduleux" << "\n"
                    "Pourcentage d'erreur par rapport au voisin : " << currentPair.second.second << "\n"
                    << endl;
            }
            delete frauds;
            break;
        }
        case 6:
        {
            cout << "Entrez l'id de l'utilisateur : " << endl;
            int idUser = getInput();
            system.InitializedMeasurement();
            SensorManagement sm(model);
            bool res = sm.ClassifyAsUnreliable(idUser);
            if (res)
            {
                cout << "Utilisateur banni avec succes" << endl;
            }
            else {
                cout << "L'utilisateur est deja banni ou n'existe pas" << endl;
            }
            break;
        }
        case 7:
        {
            cout << "Entrez l'id de l'utilisateur : " << endl;
            int idUser = getInput();
            system.InitializedMeasurement();
            IndividualUser* user = model->SearchIndividual(idUser);
            if (user != nullptr) {
                cout << *user << endl;
            }
            else {
                cout << "L'utilisateur n'existe pas" << endl;
            }
            break;
        }
        case 8:
        {
            cout << "Entrez l'id du capteur : " << endl;
            int idSensor = getInput();
            Sensor* sensor = model->SearchSensor(idSensor);
            if (sensor != nullptr && sensor->GetUserID() != -1) {
                cout << "Voulez vous afficher un apercu du capteur (1) ou toutes les mesures (2)" << endl;
                int option = getInput();
                system.InitializedMeasurement();
                if (option == 1) {
                    cout << *sensor << endl;
                }
                else if (option == 2) {
                    cout << "Sensor" << sensor->GetID() << endl;
                    cout << "Etat : " << sensor->GetState() << endl;
                    if (sensor->GetUserID() != -1) {
                        cout << "Sensor de user" << sensor->GetUserID() << endl;
                    }
                    for (const auto& pair : *sensor->GetMeasurements()) {
                        for (const auto& mesure : pair.second)
                        {
                            cout << mesure << endl;
                        }
                    }
                }
                else {
                    cout << "Veuillez saisir un nombre valide" << endl;
                }
            }
            else {
                system.InitializedMeasurement();
                cout << "Le capteur n'existe pas" << endl;
            }
            break;
        }
        case 9:
            return;
        default:
            cout << "Veuillez saisir un nombre valide" << endl;
            break;
        }

        if (evalPerformance) {
            system.EndMeasurement();
            cout << "Requete traitee en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
        }
    }
}

void UserInterface::statisticsUI()
//Menu des statistiques
{

    Statistics stats(model);
    while (1) {
        cout << "------------Affichage des statistiques-------------\n"
            "\n"
            "1 - Afficher la qualite d'air moyenne d'un endroit precis via le dernier indice Atmo calcule dans la zone \n"
            "2 - Afficher la qualite d'air moyenne d'un endroit precis a une date precise via l'indice Atmo\n"
            "3 - Afficher la qualite d'air moyenne d'une zone via le dernier indice Atmo calcule dans la zone \n"
            "4 - Afficher la qualite d'air moyenne d'une zone a une date precise via l'indice Atmo\n"
            "5 - Afficher la qualite d'air moyenne d'un capteur vie un indice Atmo moyen\n"
            "6 - Retour au menu principal\n"
            "-----------------------------------------------------\n"
            << endl;
        choice = getInput();
        double x, y;
        double r = 0;
        time_t time;
        double result = 0;

        switch (choice)
        {
        case 1:
        {
            cout << "Merci d'entrer les coordonnees de l'endroit dont vous souhaitez observer la qualite d'air" << endl;
            x = getXcoord();
            y = getYcoord();
            r = 0;
            system.InitializedMeasurement();
            result = stats.CircularMeanAirQuality(x, y, r, nullptr);
            displayATMO(result, false);
            break;
        }
        case 2:
        {
            cout << "Merci d'entrer les coordonnees de l'endroit dont vous souhaitez observer la qualite d'air" << endl;
            x = getXcoord();
            y = getYcoord();
            r = 0;
            time = getTime();
            system.InitializedMeasurement();
            result = stats.CircularMeanAirQuality(x, y, r, &time);
            displayATMO(result, false);
            break;
        }
        case 3:
        {
            cout << "Merci d'entrer les coordonnees de l'endroit dont vous souhaitez observer la qualite d'air" << endl;
            x = getXcoord();
            y = getYcoord();
            r = getRayon();
            system.InitializedMeasurement();
            result = stats.CircularMeanAirQuality(x, y, r, nullptr);
            displayATMO(result, false);
            break;
        }
        case 4:
        {
            cout << "Merci d'entrer les coordonnees de l'endroit dont vous souhaitez observer la qualite d'air" << endl;
            x = getXcoord();
            y = getYcoord();
            r = getRayon();
            time = getTime();
            system.InitializedMeasurement();
            result = stats.CircularMeanAirQuality(x, y, r, &time);
            displayATMO(result, false);
            break;
        }
        case 5:
        {
            cout << "Entrez l'id du capteur : " << endl;
            int idSensor = getInput();
            Sensor* sensor = model->SearchSensor(idSensor);
            if (sensor != nullptr) {
                cout << "Utiliser les dernieres donnees (1) ou renseigner une date precise (2) ?" << endl;
                int option = getInput();
                if (option == 1) {
                    system.InitializedMeasurement();
                    result = stats.AirQualitySensor(sensor);
                    displayATMO(result, true);
                }
                else if (option == 2) {
                    time = getTime();
                    system.InitializedMeasurement();
                    result = stats.AirQualitySensor(sensor, &time);
                    displayATMO(result, true);
                }
                else {
                    system.InitializedMeasurement();
                    cout << "Veuillez saisir un nombre valide" << endl;
                }
            }
            else {
                system.InitializedMeasurement();
                cout << "Le capteur n'existe pas" << endl;
            }
            break;
        }
        case 6:
            return;

        default:
            cout << "Veuillez saisir un nombre valide" << endl;
            break;
        }

        if (evalPerformance) {
            system.EndMeasurement();
            cout << "Requete traitee en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
        }
    }
}

double UserInterface::getRayon()
//Algorithme : retourne le rayon rentré par l'utilisateur
{
    cout << " Merci d'entrer le rayon de la zone a mesurer autour du point fourni precedemment" << endl;
    double rayon = -1;
    cin >> rayon;
    while (cin.fail()) {
        cleanInputBuffer();
        cout << "Veuillez respecter le format :" << endl;
        cin >> rayon;
    }
    cleanInputBuffer();
    return rayon;
}

time_t UserInterface::getTime()
//Algorithme : retourne et formatte la date renvoyée par l'utilisateur
{
    int day, month, year;
    cout << "Merci d'entrer la date au format numerique, en saisissant un numero par ligne" << endl;
    cout << "Entrez le jour" << endl;
    day = getInput();
    cout << "Entrez le mois" << endl;
    month = getInput();
    cout << " Entrez l'annee" << endl;
    year = getInput();
    tm tmp = tm();
    tmp.tm_mday = day;
    tmp.tm_mon = month - 1;
    tmp.tm_year = year - 1900;
    time_t date = mktime(&tmp);
    return date;
}

double UserInterface::getXcoord()
//Algorithme : retourne la coordonnée saisie par l'utilisateur
{
    cout << "x : " << endl;
    double x = -1;
    cin >> x;
    while (cin.fail()) {
        cleanInputBuffer();
        cout << "Veuillez respecter le format :" << endl;
        cin >> x;
    }
    cleanInputBuffer();
    return x;
}
double UserInterface::getYcoord()
//Algorithme : retourne la coordonnée saisie par l'utilisateur
{
    cout << "y : " << endl;
    double y = -1;
    cin >> y;
    while (cin.fail()) {
        cleanInputBuffer();
        cout << "Veuillez respecter le format :" << endl;
        cin >> y;
    }
    cleanInputBuffer();
    return y;
}

void UserInterface::displayATMO(double value, bool moyenne)
// Algorithme : Affiche la valeur de l'indice atmo en fonction des paramètres entrés
{
    if (value == -1) {
        cout << "ERREUR DANS LA LECTURE DES DONNEES" << endl;
    }
    else if (value == -2) {
        cout << "Aucune donnee disponible a la date demande" << endl;
    }
    else {
        if (moyenne) {
            cout << "Indice ATMO moyen de la qualite de l'air : " << value << endl;
        }
        else {
            cout << " Indice ATMO de la qualite de l'air : " << value << endl;
        }
        cout << endl;
        cout << "L'indice Atmo a les caracteristiques suivantes : \n" <<
            "il met en evidence une pollution globale de fond, et non localisee;\n" <<
            "il tient compte des niveaux de dioxyde de soufre, dioxyde d'azote, ozone et particules fines ;\n" <<
            "il est compris entre 1 et 10;\n" <<
            "il est calcule pour une journee et pour une zone geographique; " << endl;
        cout << "Interpretation du resultat : " << endl;
        cout << "1<= indice <3 : niveau tres bon\n" <<
            "3<= indice <5 : niveau bon\n" <<
            "5<= indice <6 : niveau moyen\n" <<
            "6<= indice <8 : niveau mediocre\n" <<
            "8<= indice <10 : niveau mauvais\n" <<
            "10<= indice : niveau tres mauvais\n" << endl;
    }
}


void UserInterface::cleanInputBuffer()
// Algorithme :
// En utilisant les methodes de cin, on vide l'entree standard vu qu'il y a eu un
// depassement de capacite.
{
    char verif;
    cin.clear();		//clear() permet d'utiliser peek() apres getline() sans erreur
    verif = cin.peek(); //peek() permet de recuperer le premier caractere de l'entree

    //Si verif est un retour a la ligne alors on a fini de vider l'entree
    while (verif != '\n')
    {
        cin.ignore(); //ignore le caractere et le retire de l'entree
        verif = cin.peek();
    }
    cin.ignore(); //ignore le '\n' pour tout remettre a 0
} //----- Fin de ViderEntreeStandard