#include "comand_line_argument.h"
namespace ved
{

	std::wstringstream CommandLineArgument::get_command_lines_stream()
	{

		auto n_args{0};

		const auto psz_arglist = CommandLineToArgvW(::GetCommandLine(),
			&n_args);
		if (!psz_arglist)
			throw ved::c_win_api_exception(L"Error CommandLineToArgvW",
				GetLastError());

		std::vector<std::wstring> str;
		std::wstringstream ss;
		
		for (auto i{1}; i < n_args; i++)
			ss<<psz_arglist[i]<<L" ";
		
		::LocalFree(psz_arglist);

		return ss;
		
	}
}
