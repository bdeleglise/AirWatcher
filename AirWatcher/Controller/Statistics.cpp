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

    if (*time < it->second.GetMeasurements()->begin()->first || *time>it->second.GetMeasurements()->crbegin()->first)
    {
        return -2;  //Erreur la date ne rentre pas dans la plage des données
    }

    system.InitializedMeasurement();
    for (it; it != sensors->end(); ++it) {
        Sensor* sensor = &it->second;
        double distance = pow(latitude - sensor->GetLatitude(), 2) + pow(longitude - sensor->GetLongitude(), 2);
        if (distance <= (radius*radius)) {
            sensorUsed++;
            vector<Measurement>* measuresSensor = sensor->GetMeasurements(*time);
            if (measuresSensor != nullptr) {
                vector<Measurement>::iterator itMeasure;

                for (itMeasure = measuresSensor->begin(); itMeasure != measuresSensor->end(); ++itMeasure) {
                    string idAttribute = itMeasure->GetAttribute().GetID();
                    if (idAttribute == "O3") {
                        O3 += itMeasure->GetValue();
                    }
                    else if (idAttribute == "NO2") {
                        NO2 += itMeasure->GetValue();
                    }
                    else if (idAttribute == "SO2") {
                        SO2 += itMeasure->GetValue();
                    }
                    else if (idAttribute == "PM10") {
                        PM10 += itMeasure->GetValue();
                    }
                    else {
                        return -1;
                    }
                }
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
            // des choses
        }
        vector<Sensor*> nearSensors(3); //sans new et sans étoile
        partial_sort_copy(copySensors.begin(), copySensors.end(), nearSensors.begin(), nearSensors.end(), [latitude, longitude](Sensor* s1, Sensor* s2) {
            double d1 = pow(latitude - s1->GetLatitude(), 2) + pow(longitude - s1->GetLongitude(), 2);
            double d2 = pow(latitude - s2->GetLatitude(), 2) + pow(longitude - s2->GetLongitude(), 2);
            return (d1 < d2);
        });

        sensorUsed = 3;
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
            vector<Measurement>* measuresSensor = currentSensor->GetMeasurements(*time);
            if (measuresSensor != nullptr) {

                for (auto& currentMeasure : *measuresSensor) {
                    string idAttribute = currentMeasure.GetAttribute().GetID();
                    double value = currentMeasure.GetValue() * (sumDist - tabDist[index]) / ponderDist; //pondération
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
                if (currentSensor->GetUserID() != -1) {
                    model->IncrementPointIndividualUser(currentSensor->GetUserID());
                }
            }
            index++;
        }
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
    time->tm_mday = time->tm_mday - 6;
    time_t currentDate = mktime(time);

    if (currentDate < sensor->GetMeasurements()->begin()->first) {
        currentDate = sensor->GetMeasurements()->begin()->first;
    }
    int numberDay = 0;
    double O3 = 0;
    double NO2 = 0;
    double PM10 = 0;
    double SO2 = 0;
    
    System system;
    system.InitializedMeasurement();

    while (currentDate <= *end) {
        vector<Measurement>* measuresSensor = sensor->GetMeasurements(currentDate);
        if (measuresSensor != nullptr) {
            numberDay++;
            vector<Measurement>::iterator itMeasure;

            for (itMeasure = measuresSensor->begin(); itMeasure != measuresSensor->end(); ++itMeasure) {
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
        }
        localtime_s(time, &currentDate);
        time->tm_mday = time->tm_mday + 1;
        currentDate = mktime(time);
    }
    
    double airQuality = atmoIndex(O3 / ((double)numberDay), SO2 / ((double)numberDay), NO2 / ((double)numberDay), PM10 / ((double)numberDay));

    cout << "Calculé en :  " << system.GetAlgorithmEfficiency() << " secondes" << endl;
    system.InitializedMeasurement();

    delete time;
    return airQuality;
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
