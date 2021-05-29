#include "Statistics.h"
#include <vector>
#include "../Model/Model.h"
#include "System.h"
using namespace std;

double Statistics::CircularMeanAirQuality(double latitude, double longitude, double radius, time_t* time)
{
    if (model == nullptr) {
        return -1;
    }
    double airQuality = 0;

    map<int, Sensor>* sensors = model->GetSensors();
    

    map<int, Sensor>::iterator it = sensors->begin();
    if (sensors->empty()) {
        return -1; //Erreur
    }
    int sensorUsed = 0;
    double O3 = 0;
    double NO2 = 0;
    double PM10 = 0;
    double SO2 = 0;

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




    for (it; it != sensors->end(); ++it) {
        Sensor* sensor = &it->second;
        double distance = pow(latitude - sensor->GetLatitude(), 2) + pow(longitude - sensor->GetLongitude(), 2);
        if (distance <= (radius*radius)) {
            map<time_t, vector<Measurement>>* measurementSensor = sensor->GetMeasurements();
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
            map<time_t, vector<Measurement>>::iterator itMes = measurementSensor->lower_bound(start);
            
            int nbMesureSensor = 0;
            double buffO3 = 0;
            double buffNO2 = 0;
            double buffPM10 = 0;
            double buffSO2 = 0;
            while (itMes != measurementSensor->end() && itMes->first<end) {
                nbMesureSensor++;
                vector<Measurement>::iterator itMeasure;

                for (itMeasure = itMes->second.begin(); itMeasure != itMes->second.end(); ++itMeasure) {
                    string idAttribute = itMeasure->GetAttribute().GetID();
                    if (idAttribute == "O3") {
                        buffO3 += itMeasure->GetValue();
                    }
                    else if (idAttribute == "NO2") {
                        buffNO2 += itMeasure->GetValue();
                    }
                    else if (idAttribute == "SO2") {
                        buffPM10 += itMeasure->GetValue();
                    }
                    else if (idAttribute == "PM10") {
                        buffSO2 += itMeasure->GetValue();
                    }
                    else {
                        return -1;
                    }
                }
                itMes++;
            }
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
        vector<Sensor*> copySensors;
        for (auto& pair : *sensors) {
            copySensors.push_back(&pair.second);
        }
        vector<Sensor*> nearSensors(3); //sans new et sans étoile
        partial_sort_copy(copySensors.begin(), copySensors.end(), nearSensors.begin(), nearSensors.end(), [latitude, longitude](Sensor* s1, Sensor* s2) {
            double d1 = pow(latitude - s1->GetLatitude(), 2) + pow(longitude - s1->GetLongitude(), 2);
            double d2 = pow(latitude - s2->GetLatitude(), 2) + pow(longitude - s2->GetLongitude(), 2);
            return (d1 < d2);
        });


        double tabDist[3];
        double sumDist = 0;
        int index = 0;

        for (auto& currentSensor : nearSensors) {
            double distance = sqrt(pow(latitude - currentSensor->GetLatitude(), 2) + pow(longitude - currentSensor->GetLongitude(), 2)) - radius;
            tabDist[index] = distance;
            sumDist += distance;
            index++;
        }
        double ponderDist = sumDist - sumDist / 3;
        index = 0;

        for (auto& currentSensor : nearSensors) {
            map<time_t, vector<Measurement>>* measurementSensor = currentSensor->GetMeasurements();
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
            map<time_t, vector<Measurement>>::iterator itMes = measurementSensor->lower_bound(start);
            int nbMesureSensor = 0;
            double buffO3 = 0;
            double buffNO2 = 0;
            double buffPM10 = 0;
            double buffSO2 = 0;
            while (itMes != measurementSensor->end() && itMes->first < end) {
                nbMesureSensor++;
                vector<Measurement>::iterator itMeasure;

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
                        return -1;
                    }
                }
              
                itMes++;
            }
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

    
    airQuality = atmoIndex(O3 / ((double)sensorUsed), SO2 / ((double)sensorUsed), NO2 / ((double)sensorUsed), PM10 / ((double)sensorUsed));

    return airQuality;
}

double Statistics::AirQualitySensor(Sensor* sensor, time_t* end)
{

    if (sensor == nullptr || model ==nullptr)
    {
        return -1;  //Erreur le sensor est null
    }

    if (end == nullptr) 
    {
        time_t timeBuffer = sensor->GetMeasurements()->crbegin()->first;
        end = &timeBuffer;
    }


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
    while (start < *end) {
        map<time_t, vector<Measurement>>* measurementSensor = sensor->GetMeasurements();
        map<time_t, vector<Measurement>>::iterator itMes = measurementSensor->lower_bound(start);
        int numberMesure = 0;
        double O3 = 0;
        double NO2 = 0;
        double PM10 = 0;
        double SO2 = 0;
        while (itMes != measurementSensor->end() && itMes->first < next) {
            numberMesure++;
            vector<Measurement>::iterator itMeasure;

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






double Statistics::atmoIndex(double O3, double So2, double No2, double Pm10)
{
    double meanFactor=0;
    double sumQuality = 0;
    if (O3 <= 29) {
        sumQuality = 1;
    }
    else if (O3 <= 54) {
        sumQuality = 2;
    }
    else if (O3 <= 79) {
        sumQuality = 3;
    }
    else if (O3 <= 104) {
        sumQuality = 4;
    }
    else if (O3 <= 129) {
        sumQuality = 5;
    }
    else if (O3 <= 149) {
        sumQuality = 6;
    }
    else if (O3 <= 179) {
        sumQuality = 7;
    }
    else if (O3 <= 209) {
        sumQuality = 8;
    }
    else if (O3 <= 239) {
        sumQuality = 9;
    }
    else {
        sumQuality = 10;
    }

    if (So2 <= 39) {
        sumQuality += 1;
    }
    else if (So2 <= 79) {
        sumQuality += 2;
    }
    else if (So2 <= 119) {
        sumQuality += 3;
    }
    else if (So2 <= 159) {
        sumQuality += 4;
    }
    else if (So2 <= 199) {
        sumQuality += 5;
    }
    else if (So2 <= 249) {
        sumQuality += 6;
    }
    else if (So2 <= 299) {
        sumQuality += 7;
    }
    else if (So2 <= 399) {
        sumQuality += 8;
    }
    else if (So2 <= 499) {
        sumQuality += 9;
    }
    else {
        sumQuality += 10;
    }

    if (No2 <= 29) {
        sumQuality += 1;
    }
    else if (No2 <= 54) {
        sumQuality += 2;
    }
    else if (No2 <= 84) {
        sumQuality += 3;
    }
    else if (No2 <= 109) {
        sumQuality += 4;
    }
    else if (No2 <= 134) {
        sumQuality += 5;
    }
    else if (No2 <= 164) {
        sumQuality += 6;
    }
    else if (No2 <= 199) {
        sumQuality += 7;
    }
    else if (No2 <= 274) {
        sumQuality += 8;
    }
    else if (No2 <= 399) {
        sumQuality += 9;
    }
    else {
        sumQuality += 10;
    }

    if (Pm10 <= 6) {
        sumQuality += 1;
    }
    else if (Pm10 <= 13) {
        sumQuality += 2;
    }
    else if (Pm10 <= 20) {
        sumQuality += 3;
    }
    else if (Pm10 <= 27) {
        sumQuality += 4;
    }
    else if (Pm10 <= 34) {
        sumQuality += 5;
    }
    else if (Pm10 <= 41) {
        sumQuality += 6;
    }
    else if (Pm10 <= 49) {
        sumQuality += 7;
    }
    else if (Pm10 <= 64) {
        sumQuality += 8;
    }
    else if (Pm10 <= 79) {
        sumQuality += 9;
    }
    else {
        sumQuality += 10;
    }


    meanFactor = sumQuality / 4.0;

    return meanFactor;
}
