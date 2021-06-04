/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : 06/05/2021
    copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
    e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
                           benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/

#pragma once
//---------- Interface de la classe <Attribute> (fichier Attribute.h) -----
#if ! defined ( ATTRIBUTE_H )
#define ATTRIBUTE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
using namespace std;

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Role de la classe <Attribute>
// Cette classe entity appartient à la couche Model de MVC
// Elle permet de récupérer les attributs Id, Unit et description
//
//------------------------------------------------------------------------ 
class Attribute
{

    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    string GetID() const;
    // Mode d'emploi :
    // Permet de récupérer l'attribut Id
    // Contrat :
    // Aucun
    
    string GetUnit() const;
    // Mode d'emploi :
    // Permet de récupérer l'attribut unit
    // Contrat :
    // Aucun

    string GetDescription() const;
    // Mode d'emploi :
    // Permet de récupérer l'attribut description
    // Contrat :
    // Aucun

    friend ostream& operator<<(ostream& os, const Attribute& unAtt);
    // Surcharge de l'opérateur << afin de gérer les informations sur la sortie standard.
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    


    Attribute();

    Attribute(string id, string unit, string desc);

    virtual ~Attribute();
    // Mode d'emploi :
    // Destructeur de la classe Attribute
    // Contrat :
    // aucun

//------------------------------------------------------------------ PRIVE 

protected:
    //----------------------------------------------------- Méthodes protégées

private:
    //------------------------------------------------------- Méthodes privées

protected:
    //----------------------------------------------------- Attributs protégés

private:
    //------------------------------------------------------- Attributs privés
    string attributeID;
    string unit;
    string description;
    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés

};

//----------------------------------------- Types d�pendants de <Attribute>

#endif // ATTRIBUTE_H