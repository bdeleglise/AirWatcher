#pragma once
/*************************************************************************
                           GovernmentAgency  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Interface de la classe <GovernmentAgency> (fichier GovernmentAgency.h) ------
#if ! defined ( GOVERNMENTAGENCY_H )
#define GOVERNMENTAGENCY_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include "User.h"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <GovernmentAgency>
//
//
//------------------------------------------------------------------------ 
class GovernmentAgency :
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


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
    GovernmentAgency(const GovernmentAgency &unGovernmentAgency);
    // Mode d'emploi (constructeur de copie) :
    // Constructeur de copie de la classe GovernmentAgency
    // Contrat :
    // aucun
 
    GovernmentAgency(int id);
    // Mode d'emploi :
    // Constructeur de la classe GovernmentAgency
    // Contrat :
    // aucun

    GovernmentAgency();
    // Mode d'emploi :
    // 
    // Contrat :
    //

    virtual ~GovernmentAgency();
    // Mode d'emploi :
    // Destructeur de la classe GovernmentAgency
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
    int governementAgencyID;

    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés
};

#endif // GOVERNMENTAGENCY_H
