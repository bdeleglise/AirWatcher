#pragma once
/*************************************************************************
                           User  -  description
                             -------------------
    d�but                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- R�alisation de la classe <Measurement> (fichier Measurement.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Measurement.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
double Measurement::GetValue()
{
    return value;
}

time_t Measurement::GetTime()
{
    return timestamp;
}

Attribute Measurement::GetAttribute() 
{
    return attribute;
}
//------------------------------------------------- Surcharge d'opérateurs



//-------------------------------------------- Constructeurs - destructeur
Measurement::Measurement(const Measurement& unMeasurement) 
{
    timestamp = unMeasurement.timestamp;
    value = unMeasurement.value;
    attribute = unMeasurement.attribute;
}

Measurement::Measurement(time_t time, double val, Attribute& unAttribute)
    : timestamp(time), value(val), attribute(unAttribute)
{
#ifdef MAP
    cout << "Appel au destructeur de <Measurement>" << endl;
#endif
}


Measurement::~Measurement()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Measurement>" << endl;
#endif
} //----- Fin de ~Measurement


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes protégées

//------------------------------------------------------- M�thodes privées

ostream& operator<<(ostream& os, const Measurement& unMeasurement)
{
    struct tm* tmp = new tm();
    localtime_s(tmp, &unMeasurement.timestamp);
    os << "Measurement of the " << tmp->tm_year + 1900 << "-" << tmp->tm_mon + 1 << "-" << tmp->tm_mday << " " << tmp->tm_hour << ":" << tmp->tm_min << ":" << tmp->tm_sec << endl;
    os << "Value :" << unMeasurement.value << " in " << unMeasurement.attribute << endl;
    delete tmp;
    return os;
}
