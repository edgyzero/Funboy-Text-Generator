#include "storage.h"

void storage::Save(const fb::CategoryMap& categoryMap)
{
	std::ofstream saveFile("categories.txt", std::ios::trunc);
	for (fb::CategoryMap::const_iterator i = categoryMap.begin(); i != categoryMap.end(); i++)
	{
		for (fb::Category::const_iterator j = i->second.begin(); j != i->second.end(); j++)
		{
			saveFile << i->first << ' ' << *j << std::endl;
		}
	}
}

void storage::Save(const fb::CategoryFlagMap& categoryFlags)
{
	std::ofstream saveFile("categoryFlags.txt", std::ios::trunc);
	for (fb::CategoryFlagMap::const_iterator i = categoryFlags.begin(); i != categoryFlags.end(); i++)
	{
		if (i->second) saveFile << i->first << " true" << std::endl;
		else saveFile << i->first << " false" << std::endl;
	}
}

bool storage::Load(fb::CategoryMap& categoryMap)
{
	std::ifstream saveFile("categories.txt");
	if (saveFile.is_open())
	{
		categoryMap.clear();
		std::string line;
		if (saveFile.peek() == std::ifstream::traits_type::eof())
		{
			return true;
		}
		while (std::getline(saveFile, line))
		{
			std::vector<std::string> data = fb::Split(line);
			if (data.size() != 2) return false;
			else categoryMap[data[0]].push_back(data[1]);
		}
	}
	return true;
}

bool storage::Load(fb::CategoryFlagMap& categoryFlags)
{
	std::ifstream saveFile("categoryFlags.txt");
	if (saveFile.is_open())
	{
		categoryFlags.clear();
		std::string line;
		if (saveFile.peek() == std::ifstream::traits_type::eof())
		{
			return true;
		}
		while (std::getline(saveFile, line))
		{
			std::vector<std::string> data = fb::Split(line);
			if (data.size() != 2) return false;
			else
			{
				if(data[1] == "true") categoryFlags[data[0]] = true;
				else categoryFlags[data[0]] = false;
			}
		}
	}
	return true;
}