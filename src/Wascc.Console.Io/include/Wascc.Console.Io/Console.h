#pragma once

#include "Wascc.Console.Io/Preprocessor.h"

#include <string>

using std::string;

class WASCC_CONSOLE_IO Console
{
public:
	static string write(string value);
	static string writeLine(string value);
	static int readKey();
};
