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
#include "../AirWatcher/Model/Model.h"
#include "../AirWatcher/Controller/Statistics.h"

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



/*namespace my_namespace {
	class ModelTest : public ::testing::Test {
	public :
		ModelTest() {
		}
		~ModelTest() {

		}
		virtual void SetUp(void) {
			if (model != nullptr) {
				cout << "test 3" << endl;
				delete model;
			}
			model = new Model();
			model->LoadData();
			cout << "test 1" << endl;
		}
		virtual void TearDown(void) {
			delete model;
			cout << "test 2" << endl;
		}

	protected:
		Model* model;
	};
	 
	TEST_F(ModelTest, ReadData) {
		EXPECT_EQ(model->GetCleaners()->size(), 2);
		EXPECT_EQ(model->GetProviders()->size(), 2);
		EXPECT_EQ(model->GetIndividuals()->size(), 2);
		EXPECT_EQ(model->GetSensors()->size(), 100);
		EXPECT_EQ(model->GetPrivateSensors()->size(), 2);
	}

	TEST_F(ModelTest, SearchIndividual) {
		IndividualUser* user = model->SearchIndividual(0);
		EXPECT_EQ(user->GetID(), 0);
		EXPECT_EQ(user->GetReliable(), true);
		EXPECT_EQ(user->GetSensors()->begin()->GetID(), 70);

		user = model->SearchIndividual(25);
	}

}  // namespace my_namespace*/

class TestEnvironment : public ::testing::Environment {
public:
	// Assume there's only going to be a single instance of this class, so we can just
	// hold the timestamp as a const static local variable and expose it through a
	// static member function
	static std::string getStartTime() {
		static const std::string timestamp = "youpi";
		return timestamp;
	}

	static Model* getModel() {
		static Model model;
		model.LoadData();
		return &model;
	}
	// Initialise the timestamp in the environment setup.
	virtual void SetUp() { getModel(); }
};

TEST(CnFirstTest, Test2) {
	std::cout << TestEnvironment::getModel()->GetSensors()->size() << std::endl;
}

TEST(ModelTest, ReadData) {
	Model* model = TestEnvironment::getModel();
	EXPECT_EQ(model->GetCleaners()->size(), 2);
	EXPECT_EQ(model->GetProviders()->size(), 2);
	EXPECT_EQ(model->GetIndividuals()->size(), 2);
	EXPECT_EQ(model->GetSensors()->size(), 100);
	EXPECT_EQ(model->GetPrivateSensors()->size(), 2);
}
TEST(ModelTest, ReadData2) {
	Model* model = TestEnvironment::getModel();
	EXPECT_EQ(model->GetCleaners()->size(), 2);
	EXPECT_EQ(model->GetProviders()->size(), 2);
	EXPECT_EQ(model->GetIndividuals()->size(), 2);
	EXPECT_EQ(model->GetSensors()->size(), 100);
	EXPECT_EQ(model->GetPrivateSensors()->size(), 2);
}
TEST(ModelTest, SearchIndividual) {
	Model* model = TestEnvironment::getModel();
	IndividualUser* user = model->SearchIndividual(0);
	EXPECT_EQ(user->GetID(), 0);
	EXPECT_EQ(user->GetReliable(), true);
	EXPECT_EQ(user->GetSensors()->begin()->GetID(), 70);

	user = model->SearchIndividual(25);
	delete model;
}

