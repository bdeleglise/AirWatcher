/*************************************************************************
                           GovernmentAgency  -  description
                             -------------------
    d�but                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/
#pragma once
//---------- Réalisation de la classe <GovernmentAgency> (fichier GovernmentAgency.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "GovernmentAgency.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
int GovernmentAgency::GetID() 
{
    return governementAgencyID;
}

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
GovernmentAgency::GovernmentAgency(int id) 
    : governementAgencyID(id)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <GovernmentAgency>" << endl;
#endif
} //----- Fin de GovernmentAgency


GovernmentAgency::~GovernmentAgency()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <GovernmentAgency>" << endl;
#endif
} //----- Fin de ~GovernmentAgency


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes protégées

//------------------------------------------------------- M�thodes privées