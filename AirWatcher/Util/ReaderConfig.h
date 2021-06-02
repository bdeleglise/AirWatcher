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

using namespace std;

struct Config
{
    //Redirection par rapport ou l'objet model est créé*
    //Récupération du chemin de la solution avec une macro préprocesseur
    string DATADIR = "../";
    string DATASETPATH = R"(Dataset\)";
    string DIRECTORYPATH = DATADIR + DATASETPATH;
    string SENSORFILE = "sensors.csv";
    string MEASUREMENTSFILE = "measurements.csv";
    string ATTRIBUTESFILE = "attributes.csv";
    string PROVIDERSFILE = "providers.csv";
    string CLEANERSFILE = "cleaners.csv";
    string USERSFILE = "users.csv";
};
#endif