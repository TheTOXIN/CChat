#pragma once

#include "iostream"
#include "string"
#include "list"

using namespace std;

class DTO
{
public:
	DTO();

	list<string> users;

	string messagesPath;
	string usersPath;
	string tokensPath;

	bool checkByNick(string user);
	bool checkByToken(string token);
	string getMessages(string message);
	void setMessages(string message);
	void saveNewUser(string token, string user);
	void printAll();
};