#if ! defined (USERINTERFACE_H)
#define USERINTERFACE_H
#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include "../Controller/Statistics.h"
#include "../Controller/SensorManagement.h"
using namespace std;



class UserInterface
{
public:
	UserInterface(Model* unModel);
	void MenuUI();
private:
	int choice;
	Model* model;
	void StatisticsUI();
	void FraudUI();
	int GetInput();
	int getYcoord();
	int getXcoord();
	int getRayon();
	time_t getTime();
};
#endif
