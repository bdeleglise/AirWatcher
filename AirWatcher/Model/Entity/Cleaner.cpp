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
int Cleaner::GetID() 
{
    return cleanerID;
}

int Cleaner::GetProviderID() 
{
    return providerID;
}

double Cleaner::GetLatitude()
{
    return latitude;
}

double Cleaner::GetLongitude()
{
    return longitude;
}

Date Cleaner::GetStart() 
{
    return start;
}

Date Cleaner::GetStop() 
{
    return stop;
}

//------------------------------------------------- Surcharge d'opérateurs
Cleaner& Cleaner::operator=(const Cleaner& unCleaner)
{
    if (this != &unCleaner)
    {
        cleanerID = unCleaner.cleanerID;
        providerID = unCleaner.providerID;
        latitude = unCleaner.latitude;
        longitude = unCleaner.longitude;
        start = unCleaner.start;
        stop = unCleaner.stop;
    }
    return *this;
}

//-------------------------------------------- Constructeurs - destructeur


Cleaner::Cleaner(const Cleaner& unCleaner)
{
    cleanerID = unCleaner.cleanerID;
    providerID = unCleaner.providerID;
    latitude = unCleaner.latitude;
    longitude = unCleaner.longitude;
    start = unCleaner.start;
    stop = unCleaner.stop;
}

Cleaner::Cleaner(int id, int provider, double latitude, double longitude, Date start, Date stop)
    : cleanerID(id), providerID(provider), latitude(latitude), longitude(longitude), start(start), stop(stop)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Cleaner>" << endl;
#endif
} //----- Fin de Cleaner

Cleaner::~Cleaner()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Cleaner>" << endl;
#endif
} //----- Fin de ~Cleaner


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes protégées

//------------------------------------------------------- M�thodes privées


