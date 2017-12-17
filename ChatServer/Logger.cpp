#include "Logger.h"
#include "iostream"
#include "string"
#include "fstream"

#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

Logger::Logger()
{
	pathLog = "LOG.txt";
	isSave = false;

	ofstream tmp(pathLog);
	tmp.close();
}

string Logger::getTime()
{
	SYSTEMTIME st;
	GetSystemTime(&st);

	string res = to_string(st.wHour) + ":" + to_string(st.wMinute);
	res += ":" + to_string(st.wSecond) + " | ";

	return res;
}

void Logger::setTime()
{
	SYSTEMTIME st;
	GetSystemTime(&st);

	ofstream file1(pathLog, ios::app);
	
	string res = to_string(st.wDay) + "." + to_string(st.wMonth);
	res += "." + to_string(st.wYear) + " | ";

	file1 << "========== " << res << " ==========" << endl;;
	file1.close();
}

void Logger::printLog()
{
	ifstream file(pathLog);
	string str = "";

	while(getline(file, str)) 
		cout << str << endl;	

	file.close();
}

void Logger::saveLog(string log)
{
	if (isSave)
	{
		ofstream file(pathLog, ios::app);
		file << log << endl;;
		file.close();
	}
}

void Logger::logINFO(string log)
{
	string info = getTime() + "INFO: " + log;
	cout << info << endl;
	saveLog(info);
}

void Logger::logERROR(string log)
{
	string error = getTime() + "ERROR: " + log;
	cout << error << endl;
	saveLog(error);
}

void Logger::logSTAT(string log)
{
	string stat = getTime() + "STAT: " + log;
	cout << stat << endl;
	saveLog(stat);
}

void Logger::logDTO(string log)
{
	string dto = getTime() + "DTO: " + log;
	cout << dto << endl;
	saveLog(dto);
}

void Logger::logEVENT(string log)
{
	string event = getTime() + "EVENT: " + log;
	cout << event << endl;
	saveLog(event);
}
