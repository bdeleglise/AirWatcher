﻿/*************************************************************************
                           User  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Interface de la classe <User> (fichier User.h) ------
#if ! defined ( USER_H )
#define USER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <User>
//
//
//------------------------------------------------------------------------ 

#pragma once
class User
{

    //----------------------------------------------------------------- PUBLIC

    public:
    //----------------------------------------------------- Méthodes publiques
        virtual int GetID() = 0;
        // Mode d'emploi :
        //
        // Contrat :
        //


    //------------------------------------------------- Surcharge d'opérateurs
      
    //-------------------------------------------- Constructeurs - destructeur
        

        virtual ~User();
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

        //---------------------------------------------------------- Classes amies

        //-------------------------------------------------------- Classes privées

        //----------------------------------------------------------- Types privés

};

//----------------------------------------- Types d�pendants de <${file_base}>

#endif // XXX_H