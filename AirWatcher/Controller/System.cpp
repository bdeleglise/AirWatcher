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
	return ((double)finalTime - (double)initialTime)/ CLOCKS_PER_SEC;
}

System::System()
{
	initialTime = clock();
	finalTime = clock();
}
