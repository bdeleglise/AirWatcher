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
string Attribute::GetID() const
{
    return attributeID;
}

string Attribute::GetDescription() const
{
    return description;
}




string Attribute::GetUnit() const
{
    return unit;
}
//------------------------------------------------- Surcharge d'opérateurs




//-------------------------------------------- Constructeurs - destructeur


Attribute::Attribute()
    : attributeID(), unit(), description()
{
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

ostream& operator<<(ostream& os, const Attribute& unAtt)
{
    os << unAtt.attributeID << " " << unAtt.unit;
    return os;
}
