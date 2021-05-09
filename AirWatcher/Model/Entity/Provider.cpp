#pragma once
/*************************************************************************
                           Provider  -  description
                             -------------------
    d�but                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- R�alisation de la classe <Provider> (fichier Provider.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Provider.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
int Provider::GetID()
{
    return providerID;
}

vector<Cleaner>* Provider::GetCleaners()
{
    return &cleaners;
}

void Provider::AddCleaner(Cleaner& unCleaner)
{
    cleaners.push_back(unCleaner);
}

void Provider::setCleaners(vector<Cleaner>& listcleaners)
{
    cleaners = listcleaners;
}
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Provider::Provider(int id)
    :providerID(id), cleaners()
{
}

Provider::Provider(int id, Cleaner& unCleaner)
    : providerID(id), cleaners()
{
    cleaners.push_back(unCleaner);
}

Provider::~Provider()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Provider>" << endl;
#endif
} //----- Fin de ~Provider


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes protégées

//------------------------------------------------------- M�thodes privées


