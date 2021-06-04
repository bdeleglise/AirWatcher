/*************************************************************************
                           SensorManegement  -  description
                             -------------------
    d�but                : 06/05/2021
    copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
    e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr, 
                           benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/


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

// R�le de la classe <SensorManagement>
// Cette classe appartient � la couche Controlleur, elle contient les m�thodes relatives � la gestion gouvernementale
// elle se charge d'identifier les capteurs frauduleux et leur taux frauduleux et les renvoyer sous forme de vecteurs
// elle permet aussi classer les utilisateurs priv�s comme malicieux et de les bannir ainsi que leurs capteurs 


class SensorManagement {

public:
    //list<pair<Sensor, int>> MalfunctionningSensorsDetection();
    //int GetEvaluationSensor(int SensorId);
    //int GetEvaluationPrivateSensor(int SensorId);
    //bool ChangeSensorState(int SensorId);
    //list<Sensor> SimilaritySensorRanking(int SensorId, Date start, Date end);
    vector<pair<Sensor*, Confidence>>* FraudulentSensorDetection();

    // Mode d'emploi :
    // permet de parcourir la liste des capteurs priv�s et de renvoyer ceux qui semble potentiellement frauduleux avec leur �valuation, et ce en comparant l�indice ATMO de chaque capteur priv� � celui de ses voisins.  
    // Contrat :
    // aucun

    //list<pair<Sensor, int>> FraudulentIndividualDetection(int individualId);
    bool ClassifyAsUnreliable(int individualId);  

    // Mode d'emploi :
    // permet de rendre l�utilisateur dont l�id est en param�tre en malhonn�te (modification de son attribut Reliable) et de bannir ses capteurs.  
    // Contrat :
    // aucun

    SensorManagement(Model* unModel);
private:
    Model* model;
};
#endif
