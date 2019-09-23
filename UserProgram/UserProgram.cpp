#include "stdafx.h"
#include <Windows.h>


int main(void)
{
	try
	{
		using smart_handle = std::unique_ptr<void,std::function<void(void*)>>;
		
		const std::wstring  path_driver = L"\\\\.\\FileDriverTestSymLink";

		std::wcout<<"Path - "<<path_driver<<std::endl;
		
		const auto handle_file = ::CreateFileW(path_driver.c_str(),
			GENERIC_ALL,
			0,
			nullptr,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_SYSTEM,
			nullptr
			);

		if (handle_file == INVALID_HANDLE_VALUE)
		{
			throw std::runtime_error("Fail open driver! Code - " + std::to_string(GetLastError()));
		}

		const smart_handle file_ptr(handle_file,[](void* handle)
		{
			if (handle == INVALID_HANDLE_VALUE)
				return;
			
			::CloseHandle(handle);
			
		});

		std::cout<<"SUCCESS! Type any key.";

		std::cin.get();


		
		char outBuffer[] = "This is a test string";
		DWORD outCount = sizeof(outBuffer);
		DWORD bW;

		if (!::WriteFile(file_ptr.get(),
			outBuffer,
			outCount,
			&bW,nullptr))
		{
			std::cout<<"Error write!"<<std::endl;
		}

		std::cin.get();
		std::cin>>bW;
		
		
	}
	catch (const std::exception & error)
	{
		std::cerr<<error.what()<<std::endl;
	}
	catch (...)
	{
	}
	std::cin.get();
   
}

