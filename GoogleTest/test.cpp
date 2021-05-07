#include "pch.h"
#include "../AirWatcher/Model/Entity/GovernmentAgency.h"
#include "../AirWatcher/Util/Date.h"
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