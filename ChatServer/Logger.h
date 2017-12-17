#pragma once

#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

class Logger
{
public:
	Logger();
	bool isSave;

	string pathLog;

	string getTime();
	void setTime();

	void printLog();
	void saveLog(string log);

	void logEVENT(string log);
	void logINFO(string log);
	void logERROR(string log);
	void logSTAT(string log);
	void logDTO(string log);
};