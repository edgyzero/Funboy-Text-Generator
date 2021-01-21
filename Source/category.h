#pragma once
#include <map>
#include <string>
#include <vector>

namespace fb
{
	typedef std::vector<std::string> Category;
	typedef std::map<std::string, bool> CategoryFlagMap;
	typedef std::map<std::string, Category> CategoryMap;
	bool IsCategoryName(const std::string&);
	bool ContainsCategories(const fb::Category&);
	std::string GetCategoryName(const std::string&);
	std::string ExtractCategoryName(const std::string&);
	std::string ToLower(std::string);
	std::string ToUpper(std::string);
	std::vector<std::string> ExtractSides(const std::string&);
	Category::iterator find_duplicate(Category::iterator, Category::iterator, std::string);
}

