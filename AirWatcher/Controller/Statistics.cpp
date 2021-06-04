/*************************************************************************
                           Statistics  -  description
                             -------------------
    début                : 06/05/2021
    copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
    e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
                           benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/
#include "Statistics.h"
#include <vector>
#include "../Model/Model.h"
#include "System.h"
using namespace std;

int Statistics::CircularMeanAirQuality(double latitude, double longitude, double radius, time_t* time)
//Algorithme : 
{
    if (model == nullptr) {
        return -1;
    }
    int airQuality = 0;

    map<int, Sensor>* sensors = model->GetSensors();
    

    map<int, Sensor>::iterator it = sensors->begin();
    if (sensors->empty()) {
        return -1; //Erreur
    }

    int sensorUsed = 0;
    // on initialise les indices de la qualité de l'air à 0
    double O3 = 0;
    double NO2 = 0;
    double PM10 = 0;
    double SO2 = 0;

    // on initialise les temps et les dates des données 
    time_t start;
    time_t end;
    if (time != nullptr) {
        tm tmp;
        localtime_s(&tmp, time);
        tmp.tm_hour = 0;
        tmp.tm_min = 0;
        tmp.tm_sec = 0;
        start = mktime(&tmp);
        tmp.tm_mday = tmp.tm_mday + 1;
        end = mktime(&tmp);
    }



    // on parcourt les capteurs 
    for (it; it != sensors->end(); ++it) {
        Sensor* sensor = &it->second;
        // on calcule la distance au centre de la zone du capteur parcouru
        double distance = pow(latitude - sensor->GetLatitude(), 2) + pow(longitude - sensor->GetLongitude(), 2);
        if (distance <= (radius*radius)) {
            map<time_t, vector<Measurement>>* measurementSensor = sensor->GetMeasurements();
            // on initialise les dates des données aux dernières dates de mesure du capteur parcouru
            if (time == nullptr) {
                time_t timebuffer = measurementSensor->crbegin()->first;
                tm tmp;
                localtime_s(&tmp, &timebuffer);
                tmp.tm_hour = 0;
                tmp.tm_min = 0;
                tmp.tm_sec = 0;
                start = mktime(&tmp);
                tmp.tm_mday = tmp.tm_mday + 1;
                end = mktime(&tmp);
               
            }
            // on récupère les mesures réalisées par le capteur à la date prise dernièrement 
            map<time_t, vector<Measurement>>::iterator itMes = measurementSensor->lower_bound(start);
            
            int nbMesureSensor = 0;
            double buffO3 = 0;
            double buffNO2 = 0;
            double buffPM10 = 0;
            double buffSO2 = 0;
            // on parcourt les mesures 
            while (itMes != measurementSensor->end() && itMes->first<end) {
                // on incrémente nbMesureSensor qui est le nombre de mesures réalisées par le capteur
                // à la date prise dernièrement 
                nbMesureSensor++;
                vector<Measurement>::iterator itMeasure;

                // on init les buff_Indice avec les mesures réalisées à la date prise dernièrement
                for (itMeasure = itMes->second.begin(); itMeasure != itMes->second.end(); ++itMeasure) {
                    string idAttribute = itMeasure->GetAttribute().GetID();
                    if (idAttribute == "O3") {
                        buffO3 += itMeasure->GetValue();
                    }
                    else if (idAttribute == "NO2") {
                        buffNO2 += itMeasure->GetValue();
                    }
                    else if (idAttribute == "SO2") {
                        buffSO2 += itMeasure->GetValue();
                    }
                    else if (idAttribute == "PM10") {
                        buffPM10 += itMeasure->GetValue();
                    }
                    else {
                        return -1;
                    }
                }
                itMes++;
            }
            // on somme les indices actuels avec ceux réalisés dernièrement et on incrémente sensorUsed.
            if (nbMesureSensor != 0) {
                sensorUsed++;
                O3 += buffO3 / nbMesureSensor;
                NO2 += buffNO2 / nbMesureSensor;
                PM10 += buffPM10 / nbMesureSensor;
                SO2 += buffSO2 / nbMesureSensor;
                if (sensor->GetUserID() != -1) {
                    model->IncrementPointIndividualUser(sensor->GetUserID());
                }
            }
            
        }
    }

    if (sensorUsed == 0) {
        // Si on a utilisé aucun capteur à l'étape précédente, càd aucun capteur disponible dans la zone spécifiée par l'utilsateur :
        // on recherche les 3 capteurs les plus proches des coordonnées de la liste des capteurs 
        vector<Sensor*> copySensors;
        for (auto& pair : *sensors) {
            copySensors.push_back(&pair.second);
        }
        vector<Sensor*> nearSensors(3); 
        partial_sort_copy(copySensors.begin(), copySensors.end(), nearSensors.begin(), nearSensors.end(), [latitude, longitude](Sensor* s1, Sensor* s2) {
            double d1 = pow(latitude - s1->GetLatitude(), 2) + pow(longitude - s1->GetLongitude(), 2);
            double d2 = pow(latitude - s2->GetLatitude(), 2) + pow(longitude - s2->GetLongitude(), 2);
            return (d1 < d2);
        });


        double tabDist[3];
        double sumDist = 0;
        int index = 0;

        // pour chaque capteur voisin 
        for (auto& currentSensor : nearSensors) {
            // on calcule la distance au centre de la zone du capteur voisin parcouru
            double distance = sqrt(pow(latitude - currentSensor->GetLatitude(), 2) + pow(longitude - currentSensor->GetLongitude(), 2)) - radius;
            tabDist[index] = distance;
            // on incrémente la somme des distances 
            sumDist += distance;
            index++;
        }
        // on calcule la distance pondérée
        double ponderDist = sumDist - sumDist / 3;
        index = 0;

        // on re-parcourt les capteurs voisins 
        for (auto& currentSensor : nearSensors) {
            map<time_t, vector<Measurement>>* measurementSensor = currentSensor->GetMeasurements();
            // on init les dates des données aux dernières dates de mesure du capteur
            if (time == nullptr) {
                time_t timebuffer = measurementSensor->crbegin()->first;
                tm tmp;
                localtime_s(&tmp, &timebuffer);
                tmp.tm_hour = 0;
                tmp.tm_min = 0;
                tmp.tm_sec = 0;
                start = mktime(&tmp);
                tmp.tm_mday = tmp.tm_mday + 1;
                end = mktime(&tmp);
            }
            // on récupère les mesures réalisées par le capteur à la date prise dernièrement 
            map<time_t, vector<Measurement>>::iterator itMes = measurementSensor->lower_bound(start);
            int nbMesureSensor = 0;
            double buffO3 = 0;
            double buffNO2 = 0;
            double buffPM10 = 0;
            double buffSO2 = 0;
            while (itMes != measurementSensor->end() && itMes->first < end) {
                nbMesureSensor++;
                vector<Measurement>::iterator itMeasure;
                // on init les buff_Indice avec les mesures réalisées à la date prise dernièrement
                for (itMeasure = itMes->second.begin(); itMeasure != itMes->second.end(); ++itMeasure) {
                    string idAttribute = itMeasure->GetAttribute().GetID();
                    double value = itMeasure->GetValue(); 
                    if (idAttribute == "O3") {
                        buffO3 += value;
                    }
                    else if (idAttribute == "NO2") {
                        buffNO2 += value;
                    }
                    else if (idAttribute == "SO2") {
                        buffSO2 += value;
                    }
                    else if (idAttribute == "PM10") {
                        buffPM10 += value;
                    }
                    else {
                        return -1;
                    }
                }
              
                itMes++;
            }
            // on calcule les nouvelles valeurs des indices 
            // valeur_indice += valeur_indice_dernièrement * (somme_distance-distance_capteur[index]) /
            // distance_pondérée*nombre_mesures 
            if (nbMesureSensor != 0) {
                sensorUsed++;
                O3 += (buffO3 * (sumDist - tabDist[index]) / ponderDist) / nbMesureSensor; //pondération
                NO2 += (buffNO2 * (sumDist - tabDist[index]) / ponderDist) / nbMesureSensor;
                PM10 += (buffPM10 * (sumDist - tabDist[index]) / ponderDist) / nbMesureSensor;
                SO2 += (buffSO2 * (sumDist - tabDist[index]) / ponderDist) / nbMesureSensor;
                if (currentSensor->GetUserID() != -1) {
                    model->IncrementPointIndividualUser(currentSensor->GetUserID());
                }
            }
            index++;

        }
    }
    if (sensorUsed == 0) {
        return -2; //Erreur la date ne rentre pas dans la plage des données
    }

    // on calcule finalement la qualité de l'air
    airQuality = atmoIndex(O3 / ((double)sensorUsed), SO2 / ((double)sensorUsed), NO2 / ((double)sensorUsed), PM10 / ((double)sensorUsed));

    return airQuality;
}

double Statistics::AirQualitySensor(Sensor* sensor, time_t* end)
//Algorithme : permet de récupérer la qualité de l’air moyenne sur la semaine avant la date « end » ou sur la dernière semaine si l’attribut est nul du capteur en paramètre.  
{

    if (sensor == nullptr || model ==nullptr)
    {
        return -1;  //Erreur le sensor est null
    }

    // si end est null, on init timeBuffer à la date de la dernière mesure
    if (end == nullptr) 
    {
        time_t timeBuffer = sensor->GetMeasurements()->crbegin()->first;
        end = &timeBuffer;
    }

    // on initialise les temps sur une semaine avant la dernière mesure 
    tm* time = new tm();
    localtime_s(time, end);
    time->tm_hour = 0;
    time->tm_min = 0;
    time->tm_sec = 0;
    time->tm_mday = time->tm_mday + 1;
    *end = mktime(time);
    time->tm_mday = time->tm_mday - 7;
    time_t start = mktime(time);
    time->tm_mday = time->tm_mday + 1;
    time_t next = mktime(time);

   
    double indexAtmoWeek = 0;
    int numberIndex = 0;
    // pour chaque jour, allant de la semaine avant la dernière mesure jusqu'à la dernière mesure 
    while (start < *end) {
        map<time_t, vector<Measurement>>* measurementSensor = sensor->GetMeasurements();
        // on obtient les mesures faites à la denrnière semaine 
        map<time_t, vector<Measurement>>::iterator itMes = measurementSensor->lower_bound(start);
        int numberMesure = 0;
        double O3 = 0;
        double NO2 = 0;
        double PM10 = 0;
        double SO2 = 0;
        // on parcourt les mesures réalisées
        while (itMes != measurementSensor->end() && itMes->first < next) {
            numberMesure++;
            vector<Measurement>::iterator itMeasure;

            // on met à jour les valeurs des indices de qualité de l'air 
            for (itMeasure = itMes->second.begin(); itMeasure != itMes->second.end(); ++itMeasure) {
                string idAttribute = itMeasure->GetAttribute().GetID();
                double value = itMeasure->GetValue();
                if (idAttribute == "O3") {
                    O3 += value;
                }
                else if (idAttribute == "NO2") {
                    NO2 += value;
                }
                else if (idAttribute == "SO2") {
                    SO2 += value;
                }
                else if (idAttribute == "PM10") {
                    PM10 += value;
                }
                else {
                    return -1; //Erreur dans la lecture des mesures
                }
            }

            itMes++;
        }
        // on calcule alors l'index ATMO sur la semaine totale 
        if (numberMesure != 0) {
            numberIndex++;
            indexAtmoWeek += atmoIndex(O3 / ((double)numberMesure), SO2 / ((double)numberMesure), NO2 / ((double)numberMesure), PM10 / ((double)numberMesure));
        }
        time->tm_mday = time->tm_mday + 1;
        start = next;
        next = mktime(time);
    }

    if (numberIndex == 0) {
        return -2; //Erreur la date ne rentre pas dans la plage des données
    }

  
    delete time;
    return indexAtmoWeek/numberIndex;
}

Statistics::Statistics(Model* unModel)
    : model(unModel)
{
}






int Statistics::atmoIndex(double O3, double So2, double No2, double Pm10)
// Algorithme : retourne l'index ATMO selon les normes spécifiées avant l'introduction de PM2.5 à l'indice
{
    int index = -1;
    int currentIdex = 0;
    if (O3 <= 29) {
        index = 1;
    }
    else if (O3 <= 54) {
        index = 2;
    }
    else if (O3 <= 79) {
        index = 3;
    }
    else if (O3 <= 104) {
        index = 4;
    }
    else if (O3 <= 129) {
        index = 5;
    }
    else if (O3 <= 149) {
        index = 6;
    }
    else if (O3 <= 179) {
        index = 7;
    }
    else if (O3 <= 209) {
        index = 8;
    }
    else if (O3 <= 239) {
        index = 9;
    }
    else {
        index = 10;
    }

    if (So2 <= 39) {
        currentIdex = 1;
    }
    else if (So2 <= 79) {
        currentIdex = 2;
    }
    else if (So2 <= 119) {
        currentIdex = 3;
    }
    else if (So2 <= 159) {
        currentIdex = 4;
    }
    else if (So2 <= 199) {
        currentIdex = 5;
    }
    else if (So2 <= 249) {
        currentIdex = 6;
    }
    else if (So2 <= 299) {
        currentIdex = 7;
    }
    else if (So2 <= 399) {
        currentIdex = 8;
    }
    else if (So2 <= 499) {
        currentIdex = 9;
    }
    else {
        currentIdex = 10;
    }

    index = max(index, currentIdex);

    if (No2 <= 29) {
        currentIdex = 1;
    }
    else if (No2 <= 54) {
        currentIdex = 2;
    }
    else if (No2 <= 84) {
        currentIdex = 3;
    }
    else if (No2 <= 109) {
        currentIdex = 4;
    }
    else if (No2 <= 134) {
        currentIdex = 5;
    }
    else if (No2 <= 164) {
        currentIdex = 6;
    }
    else if (No2 <= 199) {
        currentIdex = 7;
    }
    else if (No2 <= 274) {
        currentIdex = 8;
    }
    else if (No2 <= 399) {
        currentIdex = 9;
    }
    else {
        currentIdex = 10;
    }

    index = max(index, currentIdex);

    if (Pm10 <= 6) {
        currentIdex = 1;
    }
    else if (Pm10 <= 13) {
        currentIdex = 2;
    }
    else if (Pm10 <= 20) {
        currentIdex = 3;
    }
    else if (Pm10 <= 27) {
        currentIdex = 4;
    }
    else if (Pm10 <= 34) {
        currentIdex = 5;
    }
    else if (Pm10 <= 41) {
        currentIdex = 6;
    }
    else if (Pm10 <= 49) {
        currentIdex = 7;
    }
    else if (Pm10 <= 64) {
        currentIdex = 8;
    }
    else if (Pm10 <= 79) {
        currentIdex = 9;
    }
    else {
        currentIdex = 10;
    }

    index = max(index, currentIdex);

    return index;
}
