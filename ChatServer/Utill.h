#pragma once

#include <iostream>
#include <string>

using namespace std;

class Utill
{
public:
	static char* getClearBuffer();
	static string parseToStat(char* buffer);
	static string parseToMessage(char* buffer);
};