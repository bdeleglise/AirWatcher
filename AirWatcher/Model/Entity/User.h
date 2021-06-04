/*************************************************************************
                           User  -  description
                             -------------------
    début                : 06/05/2021
    copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
    e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
                           benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
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
// Cette classe entity abstraite de la couche Model de MVC, il s'agit de classe mere
// elle a la méthodes abstraite getID() qu'il faudra redéfinir dans les classes filles
//
//------------------------------------------------------------------------ 

#pragma once
class User
{

    //----------------------------------------------------------------- PUBLIC

    public:
    //----------------------------------------------------- Méthodes publiques
        virtual int GetID() const = 0;
        // Mode d'emploi :
        // Getter de l'attribut Id
        // Contrat :
        // aucun


    //------------------------------------------------- Surcharge d'opérateurs
      
    //-------------------------------------------- Constructeurs - destructeur
        

        virtual ~User();
        // Mode d'emploi :
        // Destructeur de la classe User
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