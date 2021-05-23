#include "Statistics.h"
#include <vector>
#include "../Model/Model.h"
#include "System.h"
using namespace std;

/** Version 1
 * double Statistics::CircularMeanAirQuality(double latitude, double longitude, double radius, time_t* time)
{
    double airQuality = 0; 
    System system;
    system.InitializedMeasurement();
    vector<pair<Sensor, double>>* sensors = Model::GetSensorsOrderByDistance(latitude, longitude);
    system.EndMeasurement();
    cout << "Etape 1 en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;

    vector<pair<Sensor, double>>::iterator it = sensors->begin();
    if (sensors->empty()) {
        return -1; //Erreur
    }
    int sensorUsed = 0;
    double O3 = 0;
    double NO2 = 0;
    double PM10 = 0;
    double SO2 = 0;

    if (time == nullptr) {
        time_t timeBuffer = it->first.GetMeasurements()->crbegin()->first;       
        time=&timeBuffer;
    }
    system.InitializedMeasurement();
    for (it; it != sensors->end(); ++it) {
        double distance = it->second;
        Sensor* sensor = &it->first;
    
        if (distance <= radius) {
            


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
                    Model::IncrementPointIndividualUser(sensor->GetUserID());
                }
            }
        }
        else{
            break;
        }
       
    }
    system.EndMeasurement();
    cout << "Etape 2 en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;

    system.InitializedMeasurement();
    if (sensorUsed == 0) {
        sensorUsed = 3;
        double tabDist[3];
        double sumDist = 0;

        for (int i = 0; i < 3; i++) {
            double distance = it->second-radius;
            tabDist[i] = distance;
            sumDist += distance;
            ++it;
        }
        double ponderDist = sumDist - sumDist / 3;


        it = sensors->begin();
        for (int i = 0; i < 3; i++) {
            Sensor* sensor = &it->first;

            vector<Measurement>* measuresSensor = sensor->GetMeasurements(*time);
            if (measuresSensor != nullptr) {
                vector<Measurement>::iterator itMeasure;

                for (itMeasure = measuresSensor->begin(); itMeasure != measuresSensor->end(); ++itMeasure) {
                    string idAttribute = itMeasure->GetAttribute().GetID();
                    double value = itMeasure->GetValue()*(sumDist - tabDist[i]) / ponderDist; //pondération
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
                if (sensor->GetUserID() != -1) {
                    Model::IncrementPointIndividualUser(sensor->GetUserID());
                }
            }
            ++it;
        }
    }
    system.EndMeasurement();
    cout << "Etape 3 en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
    system.InitializedMeasurement();
    airQuality = atmoIndex(O3/((double)sensorUsed), SO2/ ((double)sensorUsed), NO2/ ((double)sensorUsed), PM10/ ((double)sensorUsed));

    system.EndMeasurement();
    cout << "Etape 4 en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
    system.InitializedMeasurement();
    delete sensors;
    return airQuality;
}  **/

double Statistics::CircularMeanAirQuality(double latitude, double longitude, double radius, time_t* time)
{
    double airQuality = 0;
    System system;
    system.InitializedMeasurement();
    vector<Sensor>* sensors = Model::GetSensors();
    system.EndMeasurement();
    cout << "Etape 1 en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;

    vector<Sensor>::iterator it = sensors->begin();
    if (sensors->empty()) {
        return -1; //Erreur
    }
    int sensorUsed = 0;
    double O3 = 0;
    double NO2 = 0;
    double PM10 = 0;
    double SO2 = 0;

    if (time == nullptr) {
        time_t timeBuffer = it->GetMeasurements()->crbegin()->first;
        time = &timeBuffer;
    }
    system.InitializedMeasurement();
    for (it; it != sensors->end(); ++it) {
        double distance = pow(latitude - it->GetLatitude(), 2) + pow(longitude - it->GetLongitude(), 2);
        if (distance <= (radius*radius)) {
            sensorUsed++;
            vector<Measurement>* measuresSensor = it->GetMeasurements(*time);
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
                if (it->GetUserID() != -1) {
                    Model::IncrementPointIndividualUser(it->GetUserID());
                }
            }
        }
    }
    system.EndMeasurement();
    cout << "Etape 2 en : " << system.GetAlgorithmEfficiency() << " secondes" << endl;
    system.InitializedMeasurement();
    if (sensorUsed == 0) {
        vector<Sensor>* nearSensors = new vector<Sensor>(3);
        partial_sort_copy(sensors->begin(), sensors->end(), nearSensors->begin(), nearSensors->end(), [latitude, longitude](Sensor& s1, Sensor& s2) {
            double d1 = pow(latitude - s1.GetLatitude(), 2) + pow(longitude - s1.GetLongitude(), 2);
            double d2 = pow(latitude - s2.GetLatitude(), 2) + pow(longitude - s2.GetLongitude(), 2);
            return (d1 < d2);
        });

        sensorUsed = 3;
        double tabDist[3];
        double sumDist = 0;
        int index = 0;

        for (it= nearSensors->begin(); it != nearSensors->end(); ++it) {
            double distance = sqrt(pow(latitude - it->GetLatitude(), 2) + pow(longitude - it->GetLongitude(), 2)) - radius;
            tabDist[index] = distance;
            sumDist += distance;
            index++;
        }
        double ponderDist = sumDist - sumDist / 3;
        index = 0;

        for (it = nearSensors->begin(); it != nearSensors->end(); ++it) {
            vector<Measurement>* measuresSensor = it->GetMeasurements(*time);
            if (measuresSensor != nullptr) {
                vector<Measurement>::iterator itMeasure;

                for (itMeasure = measuresSensor->begin(); itMeasure != measuresSensor->end(); ++itMeasure) {
                    string idAttribute = itMeasure->GetAttribute().GetID();
                    double value = itMeasure->GetValue() * (sumDist - tabDist[index]) / ponderDist; //pondération
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
                if (it->GetUserID() != -1) {
                    Model::IncrementPointIndividualUser(it->GetUserID());
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
