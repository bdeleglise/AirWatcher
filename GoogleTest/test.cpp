#include "pch.h"
#include "../AirWatcher/Model/Entity/GovernmentAgency.h"
#include "../AirWatcher/Util/Date.h"
#include "../AirWatcher/Model/Entity/Cleaner.h"
#include "../AirWatcher/Model/Entity/Provider.h"
#include "../AirWatcher/Model/Entity/Attribute.h"
#include "../AirWatcher/Model/Entity/Measurement.h"
#include "../AirWatcher/Model/Entity/Sensor.h"
#include "../AirWatcher/Model/Entity/IndividualUser.h"

#include <vector>
#include <string>

TEST(TestCaseName, TestName) {
  EXPECT_TRUE(true);
}

TEST(TestGovernmentAgency, GovernmentInit) {
	GovernmentAgency g(6);
	EXPECT_EQ(6, g.GetID());
}

TEST(TestDate, CreateDate) {
	Date date;
	date.day = 12;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	EXPECT_EQ(2019, date.year);
	EXPECT_EQ(1, date.hour);
	EXPECT_EQ(5, date.min);
	EXPECT_EQ(5, date.month);
	EXPECT_EQ(01, date.sec);
	EXPECT_EQ(12, date.day);
}

TEST(TestDate, DateEqual) {
	Date date;
	date.day = 12;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Date date2;
	date2 = date;
	EXPECT_EQ(date2, date);
}

TEST(TestDate, CopyDate) {
	Date date;
	date.day = 12;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Date date2 = date;
	EXPECT_EQ(date2.day, 12);
}

TEST(TestDate, CompareDate) {
	Date date;
	date.day = 12;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Date date2;
	date.day = 11;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	EXPECT_LT(date2, date);
}

TEST(TestCleaner, InitCleaner) {
	Date date;
	date.day = 12;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Date date2;
	date.day = 29;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Cleaner cleaner(1,3, 25, 33.1, date, date2);
	EXPECT_EQ(cleaner.GetID(), 1);
	EXPECT_EQ(cleaner.GetLatitude(), 25);
	EXPECT_EQ(cleaner.GetProviderID(), 3);
	EXPECT_EQ(cleaner.GetStart(),date);
	EXPECT_EQ(cleaner.GetStop(), date2);
}

TEST(TestCleaner, CopyConstructCleaner) {
	Date date;
	date.day = 12;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Date date2;
	date.day = 29;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Cleaner cleaner(1, 3, 25, 33.1, date, date2);
	Cleaner cleaner2(cleaner);
	EXPECT_EQ(cleaner2.GetID(), 1);
	EXPECT_EQ(cleaner2.GetLatitude(), 25);
	EXPECT_EQ(cleaner2.GetProviderID(), 3);
	EXPECT_EQ(cleaner2.GetStart(), date);
	EXPECT_EQ(cleaner2.GetStop(), date2);
}

TEST(TestCleaner, CopyEqualCleaner) {
	Date date;
	date.day = 12;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Date date2;
	date.day = 29;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Cleaner cleaner(1, 3, 25, 33.1, date, date2);
	Cleaner cleaner2=cleaner;
	EXPECT_EQ(cleaner2.GetID(), 1);
	EXPECT_EQ(cleaner2.GetLatitude(), 25);
	EXPECT_EQ(cleaner2.GetProviderID(), 3);
	EXPECT_EQ(cleaner2.GetStart(), date);
	EXPECT_EQ(cleaner2.GetStop(), date2);
}

TEST(TestProvider, InitProvider)
{
	Provider provider(2);
	EXPECT_EQ(provider.GetID(), 2);
}

TEST(TestProvider, InitProviderWithCleaner) {
	Date date;
	date.day = 12;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Date date2;
	date.day = 29;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Cleaner cleaner(1, 3, 25, 33.1, date, date2);
	Provider provider(2, cleaner);
	EXPECT_EQ(provider.GetID(), 2);
	vector<Cleaner>* cleaners = provider.GetCleaners();
	EXPECT_EQ(cleaners->size(), 1);
}


TEST(TestProvider, AddCleanerProvider) {
	Date date;
	date.day = 12;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Date date2;
	date.day = 29;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Cleaner cleaner(1, 3, 25, 33.1, date, date2);
	Provider provider(2);
	provider.AddCleaner(cleaner);
	EXPECT_EQ(provider.GetID(), 2);
	vector<Cleaner>* cleaners = provider.GetCleaners();
	EXPECT_EQ(cleaners->size(), 1);
}

