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
int Provider::GetID() const
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
bool Provider::operator==(const Provider& unProvider)
{
    return (providerID == unProvider.providerID);
}
bool Provider::operator<(const Provider& unProvider)
{
    return (providerID< unProvider.providerID);
}
Provider& Provider::operator=(const Provider& unProvider)
{
    if (this != &unProvider) {
        providerID = unProvider.providerID;
        cleaners = unProvider.cleaners;
    }
    return *this;
}
Provider::Provider(const Provider& unProvider)
{
    // construction d'une copie de Provider à partir de l'adresse d'un Provider existant
    providerID = unProvider.providerID;
    cleaners = unProvider.cleaners;
}
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

Provider::Provider()
    :providerID(-1),cleaners()
{
}

Provider::~Provider()
// Algorithme :
// Destruction d'un objet Provider (pas d'allocation dynamique donc pas de libération)
{
#ifdef MAP
    cout << "Appel au destructeur de <Provider>" << endl;
#endif
} //----- Fin de ~Provider


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes protégées

//------------------------------------------------------- M�thodes privées

ostream& operator<<(ostream& os, const Provider& provider)
{
    os << "provider" << provider.providerID << endl;
    os << provider.cleaners.size() << " cleaners" << endl;
    os << "List of cleaners :" << endl;
    vector<Cleaner>::const_iterator it=provider.cleaners.begin();
    for (it = provider.cleaners.begin(); it != provider.cleaners.end(); ++it) {
        os << *it << endl;
    }
    return os;
}
