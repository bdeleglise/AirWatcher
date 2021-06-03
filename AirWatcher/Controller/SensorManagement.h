#if ! defined (SENSORMANAGEMENT_H)
#define SENSORMANAGEMENT_H

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include<list>
#include "../Model/Entity/Sensor.h"
#include "../Model/Model.h"


using namespace std;
typedef pair<double, double> Confidence;

class SensorManagement {

public:
    //list<pair<Sensor, int>> MalfunctionningSensorsDetection();
    //int GetEvaluationSensor(int SensorId);
    //int GetEvaluationPrivateSensor(int SensorId);
    //bool ChangeSensorState(int SensorId);
    //list<Sensor> SimilaritySensorRanking(int SensorId, Date start, Date end);
    vector<pair<Sensor*, Confidence>>* FraudulentSensorDetection();

    // Mode d'emploi :
    // permet de parcourir la liste des capteurs privés et de renvoyer ceux qui semble potentiellement frauduleux avec leur évaluation, et ce en comparant l’indice ATMO de chaque capteur privé à celui de ses voisins.  
    // Contrat :
    // aucun

    //list<pair<Sensor, int>> FraudulentIndividualDetection(int individualId);
    bool ClassifyAsUnreliable(int individualId);  

    // Mode d'emploi :
    // permet de rendre l’utilisateur dont l’id est en paramètre en malhonnête (modification de son attribut Reliable) et de bannir ses capteurs.  
    // Contrat :
    // aucun

    SensorManagement(Model* unModel);
private:
    Model* model;
};
#endif
