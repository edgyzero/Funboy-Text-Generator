#include "command.h"

void fb::LoadCommands(std::vector<fb::command>& commands)
{
	fb::command help;
	fb::command add;
	fb::command remove;
	fb::command removeAll;
	fb::command list;
	fb::command generate;
	fb::command clear;
	help.name = { "HELP" };
	help.description = { "Lists information about the program." };
	help.arguments = { "[command]" };
	help.details = { "When a command is entered help will give extra details on that command." };
	add.name = { "ADD" };
	add.description = { "Adds specified items to specified category." };
	add.arguments = { "<category> [word]" };
	add.details = { "Requires both arguments to be entered." };
	remove.name = { "REMOVE" };
	remove.description = { "Removes specified categories or items from specified category." };
	remove.arguments = { "<category> [word] /d" };
	remove.details = { "Requires user to enter at least the category. /d will delete any duplicates of the word entered from the category leaving only one instance." };
	removeAll.name = { "REMOVE*" };
	removeAll.description = { "Removes all categories." };
	removeAll.arguments = { "There are no arguments for this command." };
	list.name = { "LIST" };
	list.description = { "Lists all categories or all items from a specified categories." };
	list.arguments = { "<category>" };
	list.details = { "Does not require any arguments; will list all cateogires if none are entered." };
	generate.name = { "GENERATE" };
	generate.description = { "Resolves categories into randomly selected items from those categories." };
	generate.arguments = { "<category> [amount] /g" };
	generate.details = { "Requires user to enter at least the category. /g will try to correct some common grammar mistakes." };
	clear.name = { "CLEAR" };
	clear.description = { "Clears the screen." };
	clear.arguments = { "There are no arguments for this command." };
	commands = { help, add, remove, removeAll, list, generate, clear };
}

std::vector<fb::command>::iterator fb::find_command(std::vector<fb::command>& commands, const std::string& name)
{
	std::vector<fb::command>::iterator b = commands.begin();
	while (b != commands.end())
	{
		if (b->name == name) return b;
		else b++;
	}
	return b;
}