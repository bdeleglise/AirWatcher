/*************************************************************************
                           ReaderConfig  -  description
                             -------------------
    d�but                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Interface de la classe <ReaderConfig> (fichier ReaderConfig.h) ------

#if ! defined(READERCONFIG_H)
#define READERCONFIG_H

#include <string>
#include <filesystem>
using namespace std;

struct Config
{


    string DIRECTORYPATH;
    string SENSORFILE;
    string MEASUREMENTSFILE;
    string ATTRIBUTESFILE;
    string PROVIDERSFILE;
    string CLEANERSFILE;
    string USERSFILE;

    Config()
    {
        DIRECTORYPATH = filesystem::current_path().string();
        SENSORFILE = "sensors.csv";
        MEASUREMENTSFILE = "measurements.csv";
        ATTRIBUTESFILE = "attributes.csv";
        PROVIDERSFILE = "providers.csv";
        CLEANERSFILE = "cleaners.csv";
        USERSFILE = "user.csv";
    }
};
#endif