#pragma once
#include <ctime>
#include "../Model/Entity/Sensor.h"
#include "../Model/Model.h"
class Statistics
{
public :
	int CircularMeanAirQuality(double latitude, double longitude, double radius, time_t* time=nullptr);

	double AirQualitySensor(Sensor* sensor, time_t* end = nullptr);

	Statistics(Model* unModel);

private :
	int atmoIndex(double O3, double So2, double No2, double Pm10);

	Model* model;
};

