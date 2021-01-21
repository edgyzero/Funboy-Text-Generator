#include "parser.h"

typedef std::string::const_iterator s_iter;

bool IsSpace(const char& c)
{
	return isspace(c);
}

bool IsNotSpace(const char& c)
{
	return !isspace(c);
}

std::vector<std::string> fb::Split(const std::string& s)
{
	std::vector<std::string> splitString;
	s_iter b = s.begin();
	while (b != s.end())
	{
		b = std::find_if(b, s.end(), IsNotSpace);
		s_iter e = std::find_if(b, s.end(), IsSpace);
		if (b != e)
		{
			splitString.push_back(std::string(b, e));
		}
		b = e;
	}
	return splitString;
}