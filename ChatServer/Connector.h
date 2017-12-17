#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include "DTO.h"

using namespace std;

class Connector
{
public:
	Connector(DTO &dto);
	DTO dto;

	SOCKET Connect;
	SOCKET* Connections;
	SOCKET Listen;

	int clientsCount;

	void startServer();
	void crateConnect(string port);

	void handlerGET(char* buffer, int ID);
	void handlerSET(char* buffer, int ID);
	void handlerSND(char* buffer, int ID);
	void handlerEXT(char* buffer, int ID);
	void handlerNEW(char* buffer, int ID);
	void handlerLOG(char* buffer, int ID);
	void handlerJON(char* buffer, int ID);
};