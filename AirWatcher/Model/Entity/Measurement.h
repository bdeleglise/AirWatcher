/*************************************************************************
                           Measurements  -  description
                             -------------------
    début                : 06/05/2021
    copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
    e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
                           benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/


//---------- Interface de la classe <Measurement> (fichier Measurement.h) ------
#if ! defined ( MEASUREMENT_H )
#define MEASUREMENT_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <ctime>
#include "Attribute.h"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Role de la classe <Measurement>
// Cette classe entity de la couche Model de MVC, elle s'occupe de la gestion des mesures 
// elle permet d'obtenir la valeur, l'attribut et le temps des mesures
//
//------------------------------------------------------------------------ 

#pragma once
class Measurement {

    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    double GetValue() const;
    // Mode d'emploi :
    // Getter de l'attribut Value
    // Contrat :
    // aucun
    
    time_t GetTime() const;

    // Mode d'emploi :
    // Getter de l'attribut Timestamp
    // Contrat :
    // aucun

    Attribute GetAttribute() const;

    // Mode d'emploi :
    // Getter de l'attribut attribute
    // Contrat :
    // aucun

    friend ostream& operator<<(ostream& os, const Measurement& unMeasurement);
    // Surcharge de l'opérateur << permettant de gérer les information qu'on passe dans la sortie standard
//------------------------------------------------- Surcharge d'opérateurs
    Measurement& operator = (const Measurement& unMeasurement);
    // Surcharge de l'opérateur = qui permet d'attribuer des valeurs à un objet de la classe Measurement
//-------------------------------------------- Constructeurs - destructeur
    Measurement();



    Measurement(time_t time, double val, Attribute& unAttribute);

    // Mode d'emploi :
    // Constructeur de la classe Measurement
    // Contrat :
    // aucun

    virtual ~Measurement();
    // Mode d'emploi :
    // Destructeur de la classe Measurement
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
    time_t timestamp;
    double value;
    Attribute attribute;
    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés

};

//----------------------------------------- Types d�pendants de <${file_base}>

#endif // MEASUREMENT_H