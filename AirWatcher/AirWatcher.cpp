// AirWatcher.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
using namespace std;
#include "Model/Entity/GovernmentAgency.h"
#include "Model/Entity/Cleaner.h"
#include <ctime>
#include "Model/Entity/Attribute.h"
#include "Model/Entity/Measurement.h"
#include "Model/Entity/Provider.h"
#include "Model/Entity/IndividualUser.h"
#include "Model/Entity/Sensor.h"
#include "Util/ReaderConfig.h"
int main()
{
    std::cout << "Hello World!\n";
    GovernmentAgency a(6);
    cout << a.GetID() << endl;
    Date date1;
    date1.year = 1900;
    date1.month = 02;
    date1.day= 01;
    date1.hour = 12;

    Date date2;
    date2.year = 1900;
    date2.month = 03;
    date2.day = 01;
    date2.hour = 00;

    Config path;
    cout << path.DIRECTORYPATH << endl;

    Cleaner c(1, 2, 44.5, -52, date1, date2);
    cout << c.GetID() << " " << c.GetProviderID() << " " << c.GetLatitude() << " " << c.GetLongitude() << endl;
    Date res = c.GetStart();
    cout << res.hour << endl;
    


    Attribute att("O3", "µg/m3", "concentration d'ozone");
    cout << att.GetID() << " " << att.GetDescription() << " " << att.GetUnit() << endl;


    Measurement mesure(date1, 44.5, att);
    res = mesure.GetTime();
     cout << mesure.GetValue() << " " <<res.hour << mesure.GetAttribute().GetDescription() << endl;


    Provider pro(02);
    pro.AddCleaner(c);

    vector<Cleaner> testCleanerPro = pro.GetCleaners();
    for (vector < Cleaner >::iterator iv = testCleanerPro.begin(); iv != testCleanerPro.end(); ++iv)
    {
        cout << pro.GetID() << " " << iv->GetLatitude() << endl;
    }

    Sensor s(10, 25.6, -24);
    cout << s.GetID() << " " << s.GetLatitude() << " " << s.GetLongitude() << " " << s.GetState() << endl;

    IndividualUser privateuser();
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
