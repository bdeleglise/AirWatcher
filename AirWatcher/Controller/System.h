#pragma once
#include <ctime>
class System
{
public :
	void InitializedMeasurement();

	void EndMeasurement();

	double GetAlgorithmEfficiency();


	System();
private:
	clock_t  initialTime;
	clock_t  finalTime;
};

