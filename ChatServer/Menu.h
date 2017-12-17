#pragma once

#include "iostream"
#include "string"
#include "Logger.h"
#include "DTO.h"

using namespace std;

class Menu
{
public:
	Menu(Logger &log, DTO &dto);
	
	Logger log;
	DTO dto;

	string port;
	bool isExit;
	int choose;
	static const int count = 8;
	string params[count];
	
	void initParams();
	void showMenu();
	void startMenu();
	void setCursor();
	void processKey();
};