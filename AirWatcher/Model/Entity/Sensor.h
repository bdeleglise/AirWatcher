/*************************************************************************
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
#include <ctime>
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

    int GetUserID();

    void SetUser(int privateUser);

    map<time_t, vector<Measurement>>* GetMeasurements();

    void AddMeasurement(Measurement& measure);

    friend ostream& operator<<(ostream& os, const Sensor& sensor);

//------------------------------------------------- Surcharge d'opérateurs
    Sensor& operator =(const Sensor& unSensor);
//-------------------------------------------- Constructeurs - destructeur
    Sensor(const Sensor& unSensor);
    Sensor();
    Sensor(int id, double latitude, double longitude);
    Sensor(int id, double latitude, double longitude, int privateUser);
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
    int user;
    map<time_t, vector<Measurement>> measurements;
    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés

};

//----------------------------------------- Types d�pendants de <Sensor>

#endif // SENSOR_H