/*************************************************************************
                           Provider  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Interface de la classe <Provider> (fichier Provider.h) ------
#if ! defined ( PROVIDER_H )
#define PROVIDER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include "User.h"
#include "Cleaner.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <Provider>
//
//
//------------------------------------------------------------------------ 
#pragma once
class Provider :
    public User
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    const int GetID();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    vector<Cleaner>* GetCleaners();

    void AddCleaner(Cleaner& unCleaner);

    void setCleaners(vector<Cleaner>& listcleaners);

    friend ostream& operator<<(ostream& os, const Provider& provider);

//------------------------------------------------- Surcharge d'opérateurs
    bool operator ==(const Provider& unProvider);

    bool operator <(const Provider& unProvider);

    Provider& operator = (const Provider& unProvider);
    // Mode d'emploi :
    //
    // Contrat :
    //
//-------------------------------------------- Constructeurs - destructeur
    Provider(const Provider& unProvider);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Provider(int id);
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    Provider(int id, Cleaner &unCleaner);
    // Mode d'emploi :
    //
    // Contrat :
    //

    Provider();
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Provider();
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
    int providerID;
    vector<Cleaner> cleaners;
    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés
};

#endif // GOVERNMENTAGENCY_H
