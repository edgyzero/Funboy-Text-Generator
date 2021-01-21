#include "print.h"

std::streamsize FindMaxWidth(const std::vector<std::string>& vs)
{
	std::streamsize maxWidth = 0;
	for (std::vector<std::string>::size_type i = 0; i != vs.size(); i++)
	{
		if (vs[i].size() > maxWidth)
		{
			maxWidth = vs[i].size();
		}
	}
	return maxWidth;
}

void fb::NewLine(const int& lineCount)
{
	for (int i = 0; i != lineCount; i++)
	{
		std::cout << std::endl;
	}
}

void fb::Print(const char& c)
{
	std::cout << c << std::endl;
}

void fb::Print(const std::string& s)
{
	std::cout << s << std::endl;
}

void fb::Print(std::vector<std::string>& vs, const bool& byLine)
{
	if (byLine)
	{
		for (std::vector<std::string>::size_type i = 0; i != vs.size(); i++)
		{
			std::cout << vs[i] << std::endl;
		}
	}
	else
	{
		fb::NewLine();
		for (std::vector<std::string>::size_type i = 0; i != vs.size(); i++)
		{
			std::string::iterator underscore = std::find(vs[i].begin(), vs[i].end(), '_');
			while (underscore != vs[i].end())
			{
				*underscore = ' ';
				underscore = std::find(vs[i].begin(), vs[i].end(), '_');
			}
			std::cout << vs[i] << ' ';
		}
		fb::NewLine();
	}	
}

void fb::Print(const fb::CategoryMap& categoryMap)
{
	for (fb::CategoryMap::const_iterator i = categoryMap.begin(); i != categoryMap.end(); i++)
	{
		fb::Print(i->first);
	}
}

void fb::PrintError(const std::string& s)
{
	std::cerr << s << std::endl;
}

void PrintTwoColumns(const std::vector<std::string>& vs1, const std::vector<std::string>& vs2, const std::streamsize& pad = 0)
{
	std::streamsize vs1maxWidth = FindMaxWidth(vs1);
	std::streamsize vs2maxWidth = FindMaxWidth(vs2);
	for (std::vector<std::string>::size_type i = 0; i != vs1.size(); i++)
	{
		std::cout << std::left << std::setw(vs1maxWidth + pad) << vs1[i] << std::setw(vs2maxWidth) << vs2[i] << std::endl;
	}
}

void fb::PrintCommands(const std::vector<fb::command>& commands)
{
	std::streamsize leftWidth = 0;
	std::streamsize rightWidth = 0;
	for (std::vector<fb::command>::size_type i = 0; i != commands.size(); i++)
	{
		if (leftWidth < commands[i].name.size())
			leftWidth = commands[i].name.size();
		if (rightWidth < commands[i].description.size())
			rightWidth = commands[i].description.size();
	}
	for (std::vector<fb::command>::size_type i = 0; i != commands.size(); i++)
	{
		std::cout << std::left << std::setw(leftWidth + 5) << commands[i].name << std::left << commands[i].description << std::endl;
	}
}

void fb::PrintCommandDetails(std::vector<fb::command>& commands, const std::string& name)
{
	std::vector<fb::command>::iterator it = fb::find_command(commands, name);
	fb::command _command;
	if (it == commands.end()) return;
	else _command = *it;
	std::streamsize leftWidth = _command.name.size();
	std::streamsize rightWidth = _command.arguments.size();
	std::cout << std::left << std::setw(leftWidth + 5) << _command.name << std::left << _command.arguments << std::endl;
	if (_command.details.size() != 0) std::cout << _command.details << std::endl;
}
