#pragma once
/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- R�alisation de la classe <Sensor> (fichier Sensor.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Sensor.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC

//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
int Sensor::GetID() {
    return sensorID;
}

double Sensor::GetLatitude()
{
    return latitude;
}

double Sensor::GetLongitude()
{
    return longitude;
}

bool Sensor::GetState()
{
    return state;
}

void Sensor::SetState(bool newstate)
{
    state = newstate;
}

int Sensor::GetUserID()
{
    return user;
}

void Sensor::SetUser(int privateUser)
{
    user = privateUser;
}

map<Date, vector<Measurement>>* Sensor::GetMeasurements()
{
    return &measurements;
}

void Sensor::AddMeasurement(Measurement& measure)
{
    measurements[measure.GetTime()].push_back(measure);
}



//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur


Sensor& Sensor::operator=(const Sensor& unSensor)
{
    if (this != &unSensor) {
        sensorID = unSensor.sensorID;
        state = unSensor.state;
        latitude = unSensor.latitude;
        longitude = unSensor.longitude;
        user = unSensor.user;
        measurements = unSensor.measurements;
    }
    return *this;
}

Sensor::Sensor(const Sensor& unSensor)
{
    sensorID=unSensor.sensorID;
    state=unSensor.state;
    latitude=unSensor.latitude;
    longitude=unSensor.longitude;
    user=unSensor.user;
    measurements = unSensor.measurements;
}

Sensor::Sensor(int id, double latitude, double longitude)
    : sensorID(id), latitude(latitude), longitude(longitude), state(true), user(0)
{
}

Sensor::Sensor(int id, double latitude, double longitude, int privateUser)
    : sensorID(id), latitude(latitude), longitude(longitude), state(true), user(privateUser)
{

}

Sensor::~Sensor()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
#endif
} //----- Fin de ~Sensor


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes protégées

//------------------------------------------------------- M�thodes privées
