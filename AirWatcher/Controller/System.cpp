/*************************************************************************
                           System  -  description
                             -------------------
    début                : 06/05/2021
    copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
    e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
                           benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/

#include "System.h"
#include <iostream>
using namespace std;

void System::InitializedMeasurement()
{
	initialTime = clock();
}

void System::EndMeasurement()
{
	finalTime = clock();
}

double System::GetAlgorithmEfficiency()
{
	return ((double)(finalTime - initialTime))/ CLOCKS_PER_SEC;
}

System::System()
{
	initialTime = clock();
	finalTime = clock();
}
