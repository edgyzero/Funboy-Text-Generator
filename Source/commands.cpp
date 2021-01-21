#include "commands.h"

fb::CategoryMap categoryMap;
fb::CategoryFlagMap categoryFlags;
std::vector<fb::command> commands;

void fb::Setup()
{
	fb::LoadCommands(commands);
}

bool fb::Load()
{
	return storage::Load(categoryMap) && storage::Load(categoryFlags);
}

void fb::Save()
{
	storage::Save(categoryMap);
	storage::Save(categoryFlags);
}

std::vector<std::string>& GetCategoryItems(const std::string& categoryName)
{
	return categoryMap.at(categoryName);
}

bool CategoryExists(const std::string& s)
{
	return !(categoryMap.find(s) == categoryMap.end());
}

bool Help(const std::vector<std::string>& args)
{
	if (args.size() == 2)
	{
		fb::PrintCommandDetails(commands, fb::ToUpper(args[1]));
	}
	else fb::PrintCommands(commands);
	return true;
}

bool Add(const std::vector<std::string>& args)
{
	std::vector<std::string> newItems(args.begin() + 2, args.end());
	std::string category = fb::GetCategoryName(args[1]);
	fb::Category& items = categoryMap[category];

	if (fb::ContainsCategories(newItems)) categoryFlags[category] = true;
	else categoryFlags[category] = false;

	items.insert(items.end(), newItems.begin(), newItems.end());
	return true;
}

void RemoveDuplicates(fb::Category& category)
{
	typedef std::map<std::string, int> DuplicateMap;
	DuplicateMap duplicates;
	for (fb::Category::iterator i = category.begin(); i != category.end(); i++)
	{
		duplicates[fb::ToLower(*i)] += 1;
	}
	for (DuplicateMap::const_iterator i = duplicates.begin(); i != duplicates.end(); i++)
	{
		if (i->second > 1)
		{
			fb::Category::iterator f = fb::find_duplicate(category.begin(), category.end(), i->first);
			while (f != category.end())
			{
				category.erase(f);
				f = fb::find_duplicate(category.begin(), category.end(), i->first);
			}
			category.push_back(i->first);
		}
	}
}

bool Remove(const std::vector<std::string>& args)
{
	std::string category = fb::GetCategoryName(args[1]);
	if (!CategoryExists(category))
	{
		fb::PrintError("ERROR: Attempt to remove item from non existant category");
		return false;
	}
	else if (args.size() < 3)
	{
		categoryMap.erase(category);
		categoryFlags.erase(category);
	}
	else if (args.size() > 2)
	{
		fb::Category& items = GetCategoryItems(category);
		if (args[2] == "/d")
		{
			RemoveDuplicates(items);
		}
		else
		{
			std::vector<std::string> itemsToRemove(args.begin() + 2, args.end());
			for (std::vector<std::string>::size_type i = 0; i != itemsToRemove.size(); i++)
			{
				fb::Category::iterator j = std::find(items.begin(), items.end(), itemsToRemove[i]);
				while (j != items.end())
				{
					items.erase(j);
					j = std::find(items.begin(), items.end(), itemsToRemove[i]);
				}
			}
			if (fb::ContainsCategories(items)) categoryFlags[category] = true;
			else categoryFlags[category] = false;
		}		
	}
	return true;
}

bool RemoveAll()
{
	categoryMap.clear();
	categoryFlags.clear();
	return true;
}

bool List(const std::vector<std::string>& args)
{
	if (args.size() == 1)
	{
		fb::Print(categoryMap);
		return true;
	}
	else
	{
		for (std::vector<std::string>::size_type i = 1; i != args.size(); i++)
		{
			std::string category = fb::GetCategoryName(args[i]);
			if (CategoryExists(category))
			{
				std::vector<std::string> sortedCategory = GetCategoryItems(category);
				std::sort(sortedCategory.begin(), sortedCategory.end());
				fb::Print(category);
				fb::Print(sortedCategory, true);
			}
			else
			{
				fb::PrintError("ERROR: Attempt to list non existant category.");
				return false;
			}
		}	
		return true;
	}
}

void GenAuxilary(const std::string& in, std::vector<std::string>& out)
{
	std::string category = fb::ExtractCategoryName(in);
	if (category == "") out.push_back(in);
	else
	{
		if (CategoryExists(category))
		{
			fb::Category& items = GetCategoryItems(category);
			std::vector<std::string> sides = fb::ExtractSides(in);
			if (categoryFlags[category])
			{
				for (fb::Category::size_type i = 0; i != items.size(); i++)
				{
					GenAuxilary(items[i], out);
				}
			}
			else out.push_back(sides[0] + items[fb::Random(items.size())] + sides[1]);
		}
		else out.push_back(in);
	}
}

bool Generate(const std::vector<std::string>& args)
{
	int generationCount = 1;
	if (args.size() == 3)
	{
		try
		{
			generationCount = std::stoi(args[2]);
		}
		catch (std::exception& e)
		{
			fb::PrintError("Error: 3rd Argument must be a numerical value.");
			return false;
		}
	}

	std::string category = fb::GetCategoryName(args[1]);

	if (!CategoryExists(category))
	{
		fb::PrintError("ERROR: Attempt to generate non existant category.");
		return false;
	}
	else
	{
		for (int i = 0; i != generationCount; i++)
		{
			std::vector<std::string> output;
			GenAuxilary(category, output);
			fb::Print(output);
		}
		fb::NewLine();
		return true;
	}
}

bool ClearScreen()
{
	system("CLS");
	return true;
}

bool HasValidNumOfArgs(std::vector<std::string>::size_type vec_size, std::vector<std::string>::size_type min_size, const std::string& command)
{
	if (vec_size < min_size)
	{
		fb::PrintError("ERROR: " + command + " requires at least " + std::to_string(min_size) + " arguments.");
		return false;
	}
	else return true;
}

bool fb::ExecuteCommand(const std::vector<std::string>& args)
{
	bool success = false;
	if (args.size() < 1) return success;
	std::string command = args[0];
	command = fb::ToLower(command);
	if (command == "help" || command == "h")
	{
		success = Help(args);
	}
	else if (command == "add" || command == "a")
	{
		if (HasValidNumOfArgs(args.size(), 3, command))
		{
			success = Add(args);
			if (success) fb::Save();
		}
		else success = false;
	}
	else if (command == "remove" || command == "r")
	{
		if (HasValidNumOfArgs(args.size(), 2, command))
		{
			success = Remove(args);
			if (success) fb::Save();
		}
		else success = false;
	}
	else if (command == "remove*" || command == "r*")
	{
		success = RemoveAll();
		if (success) fb::Save();
	}
	else if (command == "list" || command == "l")
	{
		success = List(args);
	}
	else if (command == "generate" || command == "g")
	{
		if (HasValidNumOfArgs(args.size(), 2, command))
			success = Generate(args);
		else success = false;
	}
	else if (command == "clear" || command == "c")
	{
		success = ClearScreen();
	}
	else
	{
		success = false;
		fb::PrintError("ERROR: " + command + " is not a valid command.");
	}
	return success;
}