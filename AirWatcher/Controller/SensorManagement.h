#if ! defined (SENSORMANAGEMENT_H)
#define SENSORMANAGEMENT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include<list>
#include "../Model/Entity/Sensor.cpp"
#include "../Util/Date.h"
#include "../Model/Model.h"


using namespace std;

class SensorManagement {

public:
    list<pair<Sensor, int>> MalfunctionningSensorsDetection();
    int GetEvaluationSensor(int SensorId);
    int GetEvaluationPrivateSensor(int SensorId);
    bool ChangeSensorState(int SensorId);
    list<Sensor> SimilaritySensorRanking(int SensorId, Date start, Date end);
    vector<pair<Sensor, int>> FraudulentSensorDetection();
    list<pair<Sensor, int>> FraudulentIndividualDetection(int individualId);
    bool ClassifyAsUnreliable(int individualId);





};
#endif