/*TEST(ModelTest, SearchGovernmentAgency) {
	Model model;
	model.LoadData();
	EXPECT_EQ(model.SearchGovernmentAgency(2), nullptr);
}

TEST(ModelTest, SearchIndividual) {
	Model model;
	model.LoadData();
	IndividualUser* user = model.SearchIndividual(0);
	EXPECT_EQ(user->GetID(), 0);
	EXPECT_EQ(user->GetReliable(), true);
	EXPECT_EQ(user->GetSensors()->begin()->GetID(), 70);

	user = model.SearchIndividual(25);
	EXPECT_EQ(user, nullptr);
}

TEST(ModelTest, SearchProvider) {
	Model model;
	model.LoadData();
	Provider* user = model.SearchProvider(0);
	EXPECT_EQ(user->GetID(), 0);
	EXPECT_EQ(user->GetCleaners()->begin()->GetID(), 0);

	user = model.SearchProvider(25);
	EXPECT_EQ(user, nullptr);
}

TEST(ModelTest, SearchCleaner) {
	Model model;
	model.LoadData();
	Cleaner* cleaner = model.SearchCleaner(0);
	EXPECT_EQ(cleaner->GetID(), 0);
	EXPECT_EQ(cleaner->GetLatitude(), 45.333333);
	EXPECT_EQ(cleaner->GetLongitude(), 1.333333);

	cleaner = model.SearchCleaner(29);
	EXPECT_EQ(cleaner, nullptr);
}

TEST(ModelTest, SearchSensor) {
	Model model;
	model.LoadData();
	Sensor* sensor = model.SearchSensor(1);
	EXPECT_EQ(sensor->GetID(), 1);
	EXPECT_EQ(sensor->GetLatitude(), 44);
	EXPECT_EQ(sensor->GetLongitude(), -0.3);
	EXPECT_EQ(sensor->GetMeasurements()->size(), 365);

	sensor = model.SearchSensor(1500);
	EXPECT_EQ(sensor, nullptr);
}

TEST(StatisticsTest, CircularMeanAirQualityDateNULLRayonNULL) {
	Model model;
	model.LoadData();
	Statistics stat = (&model);
	double test = stat.CircularMeanAirQuality(44, 0, 0, nullptr);
	EXPECT_EQ(test, 2);
}

TEST(StatisticsTest, CircularMeanAirQualityRayonNull) {
	Model model;
	model.LoadData();
	Statistics stat = (&model);
	tm tmp = tm();
	tmp.tm_mday = 28;
	tmp.tm_mon = 3 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 12;
	time_t date = mktime(&tmp);
	double test = stat.CircularMeanAirQuality(44, 0, 0, &date);
	EXPECT_EQ(test, 2);
}

TEST(StatisticsTest, CircularMeanAirQualityDateNULL) {
	Model model;
	model.LoadData();
	Statistics stat = (&model);
	double test = stat.CircularMeanAirQuality(44, 0, 0.4, nullptr);
	EXPECT_EQ(test, 2);
}

TEST(StatisticsTest, CircularMeanAirQuality) {
	Model model;
	model.LoadData();
	Statistics stat = (&model);
	tm tmp = tm();
	tmp.tm_mday = 9;
	tmp.tm_mon = 2 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 12;
	time_t date = mktime(&tmp);
	double test = stat.CircularMeanAirQuality(44, 0, 0, &date);
	EXPECT_EQ(test, 2);
}

TEST(StatisticsTest, AirQualitySensorDateNULLSensorNULL) {
	Model model;
	model.LoadData();
	Statistics stat = (&model);
	double test = stat.AirQualitySensor(nullptr);
	EXPECT_EQ(test, -1);
}

TEST(StatisticsTest, AirQualitySensorDateNULL) {
	Model model;
	model.LoadData();
	Statistics stat = (&model);
	Sensor* sensor = model.SearchSensor(36);
	double test = stat.AirQualitySensor(sensor);
	EXPECT_EQ(test, 1.75);
}

TEST(StatisticsTest, AirQualitySensor) {
	Model model;
	model.LoadData();
	Statistics stat = (&model);
	tm tmp = tm();
	tmp.tm_mday = 3;
	tmp.tm_mon = 12 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 12;
	time_t date = mktime(&tmp);
	Sensor* sensor = model.SearchSensor(36);
	double test = stat.AirQualitySensor(sensor, &date);
	EXPECT_EQ(test, 1.75);
}

TEST(StatisticsTest, AirQualitySensorWrongFormat) {
	Model model;
	model.LoadData();
	Statistics stat = (&model);
	tm tmp = tm();
	tmp.tm_mday = 3;
	tmp.tm_mon = 12 - 1;
	tmp.tm_year = 2017 - 1900;
	tmp.tm_hour = 12;
	time_t date = mktime(&tmp);
	Sensor* sensor = model.SearchSensor(36);
	double test = stat.AirQualitySensor(sensor, &date);
	EXPECT_EQ(test, -2);

	tmp.tm_mday = 3;
	tmp.tm_mon = 12 - 1;
	tmp.tm_year = 2020 - 1900;
	tmp.tm_hour = 12;
	date = mktime(&tmp);
	test = stat.AirQualitySensor(sensor, &date);
	EXPECT_EQ(test, -2);
}

TEST(ModelTest, UpdateSensorStateSensorOfGovernement) {
	Model model;
	model.LoadData();
	Sensor* sensor = model.SearchSensor(99);
	int size1 = model.GetSensors()->size();
	int size2 = model.GetMaintenanceSensors()->size();
	EXPECT_EQ(sensor->GetState(), true);
	model.UpdateSensorState(99);
	sensor = model.SearchSensor(99);
	EXPECT_EQ(sensor->GetState(), false);
	EXPECT_EQ(model.GetSensors()->size(), size1-1);
	EXPECT_EQ(model.GetMaintenanceSensors()->size(), size2+1);

	model.UpdateSensorState(99);
	sensor = model.SearchSensor(99);
	EXPECT_EQ(sensor->GetState(), true);
	EXPECT_EQ(model.GetSensors()->size(), size1 );
	EXPECT_EQ(model.GetMaintenanceSensors()->size(), size2 );
}

TEST(ModelTest, UpdateIndividualState) {
	Model model;
	model.LoadData();
	IndividualUser* user = model.SearchIndividual(1);
	int size1 = model.GetSensors()->size();
	int size2 = model.GetMaliciousIndividualSensors()->size();
	int size3 = model.GetPrivateSensors()->size();
	EXPECT_EQ(user->GetReliable(), true);
	model.UpdateIndividualState(user->GetID());
	EXPECT_EQ(user->GetReliable(), false);
	EXPECT_EQ(model.GetSensors()->size(), size1 - 1);
	EXPECT_EQ(model.GetMaintenanceSensors()->size(), size2 + 1);
	EXPECT_EQ(model.GetMaintenanceSensors()->size(), size3 - 1);
	vector<Sensor>* sensors = user->GetSensors();
	vector<Sensor>::iterator iter;
	for (iter = sensors->begin(); iter != sensors->end(); ++iter) {
		EXPECT_EQ(iter->GetState(), false);
	}
}*/