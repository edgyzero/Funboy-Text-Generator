#pragma once
#include <string>
#include <vector>

namespace fb
{
	struct command
	{
		std::string name;
		std::string description;
		std::string details;
		std::string arguments;
	};
	void LoadCommands(std::vector<fb::command>&);
	std::vector<fb::command>::iterator find_command(std::vector<fb::command>&, const std::string&);
}
