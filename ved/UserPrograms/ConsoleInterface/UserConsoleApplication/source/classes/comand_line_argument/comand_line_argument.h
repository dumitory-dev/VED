#pragma once
#include "../global_headers/pch.h"
#include "classes/exceptions/exception.h"

namespace ved
{
	class CommandLineArgument
	{
				
	public:
		CommandLineArgument(void) = delete;
		CommandLineArgument(const CommandLineArgument&) = delete;
		CommandLineArgument(CommandLineArgument&&) = delete;
		CommandLineArgument& operator = (const CommandLineArgument&) = delete;
		CommandLineArgument& operator = (CommandLineArgument&&) = delete;
		~CommandLineArgument(void) = delete;

		
		static std::wstringstream get_command_lines_stream(void);

	};
}
