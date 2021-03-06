#pragma once
/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : 06/05/2021
    copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
    e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
                           benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
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
int Sensor::GetID() const{
    return sensorID;
}

double Sensor::GetLatitude() const
{
    return latitude;
}

double Sensor::GetLongitude() const
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

map<time_t, vector<Measurement>>* Sensor::GetMeasurements()
{
    return &measurements;
}

vector<Measurement>*Sensor::GetMeasurements(time_t& time) {
    return &measurements[time];
}

void Sensor::AddMeasurement(Measurement& measure)
{
    measurements[measure.GetTime()].push_back(measure);
}



//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur



Sensor::Sensor(int id, double latitude, double longitude)
    : sensorID(id), latitude(latitude), longitude(longitude), state(true), user(-1)
{
}

Sensor::Sensor(int id, double latitude, double longitude, int privateUser)
    : sensorID(id), latitude(latitude), longitude(longitude), state(true), user(privateUser)
{

}

Sensor::Sensor()
    :sensorID(-1)
{
}

Sensor::~Sensor()
// Algorithme :
// Destruction d'un objet Sensor (pas d'allocation dynamique donc pas de libération)
{
#ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
#endif
} //----- Fin de ~Sensor


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes protégées

//------------------------------------------------------- M�thodes privées

ostream& operator<<(ostream& os, const Sensor& sensor)
{
    os << "Sensor" << sensor.sensorID << endl;
    os << "Latitude : " << sensor.latitude << endl;
    os << "Longitude : " << sensor.longitude << endl;
    os << "Etat :" << sensor.state << endl;
    if (sensor.user != -1) {
        os << "Appartient a user" << sensor.user << endl;
    }
    os << "Dernieres mesures :" << endl;
    for (const auto& mesure : sensor.measurements.crbegin()->second)
    {
        cout << mesure << endl;
    }
    os << sensor.measurements.size() << " jour de mesures";
    return os;
}
