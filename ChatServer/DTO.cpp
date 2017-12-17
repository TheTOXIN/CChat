#include "iostream"
#include "fstream"
#include "string"
#include "list"
#include "DTO.h"

using namespace std;

DTO::DTO()
{
	messagesPath = "dto/messages.txt";
	usersPath = "dto/users.txt";
	tokensPath = "dto/tokens.txt";
}

bool DTO::checkByNick(string user)
{
	ifstream file(usersPath);
	string str = "";

	while(getline(file, str)) 
	{
		string nick1 = user.substr(9, user.substr(9).find_first_of("|"));
		string nick2 = str.substr(9, str.substr(9).find_first_of("|"));

		if (nick1 == nick2)
		{
			file.close();
			return true;
		}
	}
	
	return false;
}

bool DTO::checkByToken(string token)
{
	list<string>::iterator u = users.begin();
	while (u != users.end())
	{
		if ((*u).substr(0, 8) == token)
			return false;
		u++;
	}

	ifstream file(tokensPath);
	string str = "";
	while(getline(file, str)) 
	{
		if (str == token)
		{
			file.close();
			return true;
		}
	}

	return false;
}

void DTO::saveNewUser(string token, string user)
{
	ofstream file1(tokensPath, ios::app);
	file1 << token << "\n";
	file1.close();

	ofstream file2(usersPath, ios::app);
	file2 << user << "\n";
	file2.close();
}

string DTO::getMessages(string message)
{
	string res = "";
	string str = "";
	ifstream file(messagesPath);
		
	while(getline(file, str)) 
	{
		if (str.length() > 8)
			if (str.substr(0, 8) == message)
				res += "|" + str.substr(8);
	}
	file.close();

	return res;
}

void DTO::setMessages(string message)
{
	ofstream file(messagesPath, ios::app);
	file << message << "\n";
	file.close();
}

void DTO::printAll()
{
	string str = "";

	cout << "=====MESSAGES=====" << endl;
	ifstream file1(messagesPath);
	while(getline(file1, str)) 
		cout << str << endl;

	cout << "=====USERS=====" << endl;
	ifstream file2(usersPath);
	while(getline(file2, str)) 
		cout << str << endl;
	
	cout << "=====TOKENS=====" << endl;
	ifstream file3(tokensPath);
	while(getline(file3, str)) 
		cout << str << endl;

	file1.close();
	file2.close();
	file3.close();
}