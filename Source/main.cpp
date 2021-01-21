#include "commands.h"
#include "parser.h"

int main()
{
	fb::Print("Loading...");
	fb::Setup();
	if (!fb::Load()) fb::PrintError("Load failed.");
	else fb::Print("Load successful.");
	fb::Print("Welcome to the funboy 2.0 generater type \"help\" for a list of commands or \"help [command]\" for more details.");
	std::string input;
	while (std::getline(std::cin, input))
	{
		fb::ExecuteCommand(fb::Split(input));
	}
	return 0;
}