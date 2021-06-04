/*************************************************************************
						   UserInterface  -  description
							 -------------------
	d�but                : 06/05/2021
	copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
	e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
						   benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/



#if ! defined (USERINTERFACE_H)
#define USERINTERFACE_H
#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include "../Controller/Statistics.h"
#include "../Controller/SensorManagement.h"
#include "../Controller/System.h"
using namespace std;


//------------------------------------------------------------------------ 
// Role de la classe UserInterface
// Cette classe de la couche Vue permet d implementer les diff�rentes interfaces utilisateur 
// elle appelle donc les m�thodes des couches Model et Controlleur
//-----------------------------------------------------------------------

class UserInterface
{
public:
	void MenuUI();
	// Mode d'emploi :
	// Affiche le menu de navigation
	// Contrat :
	// Aucun

	UserInterface(Model* unModel);
	// Mode d'emploi :
	// Lors de la cr�ation de l'interface on lui donne un param�tre le mod�le contenant les donn�es de r�f�rence
	// Contrat :
	// Aucun

private:
	int choice;
	bool evalPerformance;
	Model* model;
	System system;

	void statisticsUI();
	// Mode d'emploi :
	// Affiche les stats
	// Contrat :
	// Aucun

	void cleanerAnalysisUI();
	// Mode d'emploi :
	// Affiche la page pour la gestion des cleaners
	// Contrat :
	// Aucun

	void sensorUI();
	// Mode d'emploi :
	// Affiche la page pour la gestion des capteurs
	// Contrat :
	// Aucun

	void privateSensorsUI();
	// Mode d'emploi :
	// Affiche la page pour la gestion des capteurs priv�s
	// Contrat :
	// Aucun

	void displayATMO(double value, bool moyenne);
	// Mode d'emploi :
	// Affiche les informations de l'indice Atmo
	// Contrat :
	// Aucun

	void cleanInputBuffer();
	// Mode d'emploi :
	// Permet de vider le buffer lors d'une erreur de saisie
	// Contrat :
	// Aucun

	int getInput();
	// Mode d'emploi :
	// Permet de demander et de renvoyer un entier
	// Contrat :
	// Aucun

	double getYcoord();
	// Mode d'emploi :
	// Permet de demander et de renvoyer une longitude
	// Contrat :
	// Aucun

	double getXcoord();
	// Mode d'emploi :
	// Permet de demander et de renvoyer une latitude
	// Contrat :
	// Aucun

	double getRayon();
	// Mode d'emploi :
	// Permet de demander et de renvoyer un rayon
	// Contrat :
	// Le rayon demand� est en km et renvoy� avec l'�quivalence en degr� en France

	time_t getTime();
	// Mode d'emploi :
	// Permet de demander et de renvoyer une date
	// Contrat :
	// Aucun
};
#endif
