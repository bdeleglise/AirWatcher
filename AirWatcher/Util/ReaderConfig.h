/*************************************************************************
                           ReaderConfig  -  description
                             -------------------
    début                : 06/05/2021
    copyright            : (C) 2021 par Belateche, Chaillan, Deleglise, Saugier
    e-mail               : rahim.belateche@insa-lyon, ewen.chaillan@insa-lyon.fr,
                           benoit.deleglise@insa-lyon.fr, mathieu.saugier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <ReaderConfig> (fichier ReaderConfig.h) ------

#if ! defined(READERCONFIG_H)
#define READERCONFIG_H

#include <string>

using namespace std;

//------------------------------------------------------------------------ 
// Role de la classe <ReaderConfig>
// Elle permet d'enregistrer les fichiers .csv dans des attributs de la structure config
//------------------------------------------------------------------------ 

struct Config
{
    //Redirection par rapport ou l'objet model est créé
    //Récupération du chemin de la solution avec une macro préprocesseur
    string SOLUTIONDIR = SOLUTION_DIR;
    string DATASETPATH = R"(Dataset\)";
    string DIRECTORYPATH = SOLUTIONDIR + DATASETPATH;
    string SENSORFILE = "sensors.csv";
    string MEASUREMENTSFILE = "measurements.csv";
    string ATTRIBUTESFILE = "attributes.csv";
    string PROVIDERSFILE = "providers.csv";
    string CLEANERSFILE = "cleaners.csv";
    string USERSFILE = "users.csv";
};
#endif