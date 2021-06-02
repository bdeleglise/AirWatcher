#include <iostream>
#include <string>
using namespace std;

#include "UserInterface.h"

UserInterface::UserInterface(Model* unModel)
    : model(unModel), evalPerformance(false), system()
{
}

int UserInterface::getInput()
//Récuperer le choix de l'utilisateur
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
        while(1) {
        cout<<    "------------Menu principal-------------"
                "\n"
                "1 - Afficher des statistiques\n"
                "2 - Afficher la page des capteurs\n"
                "3 - Afficher la page des capteurs privés\n"
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
                cout << "A bientôt" << endl;
                return;
            default:
                
                cout << "Veuillez saisir un nombre valide svp" << endl;
            }
        }
}



void UserInterface::sensorUI()
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
                cout << "Une erreur c'est produite" << endl;
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
            map<int, Sensor>*sensors = model->GetSensors();
            if (sensors == nullptr) {
                cout << "Une erreur c'est produite" << endl;
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
                cout << "Une erreur c'est produite" << endl;
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
                cout << "Voulez vous afficher un aperçu du capteur (1) ou toutes les mesures (2)" << endl;
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
            cout << "Requete traite en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
        }
    }
}

void UserInterface::cleanerAnalysisUI()
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
                cout << "Une erreur c'est produite" << endl;
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
            map<int, Provider>*providers = model->GetProviders();
            if (providers == nullptr) {
                cout << "Une erreur c'est produite" << endl;
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
                cout << "L'entreprise n'existe pas" << endl;
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
            cout << "Requete traite en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
        }
    }
}

