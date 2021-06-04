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
#include <utility>
#include "../AirWatcher/Model/Model.h"
#include "../AirWatcher/Controller/Statistics.h"
#include "../AirWatcher/Controller/SensorManagement.h"

/**
* Cette classe permet d'accéder aux données de test
* ATTENTION avant de lancer les tests assurez vous que le chemin du ReaderConfig pointe bien vers le répertoire de tests.
**/
class TestEnvironment : public ::testing::Environment {
public:
	// Assume there's only going to be a single instance of this class, so we can just
	// hold the modal as a const static local variable and expose it through a
	// static member function
	static Model* getModel() {
		static Model model;
		model.LoadData();
		return &model;
	}
	// Initialise the timestamp in the environment setup.
	virtual void SetUp() { getModel(); }
};

// Test de google test
TEST(TestCaseName, TestName) {
  EXPECT_TRUE(true);
}

//Test de la création d'un utilisateur de l'agence
TEST(TestGovernmentAgency, GovernmentInit) {
	GovernmentAgency g(6);
	EXPECT_EQ(6, g.GetID());
}

//Test de la création d'une date
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

//Test de l'égalité des dates
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

//Test de la copie des dates
TEST(TestDate, CopyDate) {
	tm tmp = tm();
	tmp.tm_mday = 12;
	tmp.tm_mon = 5 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 1;
	tm tmp2 =tmp;
	EXPECT_EQ(tmp2.tm_mday, 12);
}

//Test de la comparaison des dates
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

//Test de la création d'un cleaner
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

//Test de la création d'un provider
TEST(TestProvider, InitProvider)
{
	Provider provider(2);
	EXPECT_EQ(provider.GetID(), 2);
}

//Test de la création d'un provider avec un cleaner
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

//Test de l'ajout d'un cleaner à un provider existant
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

//Test de la création d'un attribut
TEST(TestAttribute, InitAttribute) {
	Attribute att("O3", "µg/m3", "concentration d'ozone");
	EXPECT_EQ(att.GetDescription(), "concentration d'ozone");
}

//Test de la création d'un mesure
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

//Test de la création d'un capteur
TEST(TestSensor, InitSensor) {
	Sensor s(1, 24.5, -76);
	EXPECT_EQ(s.GetID(), 1);
	EXPECT_EQ(s.GetLatitude(), 24.5);
	EXPECT_EQ(s.GetLongitude(), -76);
	EXPECT_EQ(s.GetState(), true);
}

//Test du changement d'état d'un capteur
TEST(TestSensor, SetStateSensor) {
	Sensor s(1, 24.5, -76);
	s.SetState(false);
	EXPECT_EQ(s.GetState(), false);
}

//Test de l'ajour d'une mesure à un capteur
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

//Test de l'ajout de plusieurs mesures à un capteur
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

//Test de la copie des mesures avec la copie des capteurs
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

//Test de la création d'un utilisateur privé
TEST(TestIndividual, InitIndividual) {
	IndividualUser user(1);
	EXPECT_EQ(user.GetID(), 1);
	EXPECT_EQ(user.GetPoints(), 0);
	EXPECT_EQ(user.GetReliable(), true);
}

//Test de l'ajout d'un point à un utilisateur privé
TEST(TestIndividual, AddPointIndividual) {
	IndividualUser user(1);
	user.SetPoints(user.GetPoints() + 1);
	EXPECT_EQ(user.GetPoints(), 1);
}

//Test de l'ajout d'un capteur à l'utilisateur privé
TEST(TestIndividual, AddSensor) {
	IndividualUser user(1);
	Sensor s(1, 24.5, -76);
	user.AddSensor(s);
	EXPECT_EQ(user.GetSensors()->size(), 1);
	EXPECT_EQ(s.GetUserID(), 1);
	EXPECT_EQ((*user.GetSensors())[0].GetUserID(), 1);
}

//Test de l'accès aux données d'un utilisateur privé
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

