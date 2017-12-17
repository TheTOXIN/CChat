#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>

#include "DTO.h"
#include "Logger.h"
#include "Utill.h"
#include "Connector.h"
#include "Menu.h"

using namespace std;

const string LOG = "LOG";
const string CON = "CON";
const string DIS = "DIS";
const string NEW = "NEW";
const string SND = "SND";
const string GET = "GET";
const string SET = "SET";
const string JON = "JON";
const string EXT = "EXT";
const string END = ";;;";

DTO dto;
Utill util;
Logger logger;
Menu menu(logger, dto);

SOCKET Connect;
SOCKET* Connections;
SOCKET Listen;

int clientsCount = 0;

void handlerGET(char* buffer, int ID)
{
	string message = Utill::parseToMessage(buffer);
	string res = "GET" + message; 
	logger.logEVENT(message);
	res += dto.getMessages(message);
	res += ";;;";
	const char *tmp = res.c_str();
	send(Connections[ID], tmp, strlen(tmp), NULL);
}

void handlerSET(char* buffer, int ID)
{
	string message = Utill::parseToMessage(buffer);
	logger.logEVENT(message);
	dto.setMessages(message);
}

void handlerSND(char* buffer, int ID)
{
	string message = Utill::parseToMessage(buffer);
	logger.logEVENT(message);
	for (int i = 0; i <= clientsCount; i++)
		if (Connections[i] != NULL)
			send(Connections[i], buffer, strlen(buffer), NULL);
}

void handlerEXT(char* buffer, int ID)
{
	string message = Utill::parseToMessage(buffer);
	logger.logEVENT(message);
	Connections[ID] = NULL;
	dto.users.remove(message);
}

void handlerJON(char* buffer, int ID)
{
	string message = Utill::parseToMessage(buffer);
	logger.logEVENT(message);

	for (auto it = dto.users.begin(); it != dto.users.end(); it++)
	{
		string user = JON + *it + END;
		const char *tmp = user.c_str();
		send(Connections[ID], tmp, strlen(tmp), NULL);
	}

	dto.users.push_back(message);
	
	for (int i = 0; i <= clientsCount; i++)
		if (Connections[i] != NULL)
			send(Connections[i], buffer, strlen(buffer), NULL);
}

void handlerNEW(char* buffer, int ID)
{
	char* answer = "";
	string message = Utill::parseToMessage(buffer);
	string token = message.substr(0, 8);
	logger.logEVENT(message);
					
	if (!dto.checkByNick(message) && !dto.checkByToken(token))
	{
		dto.saveNewUser(token, message);
		answer = "CON;;;";
	}
	else
	{
		answer = "DIS;;;";
	}

	send(Connections[ID], answer, strlen(answer), NULL);
}

void handlerLOG(char* buffer, int ID)
{
	char* answer = "";
	string message = Utill::parseToMessage(buffer);
	logger.logEVENT(message);

	if (dto.checkByToken(message))
		answer = "CON;;;";
	else
		answer = "DIS;;;";

	send(Connections[ID], answer, strlen(answer), NULL);
}

void crateConnect(string port)
{
	WSAData data;
	WORD version = MAKEWORD(2,2);

	int res = WSAStartup(version, &data);
	if (res != 0) return;

	struct addrinfo hints;
	struct addrinfo * result;

	Connections = (SOCKET*) calloc(64, sizeof(SOCKET));

	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	const char* tmp = port.c_str();
	getaddrinfo(NULL, tmp, &hints, &result);

	Listen = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	bind(Listen, result->ai_addr, result->ai_addrlen);
	listen(Listen, SOMAXCONN);

	freeaddrinfo(result);
}

void eventListener(int ID)
{
	while(true)
	{
		char* buffer = Utill::getClearBuffer();
		if (recv(Connections[ID], buffer, 1024, NULL))
		{	
			string message(buffer);
			string stat = message.substr(0, 3);

			logger.logSTAT(stat + "-> ");

			if (stat == SND)
			{
				handlerSND(buffer, ID);
			}
			else if (stat == GET)
			{
				handlerGET(buffer, ID);
			}
			else if (stat == SET)
			{
				handlerSET(buffer, ID);
			}
			else if (stat == EXT)
			{
				handlerEXT(buffer, ID);
				return;
			}
		}
		Sleep(100);
	}
}

void startServer()
{
	logger.setTime();
	logger.logINFO("-=SERVER START=-");

	while (true)
	{
		char* buffer = Utill::getClearBuffer();
		if (Connect = accept(Listen, NULL, NULL))
		{
			Connections[clientsCount] = Connect;
			clientsCount++;
			int ID = clientsCount - 1;
			
			logger.logINFO("Try connect # " + ID);

			if (recv(Connections[ID], buffer, 1024, NULL))
			{	
				string stat = Utill::parseToStat(buffer);
				logger.logSTAT(stat + "-> ");

				if (stat == LOG) 
				{
					handlerLOG(buffer, ID);
				}
				else if (stat == NEW)
				{
					handlerNEW(buffer, ID);
				}
				else if (stat == JON)
				{					
					handlerJON(buffer, ID);
					logger.logINFO("Run new Thread - #" + ID);
					CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)eventListener, (LPVOID)(ID), NULL, NULL);
				}
			}
		}
		Sleep(100);
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	while(!menu.isExit)
		menu.startMenu();

	crateConnect(menu.port);
	startServer();

	return 1;
}
