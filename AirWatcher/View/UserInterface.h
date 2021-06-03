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
