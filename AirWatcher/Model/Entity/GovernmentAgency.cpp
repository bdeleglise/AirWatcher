/*************************************************************************
                           GovernmentAgency  -  description
                             -------------------
    début                : 06/05/2021
    copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
    e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
                           benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
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
int GovernmentAgency::GetID() const
{
    return governementAgencyID;
}

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
GovernmentAgency::GovernmentAgency(int id) 
    : governementAgencyID(id)
// Algorithme :
// Setting des attributs de la classe GovernmentAgency
{
#ifdef MAP
    cout << "Appel au constructeur de <GovernmentAgency>" << endl;
#endif
} //----- Fin de GovernmentAgency

GovernmentAgency::GovernmentAgency()
    : governementAgencyID(-1)
{
}


GovernmentAgency::~GovernmentAgency()
// Algorithme :
// Destruction de l'objet GovernmentAgency (pas d'allocation dynamique donc pas de libération)
{
#ifdef MAP
    cout << "Appel au destructeur de <GovernmentAgency>" << endl;
#endif
} //----- Fin de ~GovernmentAgency


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes protégées

//------------------------------------------------------- M�thodes privées