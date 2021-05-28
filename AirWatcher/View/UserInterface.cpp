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
	virtual ~BaseMenu() { } //Destructeur virtuel du menu pour eviter les fuites m�moires
	virtual BaseMenu* getNextMenu(int iChoice, bool& iIsQuitOptionSelected) = 0; //M�thode virtuelle pure pour l'h�ritage
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
			"Pour naviguer dans les menus du programme, entrez le chiffre correspondant � l'action que vous souhaitez r�aliser. \n"
			"\n"
			"------------Menu principal-------------"
			"\n"
			"1 - Afficher des statistiques\n"
			"2 - D�tecter les fraudes\n"
			;
	}

	BaseMenu* getNextMenu(int choice, bool& iIsQuitOptionSelected)
	//D�finition de la m�thode pure virtuelle au dessus.
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
			"1 - Afficher la qualit� d'air moyenne d'une zone \n"
			"2 - Afficher les zones avec la meilleure / pire qualit� d'air \n"
			"3 - S�lectionner un capteur \n"
			"4 - Observer l'impact des AirCleaners \n"
			;
	}

}
