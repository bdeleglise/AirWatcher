/*************************************************************************
                           Cleaner  -  description
                             -------------------
    début                : 06/05/2021
    copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
    e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
                           benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/


//---------- Interface de la classe <Cleaner> (fichier Cleaner.h) ------
#if ! defined ( CLEANER_H )
#define CLEANER_H

//--------------------------------------------------- Interfaces utilisées
#include <ctime>
#include <string>

using namespace std;
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <Cleaner>
// Cette classe entity de la couche Model de MVC, elle s'occupe de la gestion des cleaners 
// elle permet d'obtenir l'id, le provider et les coordonnées du cleaner 
// elle permet aussi de modifier le provider de cleaner
//------------------------------------------------------------------------ 

#pragma once
class Cleaner
{

    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    int GetID() const;
    // Mode d'emploi :
    // Getter de l'attribut Id
    // Contrat :
    // aucun
    
    int GetProviderID() ;

    // Mode d'emploi :
    // Getter de l'attribut ProviderId
    // Contrat :
    // aucun

    void SetProviderID(int proID);

    // Mode d'emploi :
    // Setter de l'attribut ProviderId afin de le modifier
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

    time_t GetStart() const;

    // Mode d'emploi :
    // Getter de l'attribut Start
    // Contrat :
    // aucun

    time_t GetStop() const;

    // Mode d'emploi :
    // Getter de l'attribut Stop
    // Contrat :
    // aucun

    friend ostream& operator<<(ostream& os, const Cleaner& cleaner);
    // Surcharge de l'opérateur << afin de gérer les informations allant sur la sortie standard.
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur


    Cleaner(int id, int provider, double latitude, double longitude, time_t start, time_t stop);
    // Mode d'emploi :
    // Constructeur de la classe Cleaner
    // Contrat :
    // Aucun

    Cleaner();
    // Mode d'emploi :
    // Surcharge du constructeur de la classe Cleaner
    // Contrat :
    // Aucun


    virtual ~Cleaner();
    // Mode d'emploi :
    // Destructeur de la classe Cleaner
    // Contrat :
    // Aucun

//------------------------------------------------------------------ PRIVE 

protected:
    //----------------------------------------------------- Méthodes protégées

private:
    //------------------------------------------------------- Méthodes privées

protected:
    //----------------------------------------------------- Attributs protégés

private:
    //------------------------------------------------------- Attributs privés
    int cleanerID;
    int providerID;
    double latitude;
    double longitude;
    time_t start;
    time_t stop;

    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Cleaner>

#endif // CLEANER