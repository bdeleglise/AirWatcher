/*************************************************************************
                           GovernmentAgency  -  description
                             -------------------
    début                : 06/05/2021
    copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
    e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
                           benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/

#pragma once
//---------- Interface de la classe <GovernmentAgency> (fichier GovernmentAgency.h) ------
#if ! defined ( GOVERNMENTAGENCY_H )
#define GOVERNMENTAGENCY_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include "User.h"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Role de la classe <GovernmentAgency>
// Cette classe entity de la couche Model de MVC, est heritiere de la classe mere User
// elle s'occupe de la gestion des agences 
// gouvernementales, à travers elle on obtient l'id de l'agence 
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
