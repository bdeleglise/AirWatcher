#pragma once
#include <ctime>
class Statistics
{
public :
	static double CircularMeanAirQuality(double latitude, double longitude, double radius, time_t* time=nullptr);


private :
	static double atmoIndex(double O3, double So2, double No2, double Pm10);
};

