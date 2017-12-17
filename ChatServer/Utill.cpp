#include "Utill.h"
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

char* Utill::getClearBuffer()
{
	char* buffer = new char[1024];
	memset(buffer, 0, sizeof(buffer));
	for (int i = 0; i < 1024; i++) 
		buffer[i] = 0;

	return buffer;
}

string Utill::parseToStat(char* buffer)
{
	string stat(buffer);
	return stat.substr(0, 3);
}

string Utill::parseToMessage(char* buffer)
{
	string message(buffer);
	return message.substr(3, message.find(";;;") - 3);
}