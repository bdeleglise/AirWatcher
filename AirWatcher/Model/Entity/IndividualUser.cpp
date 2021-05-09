/*************************************************************************
                           IndividuaUser  -  description
                             -------------------
    d�but                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/
#pragma once
//---------- Réalisation de la classe <IndividuaUser> (fichier IndividuaUser.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "IndividualUser.h"
#include "Sensor.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
int IndividualUser::GetID()
{
    return individualUserID;
}

int IndividualUser::GetPoints()
{
    return totalPoints;
}

void IndividualUser::SetPoints(int points)
{
    totalPoints = points;
}

bool IndividualUser::GetReliable()
{
    return reliable;
}

void IndividualUser::SetReliable(bool state)
{
    reliable = state;
    for (vector<Sensor>::iterator i = sensors.begin(); i != sensors.end(); ++i) {
        i->SetState(state);
    }
}

vector<Sensor>* IndividualUser::GetSensors()
{
    return &sensors;
}

void IndividualUser::AddSensor(Sensor &unSensor)
{
    unSensor.SetUser(individualUserID);
    Sensor sensor(unSensor);
    sensors.push_back(unSensor);
}

void IndividualUser::AddSensor(int id, float latitude, float longitude)
{
    Sensor sensor(id, latitude, longitude, individualUserID);
    sensors.push_back(sensor);
}

void IndividualUser::SetSensors(vector<Sensor>& listeSensors)
{
    sensors.clear();
    for (vector<Sensor>::iterator i = listeSensors.begin(); i != listeSensors.end(); ++i) {
        i->SetUser(individualUserID);
        Sensor sensor(*i);
        sensors.push_back(sensor);
    }
}



//------------------------------------------------- Surcharge d'opérateurs
IndividualUser& IndividualUser::operator=(const IndividualUser& unIndividualUser)
{
    if (this != &unIndividualUser)
    {
        individualUserID = unIndividualUser.individualUserID;
        totalPoints = unIndividualUser.totalPoints;
        reliable = unIndividualUser.reliable;
        sensors = unIndividualUser.sensors;
    }
    return *this;
}


//-------------------------------------------- Constructeurs - destructeur
IndividualUser::IndividualUser(const IndividualUser& unIndividualUser)
{
    individualUserID = unIndividualUser.individualUserID;
    totalPoints = unIndividualUser.totalPoints;
    reliable = unIndividualUser.reliable;
    sensors = unIndividualUser.sensors;
}

IndividualUser::IndividualUser(int id)
    : individualUserID(id), totalPoints(0), reliable(true), sensors()
    // Algorithme :
    //
{
#ifdef MAP
    cout << "Appel au constructeur de <GovernmentAgency>" << endl;
#endif
} //----- Fin de GovernmentAgency

IndividualUser::IndividualUser(int id, Sensor& unSensor)
    : individualUserID(id), totalPoints(0), reliable(true), sensors()
{
    Sensor sensor(unSensor);
    sensors.push_back(sensor);
}




IndividualUser::~IndividualUser()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <IndividuaUser>" << endl;
#endif
} //----- Fin de ~IndividuaUser


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes protégées

//------------------------------------------------------- M�thodes privées