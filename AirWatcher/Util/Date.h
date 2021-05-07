/*************************************************************************
                           Date  -  description
                             -------------------
    dÃ©but                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Interface de la classe <Date> (fichier Date.h) ------

#pragma once
#if ! defined ( DATE_H )
#define DATE_H

struct Date
    //Contains all useful date elements
{
    int sec;
    int min;
    int hour;
    int day;
    int month;
    int year;


    Date()
    {

    }

    Date(int ayear, int amonth, int aday, int ahour, int amin, int asec)
    {
        year = ayear;
        month = amonth;
        day = aday;
        hour = ahour;
        min = amin;
        sec = asec;
    }

    Date& operator = (const Date& aDate)
        //Assignement operator overloading
    {
        sec = aDate.sec;
        min = aDate.min;
        hour = aDate.hour;
        day = aDate.day;
        month = aDate.month;
        year = aDate.year;
        return *this;
    }

    bool operator ==(const Date& aDate) const
        //Equals operator overloading
    {
        if (sec == aDate.sec && min == aDate.min && hour == aDate.hour && day == aDate.day && month == aDate.month && year == aDate.year)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator<(const Date& aDate) const
    {
        if (year < aDate.year)
        {
            return true;
        }
        else if (year == aDate.year)
        {
            if (month < aDate.month)
            {
                return true;
            }
            else if (month == aDate.month)
            {
                if (day < aDate.day)
                {
                    return true;
                }
                else if (day == aDate.day)
                {
                    if (hour < aDate.hour)
                    {
                        return true;
                    }
                    else if (hour == aDate.hour)
                    {
                        if (min < aDate.min)
                        {
                            return true;
                        }
                        else if (min == aDate.min)
                        {
                            if (sec < aDate.sec)
                            {
                                return true;
                            }
                            else
                            {
                                return false;
                            }
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }


};
#endif