void UserInterface::privateSensorsUI()
{
    while (1) {
        cout << "------------Affichage des capteurs privés-------------\n"
            "\n"
            "1 - Afficher la liste de TOUS les capteurs privés \n"
            "2 - Afficher la liste de TOUS les utilisateurs\n"
            "3 - Afficher la liste des capteurs privés honnêtes\n"
            "4 - Afficher la liste des capteurs privés malhonnetes\n"
            "5 - Détecter les capteurs potentiellement frauduleux\n"
            "6 - Passer un utilisateur comme frauduleux\n"
            "7 - Rechercher un utilisateur \n"
            "8 - Rechercher un capteur privé\n"
            "9 - Retour au menu principal\n"
            "-----------------------------------------------------\n"
            << endl;
        choice = getInput();
       
        switch (choice)
        {
        case 1:
        {
            system.InitializedMeasurement();
            map<int, Sensor>*sensors = model->GetPrivateSensors();
            map<int, Sensor>* sensorsMal = model->GetMaliciousIndividualSensors();
            if (sensors == nullptr || sensorsMal ==nullptr) {
                cout << "Une erreur c'est produite" << endl;
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
            map<int, IndividualUser>*users = model->GetIndividuals();
            if (users == nullptr) {
                cout << "Une erreur c'est produite" << endl;
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
            map<int, Sensor>*sensors = model->GetPrivateSensors();
            if (sensors == nullptr) {
                cout << "Une erreur c'est produite" << endl;
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
            map<int, Sensor>*sensorsMal = model->GetMaliciousIndividualSensors();
            if (sensorsMal == nullptr) {
                cout << "Une erreur c'est produite" << endl;
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
                    "Pourcentage d'erreur  : " << currentPair.second.second << "\n"
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
                cout << "Utilisateur banni avec succès" << endl;
            }
            else {
                cout << "L'utilisateur n'existe pas" << endl;
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
            system.InitializedMeasurement();
            Sensor* sensor = model->SearchSensor(idSensor);
            if (sensor != nullptr && sensor->GetUserID() != -1) {
                cout << "Voulez vous afficher un aperçu du capteur (1) ou toutes les mesures (2)" << endl;
                int option = getInput();
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
            cout << "Requete traite en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
        }
    }
}

void UserInterface::statisticsUI()
//Menu statistiques
{

    Statistics stats(model);
    while (1) {
        cout << "------------Affichage des statistiques-------------\n"
            "\n"
            "1 - Afficher la qualite d'air moyenne d'un endroit precis via le dernier indice Atmo calcule dans la zone \n"
            "2 - Afficher la qualite d'air moyenne d'un endroit precis à une date precise via l'indice Atmo\n"
            "3 - Afficher la qualite d'air moyenne d'une zone via le dernier indice Atmo calcule dans la zone \n"
            "4 - Afficher la qualite d'air moyenne d'une zone à une date precise via l'indice Atmo\n"
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
                system.InitializedMeasurement();
                if (option == 1) {
                    result = stats.AirQualitySensor(sensor);
                    displayATMO(result, true);
                }
                else if (option == 2) {
                    time = getTime();
                    result = stats.AirQualitySensor(sensor,&time);
                    displayATMO(result, true);
                }
                else {
                    cout << "Veuillez saisir un nombre valide" << endl;
                }
            }
            else {
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
            cout << "Requete traite en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
        }
    }
}

double UserInterface::getRayon()
{
    cout << " Merci d'entrer le rayon de la zone à mesurer autour du point fourni precedemment" << endl;
    double rayon=-1;
    while (cin.fail()) {
        cleanInputBuffer();
        cout << "Veuillez respecter le format :" << endl;
        cin >> rayon;
    }
    cleanInputBuffer();
    return rayon;
}

time_t UserInterface::getTime()
{
    int day, month, year;
    cout << "Merci d'entrer la date au format numerique, en saisissant un numero par ligne" << endl;
    cout << "Entrez le jour" << endl;
    day = getInput();
    cout << "Entrez le mois" << endl;
    month = getInput();
    cout << " Entrez l'année" << endl;
    year = getInput();
    tm tmp = tm();
    tmp.tm_mday = day;
    tmp.tm_mon = month - 1;
    tmp.tm_year = year - 1900;
    time_t date = mktime(&tmp);
    return date;
}

double UserInterface::getXcoord()
{
    cout << "x : " << endl;
    double x = -1;
    while (cin.fail()) {
        cleanInputBuffer();
        cout << "Veuillez respecter le format :" << endl;
        cin >> x;
    }
    cleanInputBuffer();
    return x;
}
double UserInterface::getYcoord()
{
    cout << "y : " << endl;
    double y = -1;
    while (cin.fail()) {
        cleanInputBuffer();
        cout << "Veuillez respecter le format :" << endl;
        cin >> y;
    }
    cleanInputBuffer();
    return y;
}

void UserInterface::displayATMO(double value, bool moyenne)
{
    if (value == -1) {
        cout << "ERREUR DANS LA LECTURE DES DONNEES" << endl;
    }
    else if (value == -2) {
        cout << "Aucune donnee disponible a la date demande" << endl;
    }
    else {
        if (moyenne) {
            cout << "Indice ATMO moyen de la qualité de l'air : "<<value  << endl;
        }
        else {
            cout << " Indice ATMO  de la qualité de l'air : " << value << endl;
        }
        cout << endl;
        cout << "L'indice Atmo a les caractéristiques suivantes : \n" <<
            "il met en évidence une pollution globale de fond, et non localisée; _\n" <<
            "il tient compte des niveaux de dioxyde de soufre, dioxyde d'azote, ozone et particules fines ;\n" <<
            "il est compris entre 1 et 10;\n" <<
            "il est calculé pour une journée et pour une zone géographique; " << endl;
        cout << "Interpretation du résultat : " << endl;
        cout << "1<= indice <3 : niveau très bon\n" <<
            "3<= indice <5 : niveau bon\n" <<
            "5<= indice <6 : niveau moyen\n" <<
            "6<= indice <8 : niveau médiocre\n" <<
            "8<= indice <10 : niveau mauvais\n" <<
            "10<= indice : niveau très mauvais\n" << endl;
    }
}


void UserInterface::cleanInputBuffer()
// Algorithme :
// En utilisant les méthodes de cin, on vide l'entrée standard vu qu'il y a eu un
// dépasssement de capacité.
{
    char verif;
    cin.clear();		//clear() permet d'utiliser peek() après getline() sans erreur
    verif = cin.peek(); //peek() permet de récupérer le premier caractère de l'entrée

    //Si vérif est un retour à la ligne alors on a fini de vider l'entrée
    while (verif != '\n')
    {
        cin.ignore(); //ignore le caractère et le retire de l'entrée
        verif = cin.peek();
    }
    cin.ignore(); //ignore le '\n' pour tout remettre à 0
} //----- Fin de ViderEntreeStandard