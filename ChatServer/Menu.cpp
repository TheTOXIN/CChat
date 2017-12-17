#include "iostream"
#include "string"
#include "Menu.h"
#include "Logger.h"
#include <conio.h>

using namespace std;

Menu::Menu(Logger &log, DTO &dto)
{
	this->log = log;
	this->dto = dto;

	choose = 0;
	isExit = false;
	port = "7770";

	initParams();
	showMenu();
}

void Menu::initParams()
{
	params[0] = "Launch server";
	params[1] = "Set port";
	params[2] = "Show IP confug";
	params[3] = "Print LOG";
	params[4] = "Off/On save LOG";
	params[5] = "Check DTO";
	params[6] = "About server";
	params[7] = "Exit";
	
	setCursor();
}

void Menu::showMenu()
{
	system("cls");
	cout << "______________________" << endl;
	for (int i = 0; i < count; i++)
		cout << params[i] << endl;
	cout << "______________________" << endl;
}

void Menu::startMenu()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 80: choose++; if (choose >= count) choose = count - 1; setCursor(); break;//DOWN
		case 72: choose--; if (choose < 0) choose = 0; setCursor(); break;//UP
		case 75: break;//LEFT
		case 77: break;//RIGHT
		case 13: processKey(); break;//ENTER
		}
		initParams();
		showMenu();
	}
}

void Menu::processKey()
{
	system("cls");

	switch(choose)
	{
	case 0: isExit = true; break;
	case 1: cout << "PORT = "; cin >> port; break;
	case 2: system("ipconfig"); break;
	case 3: log.printLog(); break;
	case 4: log.isSave = !log.isSave; cout << "Is Save = " << log.isSave; break;
	case 5: dto.printAll(); break;
	case 6: cout << "Chat_Server_ver-1.00 By TheTOXIN" << endl; break;
	case 7: exit(0); break;
	}

	system("pause");
}

void Menu::setCursor()
{
	params[choose] = "->" + params[choose];
}