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
    int GetID() const;
    // Mode d'emploi :
    // Getter de l'attribut Id
    // Contrat :
    // aucun
    
    vector<Cleaner>* GetCleaners();

    // Mode d'emploi :
    // Getter de l'attribut cleaners
    // Contrat :
    // aucun

    void AddCleaner(Cleaner& unCleaner);

    // Mode d'emploi :
    // Méthode ajoutant un cleaner à la liste des cleaners à partir d'un pointeur sur ce cleaner
    // Contrat :
    // aucun

    void setCleaners(vector<Cleaner>& listcleaners);

    // Mode d'emploi :
    // Setter de l'attribut cleaners
    // Contrat :
    // aucun

    friend ostream& operator<<(ostream& os, const Provider& provider);
    // Surcharge de l'opérateur << permettant de gérer les information qu'on passe dans la sortie standard

//------------------------------------------------- Surcharge d'opérateurs
    bool operator ==(const Provider& unProvider);
    // Surcharge de l'opérateur == afin de comparer efficacement deux Providers

    bool operator <(const Provider& unProvider);
    // Surcharge de l'opérateur < qui permet de comparer deux Providers efficacement

    Provider& operator = (const Provider& unProvider);
    // Surcharge de l'opérateur = qui permet d'attribuer des valeurs aux attributs d'un objet de la classe Provider
//-------------------------------------------- Constructeurs - destructeur
    Provider(const Provider& unProvider);
    // Mode d'emploi (constructeur de copie) :
    // Constructeur de copie de la classe Provider
    // Contrat :
    // aucun

    Provider(int id);
    // Mode d'emploi :
    // Constructeur de la classe Provider
    // Contrat :
    // aucun
    
    Provider(int id, Cleaner &unCleaner);
    // Mode d'emploi :
    // Surcharge du Constructeur de la classe Provider
    // Contrat :
    //

    Provider();


    virtual ~Provider();
    // Mode d'emploi :
    // Destructeur de la classe Provider
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
    int providerID;
    vector<Cleaner> cleaners;
    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés
};

#endif // GOVERNMENTAGENCY_H
