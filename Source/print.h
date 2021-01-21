#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "category.h"
#include "command.h"

namespace fb
{
	void NewLine(const int& = 1);
	void Print(const char&);
	void Print(const std::string&);
	void Print(std::vector<std::string>&, const bool& = false);
	void Print(const fb::CategoryMap&);
	void PrintError(const std::string&);
	void PrintCommands(const std::vector<fb::command>&);
	void PrintCommandDetails(std::vector<fb::command>&, const std::string&);
}
