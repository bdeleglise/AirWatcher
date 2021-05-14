/*************************************************************************
                           Cleaner  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
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
//
//
//------------------------------------------------------------------------ 

#pragma once
class Cleaner
{

    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    int GetID() ;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    int GetProviderID() ;

    void SetProviderID(int proID);

    double GetLatitude() ;

    double GetLongitude() ;

    time_t GetStart() ;

    time_t GetStop() ;


//------------------------------------------------- Surcharge d'opérateurs
    Cleaner& operator = (const Cleaner& unCleaner);
    // Mode d'emploi :
    //
    // Contrat :
    //
    // 
    // 
//-------------------------------------------- Constructeurs - destructeur
    Cleaner(const Cleaner& unCleaner);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Cleaner(int id, int provider, double latitude, double longitude, time_t start, time_t stop);
    // Mode d'emploi :
    //
    // Contrat :
    //

    Cleaner();
    // Mode d'emploi :
    //
    // Contrat :
    //


    virtual ~Cleaner();
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