TEST(TestAttribute, InitAttribute) {
	Attribute att("O3", "µg/m3", "concentration d'ozone");
	EXPECT_EQ(att.GetDescription(), "concentration d'ozone");
}

TEST(TestMeasurement, InitMeasure) {
	Attribute att("O3", "µg/m3", "concentration d'ozone");
	Date date;
	date.day = 12;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Measurement mesure(date, 44.5, att);
	EXPECT_EQ(mesure.GetTime(), date);
	EXPECT_EQ(mesure.GetValue(), 44.5);
	EXPECT_EQ(mesure.GetAttribute().GetUnit(), att.GetUnit());
}

TEST(TestSensor, InitSensor) {
	Sensor s(1, 24.5, -76);
	EXPECT_EQ(s.GetID(), 1);
	EXPECT_EQ(s.GetLatitude(), 24.5);
	EXPECT_EQ(s.GetLongitude(), -76);
	EXPECT_EQ(s.GetState(), true);
}

TEST(TestSensor, SetStateSensor) {
	Sensor s(1, 24.5, -76);
	s.SetState(false);
	EXPECT_EQ(s.GetState(), false);
}

TEST(TestSensor, AddMeasurementSensor) {
	Attribute att("O3", "µg/m3", "concentration d'ozone");
	Date date;
	date.day = 12;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Measurement mesure(date, 44.5, att);
	Sensor s(1, 24.5, -76);
	s.AddMeasurement(mesure);
	EXPECT_EQ(s.GetMeasurements()->size(), 1);
	EXPECT_EQ((*s.GetMeasurements())[date][0].GetValue(), 44.5);
}

TEST(TestSensor, AddMeasurementsSensor) {
	Attribute att("O3", "µg/m3", "concentration d'ozone");
	Date date;
	date.day = 12;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Measurement mesure(date, 44.5, att);
	Measurement mesure2(date, 55.5, att);
	Sensor s(1, 24.5, -76);
	s.AddMeasurement(mesure);
	s.AddMeasurement(mesure2);
	EXPECT_EQ(s.GetMeasurements()->size(), 1);
	EXPECT_EQ((*s.GetMeasurements())[date].size(), 2);
}

TEST(TestSensor, CopySensor) {
	Attribute att("O3", "µg/m3", "concentration d'ozone");
	Date date;
	date.day = 12;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Measurement mesure(date, 44.5, att);
	Measurement mesure2(date, 55.5, att);
	Sensor s(1, 24.5, -76);
	s.AddMeasurement(mesure);
	s.AddMeasurement(mesure2);
	Sensor s2(s);
	EXPECT_EQ(s2.GetMeasurements()->size(), 1);
	EXPECT_EQ((*s2.GetMeasurements())[date].size(), 2);
}

TEST(TestIndividual, InitIndividual) {
	IndividualUser user(1);
	EXPECT_EQ(user.GetID(), 1);
	EXPECT_EQ(user.GetPoints(), 0);
	EXPECT_EQ(user.GetReliable(), true);
}

TEST(TestIndividual, AddPointIndividual) {
	IndividualUser user(1);
	user.SetPoints(user.GetPoints() + 1);
	EXPECT_EQ(user.GetPoints(), 1);
}

TEST(TestIndividual, AddSensor) {
	IndividualUser user(1);
	Sensor s(1, 24.5, -76);
	user.AddSensor(s);
	EXPECT_EQ(user.GetSensors()->size(), 1);
	EXPECT_EQ(s.GetUserID(), 1);
	EXPECT_EQ((*user.GetSensors())[0].GetUserID(), 1);
}

TEST(TestIndividual, AccesData) {
	IndividualUser user(IndividualUser(1));
	Attribute att("O3", "µg/m3", "concentration d'ozone");
	Date date;
	date.day = 12;
	date.hour = 1;
	date.min = 5;
	date.month = 05;
	date.sec = 01;
	date.year = 2019;
	Measurement mesure(date, 44.5, att);
	Sensor s(1, 24.5, -76);
	s.AddMeasurement(mesure);
	user.AddSensor(s);
	EXPECT_EQ((*user.GetSensors())[0].GetMeasurements()->size(), 1);
}

TEST(TestIndividual, SetUnReliable) {
	IndividualUser user(IndividualUser(1));
	Sensor s(1, 24.5, -76);
	user.AddSensor(s);
	user.SetReliable(false);
	EXPECT_EQ((*user.GetSensors())[0].GetState(), false);
	EXPECT_EQ(user.GetReliable(), false);
}