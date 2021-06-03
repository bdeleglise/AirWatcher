#pragma once
/*************************************************************************
                           Cleaner  -  description
                             -------------------
    d�but                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- R�alisation de la classe <User> (fichier User.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Cleaner.h"


//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
int Cleaner::GetID() const
{
    return cleanerID;
}

int Cleaner::GetProviderID() 
{
    return providerID;
}

void Cleaner::SetProviderID(int proID)
{
    providerID = proID;
}

double Cleaner::GetLatitude() const
{
    return latitude;
}

double Cleaner::GetLongitude() const
{
    return longitude;
}

time_t Cleaner::GetStart() const
{
    return start;
}

time_t Cleaner::GetStop() const
{
    return stop;
}

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur




Cleaner::Cleaner(int id, int provider, double latitude, double longitude, time_t start, time_t stop)
    : cleanerID(id), providerID(provider), latitude(latitude), longitude(longitude), start(start), stop(stop)
// Algorithme :
// Setting des attributs du cleaner que l'on va créer
{
#ifdef MAP
    cout << "Appel au constructeur de <Cleaner>" << endl;
#endif
} //----- Fin de Cleaner

Cleaner::Cleaner()
    : cleanerID(-1)
{
}

Cleaner::~Cleaner()
// Algorithme :
// Destruction de l'objet Cleaner (pas d'allocation dynamique à libérer)
{
#ifdef MAP
    cout << "Appel au destructeur de <Cleaner>" << endl;
#endif
} //----- Fin de ~Cleaner


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes protégées

//------------------------------------------------------- M�thodes privées

ostream& operator<<(ostream& os, const Cleaner& cleaner)
{
    os << "cleaner" << cleaner.cleanerID << endl;
    os << "Latitude " << cleaner.latitude << endl;
    os << "Longitude " << cleaner.longitude << endl;
    os << "provider" << cleaner.providerID << endl;
    struct tm* tmp=new tm();
    localtime_s(tmp,&cleaner.start);
    os << "Effective from " << tmp->tm_year + 1900 << "-" << tmp->tm_mon + 1 << "-" << tmp->tm_mday << " " << tmp->tm_hour << ":" << tmp->tm_min << ":" << tmp->tm_sec << endl;
    localtime_s(tmp, &cleaner.stop);
    os << "To " << tmp->tm_year + 1900 << "-" << tmp->tm_mon + 1 << "-" << tmp->tm_mday << " " << tmp->tm_hour << ":" << tmp->tm_min << ":" << tmp->tm_sec;
    delete tmp;
    return os;
}
