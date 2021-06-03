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
    int GetID() const;
    // Mode d'emploi :
    // Getter de l'attribut Id
    // Contrat :
    // aucun
    
    int GetPoints();

    // Mode d'emploi :
    // Getter de l'attribut Points
    // Contrat :
    // aucun

    void SetPoints(int points);

    // Mode d'emploi :
    // Setter de l'attribut Points
    // Contrat :
    // aucun

    bool GetReliable();

    // Mode d'emploi :
    // Getter de l'attribut Reliable
    // Contrat :
    // aucun

    void SetReliable(bool state);

    // Mode d'emploi :
    // Setter de l'attribut Reliable
    // Contrat :
    // aucun

    vector<Sensor>* GetSensors();

    // Mode d'emploi :
    // Getter afin de récupérer la liste de Sensors
    // Contrat :
    // aucun

    void AddSensor(Sensor &unSensor);

    // Mode d'emploi :
    // Méthode permettant d'ajouter un nouveau Sensor à la liste des Sensors à partir d'un pointeur sur un sensor déjà créé.
    // Contrat :
    // aucun

    void AddSensor(int id, float latitude, float longitude);

    // Mode d'emploi :
    // Méthode permettant d'ajouter un nouveau Sensor à la liste des Sensors à partir de l'id du sensor et de ses coordonnées géographiques.
    // Contrat :
    // aucun

    void SetSensors(vector<Sensor>& listeSensors);

    // Mode d'emploi :
    // Setter enregistrant la liste des Sensors.
    // Contrat :
    // aucun

    friend ostream& operator<<(ostream& os, const IndividualUser& user);
//------------------------------------------------- Surcharge d'opérateurs
// 
//-------------------------------------------- Constructeurs - destructeur


    IndividualUser(int id);
    // Mode d'emploi :
    // Constructeur de la classe IndividualUser
    // Contrat :
    // aucun
    
    IndividualUser();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    IndividualUser(int id, Sensor& unSensor);
    // Mode d'emploi :
    // Constructeur de copies de la classe IndividualUser
    // Contrat :
    // aucun



    virtual ~IndividualUser();
    // Mode d'emploi :
    // Destructeur de la classe IndividualUser
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
    int individualUserID;
    int totalPoints;
    bool reliable;
    vector<Sensor> sensors;

    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés
};

#endif // INDIVIDUALUSER_H
