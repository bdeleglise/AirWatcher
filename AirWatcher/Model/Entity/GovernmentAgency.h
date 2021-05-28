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
    const int GetID() ;
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
    GovernmentAgency(const GovernmentAgency &unGovernmentAgency);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //
 
    GovernmentAgency(int id);
    // Mode d'emploi :
    //
    // Contrat :
    //

    GovernmentAgency();
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~GovernmentAgency();
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
    int governementAgencyID;

    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés
};

#endif // GOVERNMENTAGENCY_H
