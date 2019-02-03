#pragma once

#include "Wascc.Io/Preprocessor.h"

#include <string>

using std::string;

class WASCC_IO Console
{
public:
	static string write(string value);
	static string writeLine(string value);
};
