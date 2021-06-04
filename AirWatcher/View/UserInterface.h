/*************************************************************************
						   UserInterface  -  description
							 -------------------
	début                : 06/05/2021
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
// Cette classe de la couche Vue permet d implementer les différentes interfaces utilisateur 
// elle appelle donc les méthodes des couches Model et Controlleur
//-----------------------------------------------------------------------

class UserInterface
{
public:
	UserInterface(Model* unModel);
	void MenuUI();
private:
	int choice;
	bool evalPerformance;


	Model* model;
	System system;
	void statisticsUI();
	void cleanerAnalysisUI();
	void sensorUI();
	void privateSensorsUI();
	void displayATMO(double value, bool moyenne);
	void cleanInputBuffer();
	int getInput();
	double getYcoord();
	double getXcoord();
	double getRayon();
	time_t getTime();
};
#endif
