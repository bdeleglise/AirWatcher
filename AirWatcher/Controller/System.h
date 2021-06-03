#pragma once
#include <ctime>
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

