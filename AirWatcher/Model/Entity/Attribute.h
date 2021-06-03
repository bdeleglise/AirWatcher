/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Interface de la classe <Attribute> (fichier Attribute.h) -----
#if ! defined ( ATTRIBUTE_H )
#define ATTRIBUTE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
using namespace std;

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <Attribute>
//
//
//------------------------------------------------------------------------ 
class Attribute
{

    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    string GetID() const;
    // Mode d'emploi :
    // Permet de récupérer l'attribut Id
    // Contrat :
    // Aucun
    
    string GetUnit() const;
    // Mode d'emploi :
    // Permet de récupérer l'attribut unit
    // Contrat :
    // Aucun

    string GetDescription() const;
    // Mode d'emploi :
    // Permet de récupérer l'attribut description
    // Contrat :
    // Aucun

    friend ostream& operator<<(ostream& os, const Attribute& unAtt);
    // Surcharge de l'opérateur << afin de gérer les informations sur la sortie standard.
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    


    Attribute();

    Attribute(string id, string unit, string desc);

    virtual ~Attribute();
    // Mode d'emploi :
    // Destructeur de la classe Attribute
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
    string attributeID;
    string unit;
    string description;
    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés

};

//----------------------------------------- Types d�pendants de <Attribute>

#endif // ATTRIBUTE_H