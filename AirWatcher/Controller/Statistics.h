#pragma once
#include <ctime>
#include "../Model/Entity/Sensor.h"
class Statistics
{
public :
	static double CircularMeanAirQuality(double latitude, double longitude, double radius, time_t* time=nullptr);

	static double AirQualitySensor(Sensor* sensor, time_t* end = nullptr);

private :
	static double atmoIndex(double O3, double So2, double No2, double Pm10);
};

