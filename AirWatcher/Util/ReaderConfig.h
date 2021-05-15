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
    //Redirection par rapport ou l'objet model est créé
    string DIRECTORYPATH = "./Dataset/";
    string SENSORFILE = "sensors.csv";
    string MEASUREMENTSFILE = "measurements.csv";
    string ATTRIBUTESFILE = "attributes.csv";
    string PROVIDERSFILE = "providers.csv";
    string CLEANERSFILE = "cleaners.csv";
    string USERSFILE = "users.csv";
};
#endif