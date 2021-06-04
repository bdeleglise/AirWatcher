#pragma once
/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : 06/05/2021
    copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
    e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
                           benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/

//---------- Realisation de la classe <Attribute> (fichier Attribute.cpp) --

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
    //getter de l'attribut Id
    return attributeID;
}


string Attribute::GetDescription() const
{
    //getter de l'attribut description
    return description;
}




string Attribute::GetUnit() const
{
    //getter de l'attribut unit
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
