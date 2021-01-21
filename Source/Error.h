#pragma once
#include <string>
#include "print.h"

namespace fb
{
	class Error
	{
	public:

		Error(std::string _message)
		{
			message = _message;
		}

		void Display()
		{
			fb::print_error(message);
		}

	private:
		std::string message;
	};
}