//Test du changement d'état d'un utilisateur privé
TEST(TestIndividual, SetUnReliable) {
	IndividualUser user(IndividualUser(1));
	Sensor s(1, 24.5, -76);
	user.AddSensor(s);
	user.SetReliable(false);
	EXPECT_EQ((*user.GetSensors())[0].GetState(), false);
	EXPECT_EQ(user.GetReliable(), false);
}

//Test de la lecture des données des fichiers csv
TEST(ModelTest, ReadData) {
	Model* model = TestEnvironment::getModel();
	EXPECT_EQ(model->GetCleaners()->size(), 2);
	EXPECT_EQ(model->GetProviders()->size(), 2);
	EXPECT_EQ(model->GetIndividuals()->size(), 2);
	EXPECT_EQ(model->GetSensors()->size(), 100);
	EXPECT_EQ(model->GetPrivateSensors()->size(), 2);
}

//Test de la recherche d'un utilisateur de l'agence gouvernementale
TEST(ModelTest, SearchGovernmentAgency) {
	Model* model = TestEnvironment::getModel();
	EXPECT_EQ(model->SearchGovernmentAgency(2), nullptr);
}

//Test de la recherche d'un utilisateur privé
TEST(ModelTest, SearchIndividual) {
	Model* model = TestEnvironment::getModel();
	IndividualUser* user = model->SearchIndividual(0);
	EXPECT_EQ(user->GetID(), 0);
	EXPECT_EQ(user->GetReliable(), true);
	EXPECT_EQ(user->GetSensors()->begin()->GetID(), 70);

	user = model->SearchIndividual(25);
	EXPECT_EQ(user, nullptr);
}

//Test de la recherche d'un provider
TEST(ModelTest, SearchProvider) {
	Model* model = TestEnvironment::getModel();
	Provider* user = model->SearchProvider(0);
	EXPECT_EQ(user->GetID(), 0);
	EXPECT_EQ(user->GetCleaners()->begin()->GetID(), 0);

	user = model->SearchProvider(25);
	EXPECT_EQ(user, nullptr);
}

//Test de la recherche d'un cleaner
TEST(ModelTest, SearchCleaner) {
	Model* model = TestEnvironment::getModel();
	Cleaner* cleaner = model->SearchCleaner(0);
	EXPECT_EQ(cleaner->GetID(), 0);
	EXPECT_EQ(cleaner->GetLatitude(), 45.333333);
	EXPECT_EQ(cleaner->GetLongitude(), 1.333333);

	cleaner = model->SearchCleaner(29);
	EXPECT_EQ(cleaner, nullptr);
}

//Test de la recherche d'un capteur
TEST(ModelTest, SearchSensor) {
	Model* model = TestEnvironment::getModel();
	Sensor* sensor = model->SearchSensor(1);
	EXPECT_EQ(sensor->GetID(), 1);
	EXPECT_EQ(sensor->GetLatitude(), 44);
	EXPECT_EQ(sensor->GetLongitude(), -0.3);
	EXPECT_EQ(sensor->GetMeasurements()->size(), 365);

	sensor = model->SearchSensor(1500);
	EXPECT_EQ(sensor, nullptr);
}

//Test du calcul de la qualité de l'air en un point précis avec une date null
TEST(StatisticsTest, CircularMeanAirQualityDateNULLRayonNULL) {
	Model* model = TestEnvironment::getModel();
	Statistics stat(model);
	int test = stat.CircularMeanAirQuality(44, 0, 0, nullptr);
	EXPECT_EQ(test, 8);
}

//Test du calcul de la qualité de l'air en un point précis
TEST(StatisticsTest, CircularMeanAirQualityRayonNull) {
	Model* model = TestEnvironment::getModel();;
	Statistics stat (model);
	tm tmp = tm();
	tmp.tm_mday = 28;
	tmp.tm_mon = 3 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 12;
	time_t date = mktime(&tmp);
	int test = stat.CircularMeanAirQuality(44, 0, 0, &date);
	EXPECT_EQ(test, 8);
}

