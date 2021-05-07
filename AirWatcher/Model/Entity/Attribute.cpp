#pragma once
/*************************************************************************
                           Attribute  -  description
                             -------------------
    d�but                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- R�alisation de la classe <Attribute> (fichier Attribute.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Attribute.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
string Attribute::GetID()
{
    return attributeID;
}

string Attribute::GetDescription()
{
    return description;
}




string Attribute::GetUnit()
{
    return unit;
}
//------------------------------------------------- Surcharge d'opérateurs

Attribute& Attribute::operator=(const Attribute& unAttribute)
{
    if (this != &unAttribute) {
        attributeID = unAttribute.attributeID;
        unit = unAttribute.unit;
        description = unAttribute.description;
    }
    return *this;
}

//-------------------------------------------- Constructeurs - destructeur
Attribute::Attribute(const Attribute& unAttribute)
{
    attributeID = unAttribute.attributeID;
    unit = unAttribute.unit;
    description = unAttribute.description;

}

Attribute::Attribute(string id, string unit, string desc)
    : attributeID(id), unit(unit), description(desc)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Attribute>" << endl;
#endif
} //----- Fin de Attribute


Attribute::~Attribute()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Attribute>" << endl;
#endif
} //----- Fin de ~Attribute


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes protégées

//------------------------------------------------------- M�thodes privées
