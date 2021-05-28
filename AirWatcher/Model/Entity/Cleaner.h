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
    const int GetID() ;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    int GetProviderID() ;

    void SetProviderID(int proID);

    const double GetLatitude() ;

    const double GetLongitude() ;

    const time_t GetStart() ;

    const time_t GetStop() ;

    friend ostream& operator<<(ostream& os, const Cleaner& cleaner);
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur


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