//Test du calcul de la qualité de l'air dans une zone avec une date null
TEST(StatisticsTest, CircularMeanAirQualityDateNULL) {
	Model* model = TestEnvironment::getModel();
	Statistics stat(model);
	int test = stat.CircularMeanAirQuality(44, 0, 0.4, nullptr);
	EXPECT_EQ(test, 7);
}

//Test du calcul de la qualité de l'air dans une zone 
TEST(StatisticsTest, CircularMeanAirQuality) {
	Model* model = TestEnvironment::getModel();
	Statistics stat(model);
	tm tmp = tm();
	tmp.tm_mday = 9;
	tmp.tm_mon = 2 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 12;
	time_t date = mktime(&tmp);
	int test = stat.CircularMeanAirQuality(44, 0, 0.4, &date);
	EXPECT_EQ(test, 8);
}

//Test d'un cas d'erreur du calcul de la qualité de l'air
TEST(StatisticsTest, CircularMeanAirQualityNoData) {
	Model* model = TestEnvironment::getModel();
	Statistics stat(model);
	tm tmp = tm();
	tmp.tm_mday = 1;
	tmp.tm_mon = 1 - 1;
	tmp.tm_year = 2000 - 1900;
	tmp.tm_hour = 12;
	time_t date = mktime(&tmp);
	int test = stat.CircularMeanAirQuality(44, 0, 0.4, &date);
	EXPECT_EQ(test, -2);
}

//Test de l'incrémentation des points d'un utilisateur privé
TEST(StatisticsTest, IncrementPrivateUserPoint) {
	Model* model = TestEnvironment::getModel();
	Statistics stat(model);
	int test = stat.CircularMeanAirQuality(45.2, 3.2, 0.01, nullptr);
	IndividualUser* individual = model->SearchIndividual(1);
	EXPECT_EQ(individual->GetPoints(), 1);
}

//Test d'un cas d'erreur du calcul de la qualité de l'air moyenne mesuré par un capteur null
TEST(StatisticsTest, AirQualitySensorDateNULLSensorNULL) {
	Model* model = TestEnvironment::getModel();
	Statistics stat(model);
	double test = stat.AirQualitySensor(nullptr);
	EXPECT_EQ(test, -1);
}

//Test de la mesure de la qualité de l'air moyenne de la dernière semaine mesurée par un capteur
TEST(StatisticsTest, AirQualitySensorDateNULL) {
	Model* model = TestEnvironment::getModel();
	Statistics stat(model);
	Sensor* sensor = model->SearchSensor(36);
	double test = stat.AirQualitySensor(sensor);
	EXPECT_GT(test, 6.42);
	EXPECT_LT(test, 6.43);
}

//Test de la mesure de la qualité de l'air moyenne pour une semaine précise mesurée par un capteur
TEST(StatisticsTest, AirQualitySensor) {
	Model* model = TestEnvironment::getModel();
	Statistics stat(model);
	tm tmp = tm();
	tmp.tm_mday = 3;
	tmp.tm_mon = 12 - 1;
	tmp.tm_year = 2019 - 1900;
	tmp.tm_hour = 12;
	time_t date = mktime(&tmp);
	Sensor* sensor = model->SearchSensor(36);
	double test = stat.AirQualitySensor(sensor, &date);
	EXPECT_GT(test, 4.71);
	EXPECT_LT(test, 4.72);
}

//Test d'un cas d'erreur de la mesure de la moyenne de la qualité de l'air d'un capteur
TEST(StatisticsTest, AirQualitySensorWrongFormat) {
	Model* model = TestEnvironment::getModel();
	Statistics stat(model);
	tm tmp = tm();
	tmp.tm_mday = 3;
	tmp.tm_mon = 12 - 1;
	tmp.tm_year = 2017 - 1900;
	tmp.tm_hour = 12;
	time_t date = mktime(&tmp);
	Sensor* sensor = model->SearchSensor(36);
	double test = stat.AirQualitySensor(sensor, &date);
	EXPECT_EQ(test, -2);
}

