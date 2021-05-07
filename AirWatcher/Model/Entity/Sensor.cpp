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

float Sensor::GetLatitude()
{
    return latitude;
}

float Sensor::GetLongitude()
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
    if (user != nullptr) {
        user->SetReliable(state);
    }
}

IndividualUser* Sensor::GetUser()
{
    return user;
}

void Sensor::SetUser(IndividualUser* privateUser)
{
    user = privateUser;
}

//TODO: Get et ADD measurements


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
}

Sensor::Sensor(int id, float latitude, float longitude)
    : sensorID(id), latitude(latitude), longitude(longitude), state(true), user(nullptr)
{
}

Sensor::Sensor(int id, float latitude, float longitude, IndividualUser* privateUser)
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
