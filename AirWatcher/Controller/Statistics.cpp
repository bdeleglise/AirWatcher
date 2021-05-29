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
    System system;
    system.InitializedMeasurement();
    map<int, Sensor>* sensors = model->GetSensors();
    system.EndMeasurement();
    cout << "Etape 1 en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;

    map<int, Sensor>::iterator it = sensors->begin();
    if (sensors->empty()) {
        return -1; //Erreur
    }
    int sensorUsed = 0;
    double O3 = 0;
    double NO2 = 0;
    double PM10 = 0;
    double SO2 = 0;

    if (time == nullptr) {
        time_t timeBuffer = it->second.GetMeasurements()->crbegin()->first;
        time = &timeBuffer;
    }

    tm tmp;
    localtime_s(&tmp, time);
    tmp.tm_hour = 0;
    tmp.tm_min = 0;
    tmp.tm_sec = 0;
    time_t start = mktime(&tmp);
    tmp.tm_mday = tmp.tm_mday + 1;
    time_t end = mktime(&tmp);

    system.InitializedMeasurement();
    for (it; it != sensors->end(); ++it) {
        Sensor* sensor = &it->second;
        double distance = pow(latitude - sensor->GetLatitude(), 2) + pow(longitude - sensor->GetLongitude(), 2);
        if (distance <= (radius*radius)) {
            map<time_t, vector<Measurement>>* measurementSensor = sensor->GetMeasurements();
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
    system.EndMeasurement();
    cout << "Etape 2 en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
    system.InitializedMeasurement();
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
        return -2;
    }

    system.EndMeasurement();
    cout << "Etape 3 en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
    system.InitializedMeasurement();
    airQuality = atmoIndex(O3 / ((double)sensorUsed), SO2 / ((double)sensorUsed), NO2 / ((double)sensorUsed), PM10 / ((double)sensorUsed));

    system.EndMeasurement();
    cout << "Etape 4 en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
    system.InitializedMeasurement();
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

    if (*end < sensor->GetMeasurements()->begin()->first || *end>sensor->GetMeasurements()->crbegin()->first) 
    {
        return -2;  //Erreur la date ne rentre pas dans la plage des données
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
    System system;
    system.InitializedMeasurement();
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
        return -2;
    }

    cout << "Calculé en :  " << system.GetAlgorithmEfficiency() << " secondes" << endl;
    system.InitializedMeasurement();

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
    if (O3 <= 50) {
        sumQuality = 1;
    }
    else if (O3 <= 100) {
        sumQuality = 2;
    }
    else if (O3 <= 130) {
        sumQuality = 3;
    }
    else if (O3 <= 240) {
        sumQuality = 4;
    }
    else if (O3 <= 380) {
        sumQuality = 5;
    }
    else {
        sumQuality = 6;
    }

    if (So2 <= 100) {
        sumQuality += 1;
    }
    else if (So2 <= 200) {
        sumQuality += 2;
    }
    else if (So2 <= 350) {
        sumQuality += 3;
    }
    else if (So2 <= 500) {
        sumQuality += 4;
    }
    else if (So2 <= 750) {
        sumQuality += 5;
    }
    else {
        sumQuality += 6;
    }

    if (No2 <= 40) {
        sumQuality += 1;
    }
    else if (No2 <= 90) {
        sumQuality += 2;
    }
    else if (No2 <= 120) {
        sumQuality += 3;
    }
    else if (No2 <= 230) {
        sumQuality += 4;
    }
    else if (No2 <= 340) {
        sumQuality += 5;
    }
    else {
        sumQuality += 6;
    }

    if (Pm10 <= 20) {
        sumQuality += 1;
    }
    else if (Pm10 <= 40) {
        sumQuality += 2;
    }
    else if (Pm10 <= 50) {
        sumQuality += 3;
    }
    else if (Pm10 <= 100) {
        sumQuality += 4;
    }
    else if (Pm10 <= 150) {
        sumQuality += 5;
    }
    else {
        sumQuality += 6;
    }


    meanFactor = sumQuality / 4.0;

    return meanFactor;
}
