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
    //
    // Contrat :
    //
    
    string GetUnit() const;


    string GetDescription() const;

    friend ostream& operator<<(ostream& os, const Attribute& unAtt);

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    


    Attribute();

    Attribute(string id, string unit, string desc);

    virtual ~Attribute();
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
    string attributeID;
    string unit;
    string description;
    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées

    //----------------------------------------------------------- Types privés

};

//----------------------------------------- Types d�pendants de <Attribute>

#endif // ATTRIBUTE_H