/*************************************************************************
                           Measurement  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
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
// R�le de la classe <Measurement>
//
//
//------------------------------------------------------------------------ 

#pragma once
class Measurement {

    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    double GetValue() const;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    time_t GetTime() const;

    Attribute GetAttribute() const;
    friend ostream& operator<<(ostream& os, const Measurement& unMeasurement);

//------------------------------------------------- Surcharge d'opérateurs
    Measurement& operator = (const Measurement& unMeasurement);

//-------------------------------------------- Constructeurs - destructeur
    Measurement();



    Measurement(time_t time, double val, Attribute& unAttribute);

    virtual ~Measurement();
    // Mode d'emploi :
    //
    // Contrat :
    //

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