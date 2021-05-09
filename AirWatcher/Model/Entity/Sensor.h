﻿/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Interface de la classe <Sensor> (fichier Sensor.h) ------
#if ! defined ( SENSOR_H )
#define SENSOR_H

//--------------------------------------------------- Interfaces utilisées
#pragma once
#include <string>
#include "IndividualUser.h"
#include <map>
#include <vector>
#include "../../Util/Date.h"
#include "Measurement.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <Sensor>
//
//
//------------------------------------------------------------------------ 
class IndividualUser;

#pragma once
class Sensor
{

    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    int GetID();
    // Mode d'emploi :
    //
    // Contrat :
    //

    double GetLatitude();

    double GetLongitude();

    bool GetState();

    void SetState(bool newstate);

    IndividualUser* GetUser();

    void SetUser(IndividualUser* privateUser);

    map<Date, vector<Measurement>>* GetMeasurements();

    void AddMeasurement(Measurement& measure);

//------------------------------------------------- Surcharge d'opérateurs
    Sensor& operator =(const Sensor& unSensor);
//-------------------------------------------- Constructeurs - destructeur
    Sensor(const Sensor& unSensor);
    Sensor();
    Sensor(int id, double latitude, double longitude);
    Sensor(int id, double latitude, double longitude, IndividualUser* privateUser);
    virtual ~Sensor();
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE 

protected:
    //----------------------------------------------------- Méthodes protégées

private:
    //------------------------------------------------------- Méthodes privées

protected:
    //----------------------------------------------------- Attributs protégés

private:
    //------------------------------------------------------- Attributs privés
    int sensorID;
    double latitude;
    double longitude;
    bool state;
    IndividualUser* user;  //Ya moyen il faille mettre un ptr
    map<Date, vector<Measurement>> measurements;
    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés

};

//----------------------------------------- Types d�pendants de <Sensor>

#endif // SENSOR_H