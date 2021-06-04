
#pragma once
/*************************************************************************
                           AirWatcher  -  description
                             -------------------
    debut                : 04-2021
    copyright            : (C) 2021 par 3IF-3206 & 3213
*************************************************************************/

// AirWatcher.cpp : Ce fichier contient la fonction 'main'. L'execution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;
#include "Model/Entity/GovernmentAgency.h"
#include "Model/Entity/Cleaner.h"
#include "Model/Entity/Attribute.h"
#include "Model/Entity/Measurement.h"
#include "Model/Entity/Provider.h"
#include "Model/Entity/IndividualUser.h"
#include "Model/Entity/Sensor.h"
#include "Model/Model.h"
#include "Util/ReaderConfig.h"
#include "Controller/System.h"
#include "Controller/Statistics.h"
#include "View/UserInterface.h"



int main()
{
    //Permet l'affichage des accents dans la console.
    SetConsoleOutputCP(CP_UTF8);
    cout << "Initialisation de l'application ...\n";
    Model model;
    int res = model.LoadData();
    switch (res)
    {
    case 1:
        cout << "Un fichier n'existe pas" << endl;
        break;
    case 2:
        cout << "Les donnees ne sont pas coherentes" << endl;
        break;
    case 3:
        cout << "Les donnees ont dejà ete chargees" << endl;
    case 0:
    {
        UserInterface ui(&model);
        ui.MenuUI();
        break;
    }
    default:
        exit(1);
    }
    return 0;
}

// Executer le programme : Ctrl+F5 ou menu Deboguer > Executer sans debogage
// Deboguer le programme : F5 ou menu Deboguer > Demarrer le debogage

// Astuces pour bien demarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gerer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la generation et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accedez à Projet > Ajouter un nouvel element pour creer des fichiers de code, ou à Projet > Ajouter un element existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accedez à Fichier > Ouvrir > Projet et selectionnez le fichier .sln.