//Test du changement d'état d'un capteur
TEST(ModelTest, UpdateSensorStateSensorOfGovernement) {
	Model* model = TestEnvironment::getModel();
	Sensor* sensor = model->SearchSensor(99);
	size_t size1 = model->GetSensors()->size();
	size_t size2 = model->GetMaintenanceSensors()->size();
	EXPECT_EQ(sensor->GetState(), true);
	model->UpdateSensorState(99);
	sensor = model->SearchSensor(99);
	EXPECT_EQ(sensor->GetState(), false);
	EXPECT_EQ(model->GetSensors()->size(), size1-1);
	EXPECT_EQ(model->GetMaintenanceSensors()->size(), size2+1);

	model->UpdateSensorState(99);
	sensor = model->SearchSensor(99);
	EXPECT_EQ(sensor->GetState(), true);
	EXPECT_EQ(model->GetSensors()->size(), size1 );
	EXPECT_EQ(model->GetMaintenanceSensors()->size(), size2 );
}

//Test du changement d'état d'un utilisateur privé
TEST(ModelTest, UpdateIndividualState) {
	Model* model = TestEnvironment::getModel();
	IndividualUser* user = model->SearchIndividual(1);
	size_t size1 = model->GetSensors()->size();
	size_t size2 = model->GetMaliciousIndividualSensors()->size();
	size_t size3 = model->GetPrivateSensors()->size();
	EXPECT_EQ(user->GetReliable(), true);
	model->UpdateIndividualState(user->GetID());
	EXPECT_EQ(user->GetReliable(), false);
	EXPECT_EQ(model->GetSensors()->size(), size1 - 1);
	EXPECT_EQ(model->GetMaliciousIndividualSensors()->size(), size2 + 1);
	EXPECT_EQ(model->GetPrivateSensors()->size(), size3 - 1);
	vector<Sensor>* sensors = user->GetSensors();
	vector<Sensor>::iterator iter;
	for (iter = sensors->begin(); iter != sensors->end(); ++iter) {
		EXPECT_EQ(iter->GetState(), false);
	}
	model->UpdateIndividualState(user->GetID());
	EXPECT_EQ(user->GetReliable(), true);
	EXPECT_EQ(model->GetSensors()->size(), size1 );
	EXPECT_EQ(model->GetMaliciousIndividualSensors()->size(), size2 );
	EXPECT_EQ(model->GetPrivateSensors()->size(), size3 );
}

//Test de la détection d'un capteur frauduleux
TEST(SensorManagementTest, DetectionFraudulentSensor)
{
	Model* model = TestEnvironment::getModel();
	SensorManagement sm(model);
	vector<pair<Sensor*, Confidence>>* frauds = sm.FraudulentSensorDetection();
	for (auto& currentPair : *frauds)
	{
		EXPECT_EQ(currentPair.first->GetID(), 36);
		EXPECT_EQ(currentPair.first->GetUserID(), 1);
	}



}

//Test de la détection d'aucun capteur frauduleux
TEST(SensorManagementTest, DetectionWithNoFraudulent)
{
	Model* model = TestEnvironment::getModel();
	SensorManagement sm(model);
	vector<pair<Sensor*, Confidence>>* frauds = sm.FraudulentSensorDetection();
	//On conserve le même dataset qu'on modifie à la main
	//car la gestion de plusieurs environnements avec Google Test est fastidieuse
	//et entraîne des erreurs de tests quin accèdent à des ressources critiques en même temps
	for (auto& currentPair : *frauds) 
	{
		EXPECT_EQ(currentPair.first->GetID(), 36);
		EXPECT_EQ(currentPair.first->GetUserID(), 1);
		model->UpdateSensorState(currentPair.first->GetID());
	}
	frauds = sm.FraudulentSensorDetection();
	EXPECT_EQ(frauds->size(), 0);

}

//Test dans le cas où il n'y a pas de travail de la détection d'un capteur frauduleux
TEST(SensorManagementTest, DetectionWithNoPrivateSensors)
{
	Model model;
	SensorManagement sm(&model);
	vector<pair<Sensor*, Confidence>>* frauds = sm.FraudulentSensorDetection();
	EXPECT_EQ(frauds->size(), 0);


}