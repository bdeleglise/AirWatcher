#include "pch.h"
#include "../AirWatcher/Model/Entity/GovernmentAgency.h"
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
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	EXPECT_EQ(2019, tmp.tm_year +1900);
	EXPECT_EQ(1, tmp.tm_hour);
	EXPECT_EQ(5, tmp.tm_mon+1);
	EXPECT_EQ(12, tmp.tm_mday);
}

TEST(TestDate, DateEqual) {
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date = mktime(&tmp);
	tmp.tm_mday = 11;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date2 = date;
	EXPECT_EQ(date2, date);
}

TEST(TestDate, CopyDate) {
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	tm tmp2 =tmp;
	EXPECT_EQ(tmp2.tm_mday, 12);
}

TEST(TestDate, CompareDate) {
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date = mktime(&tmp);
	tmp.tm_mday = 11;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date2 = mktime(&tmp);
	EXPECT_LT(date2, date);
}

TEST(TestCleaner, InitCleaner) {
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date = mktime(&tmp);
	tmp.tm_mday = 29;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date2 = mktime(&tmp);

	Cleaner cleaner(1,3, 25, 33.1, date, date2);
	EXPECT_EQ(cleaner.GetID(), 1);
	EXPECT_EQ(cleaner.GetLatitude(), 25);
	EXPECT_EQ(cleaner.GetProviderID(), 3);
	EXPECT_EQ(cleaner.GetStart(), date);
	EXPECT_EQ(cleaner.GetStop(), date2);
}

TEST(TestCleaner, CopyConstructCleaner) {
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date = mktime(&tmp);
	tmp.tm_mday = 29;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date2 = mktime(&tmp);
	Cleaner cleaner(1, 3, 25, 33.1, date, date2);
	Cleaner cleaner2(cleaner);
	EXPECT_EQ(cleaner2.GetID(), 1);
	EXPECT_EQ(cleaner2.GetLatitude(), 25);
	EXPECT_EQ(cleaner2.GetProviderID(), 3);
	EXPECT_EQ(cleaner2.GetStart(), date);
	EXPECT_EQ(cleaner2.GetStop(), date2);
}

TEST(TestCleaner, CopyEqualCleaner) {
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date = mktime(&tmp);
	tmp.tm_mday = 29;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date2 = mktime(&tmp);
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
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date = mktime(&tmp);
	tmp.tm_mday = 29;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date2 = mktime(&tmp);
	Cleaner cleaner(1, 3, 25, 33.1, date, date2);
	Provider provider(2, cleaner);
	EXPECT_EQ(provider.GetID(), 2);
	vector<Cleaner>* cleaners = provider.GetCleaners();
	EXPECT_EQ(cleaners->size(), 1);
}


TEST(TestProvider, AddCleanerProvider) {
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date = mktime(&tmp);
	tmp.tm_mday = 29;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date2 = mktime(&tmp);
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
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date = mktime(&tmp);
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
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date = mktime(&tmp);
	Measurement mesure(date, 44.5, att);
	Sensor s(1, 24.5, -76);
	s.AddMeasurement(mesure);
	EXPECT_EQ(s.GetMeasurements()->size(), 1);
	EXPECT_EQ((*s.GetMeasurements())[date][0].GetValue(), 44.5);
}

TEST(TestSensor, AddMeasurementsSensor) {
	Attribute att("O3", "µg/m3", "concentration d'ozone");
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date = mktime(&tmp);
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
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date = mktime(&tmp);
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
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	time_t date = mktime(&tmp);
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