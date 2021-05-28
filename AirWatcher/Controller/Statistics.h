#pragma once
#include <ctime>
#include "../Model/Entity/Sensor.h"
#include "../Model/Model.h"
class Statistics
{
public :
	double CircularMeanAirQuality(double latitude, double longitude, double radius, time_t* time=nullptr);

	double AirQualitySensor(Sensor* sensor, time_t* end = nullptr);

	Statistics(Model* unModel);

private :
	double atmoIndex(double O3, double So2, double No2, double Pm10);

	Model* model;
};

