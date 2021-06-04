/*************************************************************************
						   System  -  description
							 -------------------
	début                : 06/05/2021
	copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
	e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
						   benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/


#pragma once
#include <ctime>

// Role de la classe <System>
// Cette classe appartient a la couche Controlleur
// Elle gère la date de début et fin des mesures, et permet aussi de calculer le temps que l algorithme a mis
// à tourner, ie l efficacite

class System
{
public :
	void InitializedMeasurement();

	// Mode d'emploi :
	// permet d'enregistrer la date de début des mesures
	// Contrat :
	// Aucun

	void EndMeasurement();

	// Mode d'emploi :
	// permet d'enregistrer la date de fin des mesures
	// Contrat :
	// Aucun

	double GetAlgorithmEfficiency();

	// Mode d'emploi :
	// permet de calculer le temps que l'algorithme a mis à tourner.
	// Contrat :
	// Aucun

	System();
private:
	clock_t  initialTime;
	clock_t  finalTime;
};

