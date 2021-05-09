#pragma once
/*************************************************************************
                           IndividuaUser  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Interface de la classe <IndividualUser> (fichier IndividualUser.h) ------
#if ! defined ( INDIVIDUALUSER_H )
#define INDIVIDUALUSER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include "User.h"
#include "Sensor.h"
using namespace std;

class Sensor;
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <IndividualUser>
//
//
//------------------------------------------------------------------------ 
class IndividualUser :
    public User
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    int GetID();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    int GetPoints();

    void SetPoints(int points);

    bool GetReliable();

    void SetReliable(bool state);

    vector<Sensor*>* GetSensors();

    void AddSensor(Sensor* unSensor);

    void AddSensor(int id, float latitude, float longitude);

    void SetSensors(vector<Sensor>& listeSensors);


//------------------------------------------------- Surcharge d'opérateurs
    IndividualUser& operator = (const IndividualUser& unIndividualUser);
    // Mode d'emploi :
    //
    // Contrat :
    //
//-------------------------------------------- Constructeurs - destructeur
    IndividualUser(const IndividualUser& unIndividualUser);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    IndividualUser(int id);
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    IndividualUser(int id, Sensor* unSensor);
    // Mode d'emploi :
    //
    // Contrat :
    //

    IndividualUser();
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~IndividualUser();
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
    int individualUserID;
    int totalPoints;
    bool reliable;
    vector<Sensor*> sensors;

    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés
};

#endif // INDIVIDUALUSER_H
