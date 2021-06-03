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
#pragma once
#include <string>
#include "IndividualUser.h"
#include <map>
#include <vector>
#include <ctime>
#include "Measurement.h"

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
    int GetID() const;
    // Mode d'emploi :
    // Getter de l'attribut Id
    // Contrat :
    // aucun

    double GetLatitude() const;

    // Mode d'emploi :
    // Getter de l'attribut Latitude
    // Contrat :
    // aucun

    double GetLongitude() const;

    // Mode d'emploi :
   // Getter de l'attribut Longitude
   // Contrat :
   // aucun

    bool GetState();

    // Mode d'emploi :
    // Getter de l'attribut state
    // Contrat :
    // aucun

    void SetState(bool newstate);

    // Mode d'emploi :
    // Setter de l'attribut state
    // Contrat :
    // aucun

    int GetUserID();

    // Mode d'emploi :
    // Getter de l'Id d'un user à partir de l'attribut User
    // Contrat :
    // aucun

    void SetUser(int privateUser);

    // Mode d'emploi :
    // Setter de l'attribut user
    // Contrat :
    // aucun

    map<time_t, vector<Measurement>>* GetMeasurements();

    // Mode d'emploi :
    // Méthode permettant de récupérer les Measurements d'un Sensor à tous les temps
    // Contrat :
    // aucun

    vector<Measurement>* GetMeasurements(time_t& time);

    // Mode d'emploi :
    // Méthode permettant de récupérer les Measurements d'un Sensor à un temps précis passé en paramètre de la méthode
    // Contrat :
    // aucun

    void AddMeasurement(Measurement& measure);

    // Mode d'emploi :
    // Méthode permettant d'ajouter des Measurements à la liste des Measurements d'un Sensor
    // Contrat :
    // aucun

    friend ostream& operator<<(ostream& os, const Sensor& sensor);
    //  Surcharge de l'opérateur << permettant de gérer les information qu'on passe dans la sortie standard
//------------------------------------------------- Surcharge d'opérateurs
//-------------------------------------------- Constructeurs - destructeur

    Sensor();
    Sensor(int id, double latitude, double longitude);
    Sensor(int id, double latitude, double longitude, int privateUser);
    virtual ~Sensor();
    // Mode d'emploi :
    // Destructeur de la classe Sensor
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
    int sensorID;
    double latitude;
    double longitude;
    bool state;
    int user;
    map<time_t, vector<Measurement>> measurements;
    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés

};

//----------------------------------------- Types d�pendants de <Sensor>

#endif // SENSOR_H