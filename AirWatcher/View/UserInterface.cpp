#include <iostream>
#include <string>
using namespace std;

#include "../AirWatcher.cpp"


#include <iostream>
#include <string>
using namespace std;

#include "../AirWatcher.cpp"

int GetInput()
{
	int choice;
	cin >> choice;
	return choice;
}

void DisplayMainMenu()
{
	cout << "Bienvenue dans le logiciel AirWatcher \n"
		"Pour naviguer dans les menus du programme, entrez le chiffre correspondant � l'action que vous souhaitez r�aliser. \n"
		"\n"
		"------------Menu principal-------------"
		"\n"
		"1 - Afficher des statistiques\n"
		"2 - D�tecter les fraudes\n"
		<< endl;

}

void DisplayStatsMenu()
{
	cout <<
		"------------Affichage des statistiques-------------\n"
		"\n"
		"1 - Afficher la qualit� d'air moyenne d'une zone \n"
		"2 - Afficher les zones avec la meilleure / pire qualit� d'air \n"
		"3 - S�lectionner un capteur \n"
		"4 - Observer l'impact des AirCleaners \n"
		<< endl;
}


