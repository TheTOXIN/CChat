#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include "DTO.h"
#include "Connector.h"
#include "Utill.h"

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

Connector::Connector(DTO &dto)
{
	this->dto = dto;
	clientsCount = 0;
}

void Connector::handlerGET(char* buffer, int ID)
{
	string message = Utill::parseToMessage(buffer);
	string res = "GET" + message; 
	res += dto.getMessages(message);
	res += ";;;";
	const char *tmp = res.c_str();
	send(Connections[ID], tmp, strlen(tmp), NULL);
}

void Connector::handlerSET(char* buffer, int ID)
{
	string message = Utill::parseToMessage(buffer);
	dto.setMessages(message);
}

void Connector::handlerSND(char* buffer, int ID)
{
	for (int i = 0; i <= clientsCount; i++)
	{
		send(Connections[i], buffer, strlen(buffer), NULL);
	}
}

void Connector::handlerEXT(char* buffer, int ID)
{
	string message = Utill::parseToMessage(buffer);
	dto.users.remove(message);
}

void Connector::handlerJON(char* buffer, int ID)
{
	string message = Utill::parseToMessage(buffer);

	for (auto it = dto.users.begin(); it != dto.users.end(); it++)
	{
		string user = "JON" + *it + ";;;";
		const char *tmp = user.c_str();
		send(Connections[ID], tmp, strlen(tmp), NULL);
	}

	dto.users.push_back(message);
	
	for (int i = 0; i <= clientsCount; i++)
	{
		send(Connections[i], buffer, strlen(buffer), NULL);
	}
}

void Connector::handlerNEW(char* buffer, int ID)
{
	char* answer = "";
	string message = Utill::parseToMessage(buffer);
	string token = message.substr(0, 8);
					
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

void Connector::handlerLOG(char* buffer, int ID)
{
	char* answer = "";
	string message = Utill::parseToMessage(buffer);

	if (dto.checkByToken(message))
		answer = "CON;;;";
	else
		answer = "DIS;;;";

	send(Connections[ID], answer, strlen(answer), NULL);
}

void Connector::crateConnect(string port)
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

void eventListener(int ID, Connector con)
{
	while(true)
	{
		char* buffer = Utill::getClearBuffer();
		memset(buffer, 0, sizeof(buffer));

		if (recv(con.Connections[ID], buffer, 1024, NULL))
		{	
			string message(buffer);
			string stat = message.substr(0, 3);

			if (stat == SND)
				con.handlerSND(buffer, ID);
			else if (stat == GET)
				con.handlerGET(buffer, ID);
			else if (stat == SET)
				con.handlerSET(buffer, ID);
			else if (stat == EXT)
				con.handlerEXT(buffer, ID);
		}
		Sleep(100);
	}
}

void Connector::startServer()
{
	while (true)
	{
		char* buffer = Utill::getClearBuffer();
		if (Connect = accept(Listen, NULL, NULL))
		{
			Connections[clientsCount] = Connect;
			clientsCount++;
			int ID = clientsCount - 1;

			if (recv(Connections[ID], buffer, 1024, NULL))
			{	
				string stat = Utill::parseToStat(buffer);

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
					CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)eventListener, (LPVOID)(ID, this), NULL, NULL);
				}
			}
		}
		Sleep(100);
	}
}