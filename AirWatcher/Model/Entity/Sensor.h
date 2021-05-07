/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Interface de la classe <Sensor> (fichier Sensor.h) ------
#if ! defined ( SENSOR_H )
#define SENSOR_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include "IndividualUser.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <Sensor>
//
//
//------------------------------------------------------------------------ 
class IndividualUser;

#pragma once
class Sensor
{

    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    int GetID();
    // Mode d'emploi :
    //
    // Contrat :
    //

    float GetLatitude();

    float GetLongitude();

    bool GetState();

    void SetState(bool newstate);

    IndividualUser* GetUser();

    void SetUser(IndividualUser* privateUser);

    //TODO: GetMeasurements et AddMeadurements

//------------------------------------------------- Surcharge d'opérateurs
    Sensor& operator =(const Sensor& unSensor);
//-------------------------------------------- Constructeurs - destructeur
    Sensor(const Sensor& unSensor);
    Sensor();
    Sensor(int id, float latitude, float longitude);
    Sensor(int id, float latitude, float longitude, IndividualUser* privateUser);
    virtual ~Sensor();
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
    int sensorID;
    float latitude;
    float longitude;
    bool state;
    IndividualUser* user;  //Ya moyen il faille mettre un ptr
    // TODO: définir un conteneur pour les mesures  -> measurements
    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés

};

//----------------------------------------- Types d�pendants de <Sensor>

#endif // SENSOR_H