#pragma once
#include "category.h"
#include "parser.h"
#include "print.h"
#include <iostream>
#include <fstream>

namespace storage
{
	void Save(const fb::CategoryMap&);
	void Save(const fb::CategoryFlagMap&);
	bool Load(fb::CategoryMap&);
	bool Load(fb::CategoryFlagMap&);
}