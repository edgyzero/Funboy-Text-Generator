#pragma once
#include <algorithm>
#include "print.h"
#include "storage.h"
#include "random.h"
#include "command.h"

namespace fb
{
	bool ExecuteCommand(const std::vector<std::string>&);
	bool Load();
	void Save();
	void Setup();
}

