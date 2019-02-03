#include "Wascc.Console.Io/Console.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

string Console::write(string value)
{
	cout << value;
	return value;
}

string Console::writeLine(string value)
{
	cout << value << endl;
	return value;
}

int Console::readKey()
{
	return cin.get();
}

string Console::readLine()
{
	string result;
	std::getline(cin, result);
	return result;
}
