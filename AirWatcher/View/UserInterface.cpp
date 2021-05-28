#include <iostream>
#include <string>
using namespace std;

#include "../AirWatcher.cpp"

class BaseMenu

{
public:
	BaseMenu() {
		m_MenuText = "Base menu - will no be shown but used with inheritance";
		//Constructeur d'un menu, chaque objet menu dispose de son propre texte
	}
	virtual ~BaseMenu() { } //Destructeur virtuel du menu pour eviter les fuites mémoires
	virtual BaseMenu* getNextMenu(int iChoice, bool& iIsQuitOptionSelected) = 0; //Méthode virtuelle pure pour l'héritage
	virtual void printText()
	{
		cout << m_MenuText << endl;
	}

protected:
	string m_MenuText;
};

class MenuUI : public BaseMenu
{
	MenuUI()
	{
		m_MenuText = "Bienvenue dans le logiciel AirWatcher \n"
			"Pour naviguer dans les menus du programme, entrez le chiffre correspondant à l'action que vous souhaitez réaliser. \n"
			"\n"
			"------------Menu principal-------------"
			"\n"
			"1 - Afficher des statistiques\n"
			"2 - Détecter les fraudes\n"
			;
	}

	BaseMenu* getNextMenu(int choice, bool& iIsQuitOptionSelected)
	//Définition de la méthode pure virtuelle au dessus.
	{
		BaseMenu* aNewMenu = 0;
		switch (choice)
		{
		case 1:
			aNewMenu = new StatsMenu;
		}
	}
};

class StatsMenu : public BaseMenu
{
	StatsMenu()
	{
		m_MenuText = "------------Affichage des statistiques-------------\n"
			"\n"
			"1 - Afficher la qualité d'air moyenne d'une zone \n"
			"2 - Afficher les zones avec la meilleure / pire qualité d'air \n"
			"3 - Sélectionner un capteur \n"
			"4 - Observer l'impact des AirCleaners \n"
			;
	}

}
