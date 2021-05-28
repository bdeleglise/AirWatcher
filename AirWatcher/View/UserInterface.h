#if ! defined (USERINTERFACE_H)
#define USERINTERFACE_H
#pragma once
#include <iostream>
#include <string>
#include <time.h>
using namespace std;



class UserInterface
{
public:
	void MenuUI();
private:
	int choice;
	void StatisticsUI();
	int GetInput();
	int getYcoord();
	int getXcoord();
	int getRayon();
	time_t getTime();
};
#endif
