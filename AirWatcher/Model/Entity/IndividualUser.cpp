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
int IndividualUser::GetID() const
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
    // parcourt la liste des sensors et set leur attribut Reliable par rapport au paramètre d'entrée de la méthode.
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
    // ajout dans la liste des sensors une fois que le propriétaire du sensor a été set
    sensors.push_back(unSensor);
}

void IndividualUser::AddSensor(int id, float latitude, float longitude)
{
    Sensor sensor(id, latitude, longitude, individualUserID);
    sensors.push_back(sensor);
}

void IndividualUser::SetSensors(vector<Sensor>& listeSensors)
{
    // Setting pour chaque sensor de leur User avec l'Id de l'IndividualUser en question
    sensors.clear();
    for (vector<Sensor>::iterator i = listeSensors.begin(); i != listeSensors.end(); ++i) {
        i->SetUser(individualUserID);
        Sensor sensor(*i);
        sensors.push_back(sensor);
    }
}



//------------------------------------------------- Surcharge d'opérateurs



//-------------------------------------------- Constructeurs - destructeur


IndividualUser::IndividualUser(int id)
    : individualUserID(id), totalPoints(0), reliable(true), sensors()
    // Algorithme :
    // Setting des attributs de l'objet IndividualUser
{
#ifdef MAP
    cout << "Appel au constructeur de <GovernmentAgency>" << endl;
#endif
} //----- Fin de GovernmentAgency

IndividualUser::IndividualUser()
    : individualUserID(-1), totalPoints(0), reliable(true), sensors()
{
}

IndividualUser::IndividualUser(int id, Sensor& unSensor)
    : individualUserID(id), totalPoints(0), reliable(true), sensors()
{   // Algorithme :
    // Construction d'une copie de l'IndividualUSer dont l'adresse est passée en paramètre de la méthode
    Sensor sensor(unSensor);
    sensors.push_back(sensor);
}




IndividualUser::~IndividualUser()
// Algorithme :
// Destruction de l'objet IndividualUser (pas d'allocation dynamique donc pas de libération)
{
#ifdef MAP
    cout << "Appel au destructeur de <IndividuaUser>" << endl;
#endif
} //----- Fin de ~IndividuaUser


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes protégées

//------------------------------------------------------- M�thodes privées

ostream& operator<<(ostream& os, const IndividualUser& user)
{
    os << "user" << user.individualUserID << endl;
    os << "Total points : " << user.totalPoints << endl;
    os << "Reliable : " << user.reliable << endl;
    os << "Number of sensors :" << user.sensors.size() << endl;
    os << "List of sensors : " << endl;
    vector<Sensor>::const_iterator it;
    for (it = user.sensors.begin(); it != user.sensors.end(); ++it) {
        os << *it << endl;
    }
    return os;
}
