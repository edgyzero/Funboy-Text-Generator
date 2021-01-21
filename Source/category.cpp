#include "category.h"

bool fb::IsCategoryName(const std::string& s)
{
	if (s[0] == '<' && s[s.size() - 1] == '>') return true;
	else return false;
}

bool NoCaseStrCmp(std::string s1, std::string s2)
{
	return fb::ToLower(s1) == fb::ToLower(s2);
}

bool fb::ContainsCategories(const fb::Category& category)
{
	for (fb::Category::size_type i = 0; i != category.size(); i++)
	{
		std::string::const_iterator b = std::find(category[i].begin(), category[i].end(), '<');
		std::string::const_iterator e = std::find(category[i].begin(), category[i].end(), '>');
		if (b != category[i].end() && e != category[i].end())
		{
			return true;
		}
	}
	return false;
}

std::string fb::GetCategoryName(const std::string& s)
{
	if (s[0] == '<' && s[s.size() - 1] == '>') return s;
	else return std::string('<' + s + '>');
}

std::string fb::ExtractCategoryName(const std::string& s)
{
	typedef std::string::const_iterator iter;
	iter b = std::find(s.begin(), s.end(), '<');
	iter e = std::find(s.begin(), s.end(), '>');
	if (b == s.end() || e == s.end()) return std::string();
	else return std::string(b, e + 1);
}

std::vector<std::string> fb::ExtractSides(const std::string& s)
{
	std::vector<std::string> ret;
	typedef std::string::const_iterator iter;
	iter b = std::find(s.begin(), s.end(), '<');
	iter e = std::find(s.begin(), s.end(), '>');
	ret.push_back(std::string(s.begin(), b));
	ret.push_back(std::string(e + 1, s.end()));
	return ret;
}

std::string fb::ToLower(std::string s)
{
	for (std::string::size_type i = 0; i != s.size(); i++)
	{
		s[i] = tolower(s[i]);
	}
	return s;
}

std::string fb::ToUpper(std::string s)
{
	for (std::string::size_type i = 0; i != s.size(); i++)
	{
		s[i] = toupper(s[i]);
	}
	return s;
}

fb::Category::iterator fb::find_duplicate(fb::Category::iterator b, fb::Category::iterator e, std::string s)
{
	while (b != e)
	{
		if (NoCaseStrCmp(*b, s))
		{
			return b;
		}
		b++;
	}
	return e;
}