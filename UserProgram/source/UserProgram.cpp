#include "stdafx.h"
#include "classes/file/File.h"
#include <Windows.h>

#define DEVICE_REC CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,METHOD_BUFFERED,FILE_READ_DATA)

#define DEVICE_SEND CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_WRITE_DATA)
int main(void)
{
	try
	{
		const std::string buffer = "Test";
		const std::vector<BYTE> buffer_bytes(buffer.cbegin(), buffer.cend());
		ved::file::settings settings{};
		settings.dw_desired_access =  FILE_GENERIC_WRITE;
		settings.ws_file_name = L"test.txt";
		
		const auto ptr = ved::file::create(settings);
		ptr->write(buffer_bytes);
		
		//using smart_handle = std::unique_ptr<void,std::function<void(void*)>>;
		//
		//const std::wstring  path_driver = L"\\\\.\\FileDriverTestSymLink";

		//std::wcout<<"Path - "<<path_driver<<std::endl;
		//
		//const auto handle_file = ::CreateFileW(path_driver.c_str(),
		//	GENERIC_ALL,
		//	0,
		//	nullptr,
		//	OPEN_EXISTING,
		//	FILE_ATTRIBUTE_SYSTEM,
		//	nullptr
		//	);

		//if (handle_file == INVALID_HANDLE_VALUE)
		//{
		//	throw std::runtime_error("Fail open driver! Code - " + std::to_string(GetLastError()));
		//}

		//const smart_handle file_ptr(handle_file,[](void* handle)
		//{
		//	if (handle == INVALID_HANDLE_VALUE)
		//		return;
		//	
		//	::CloseHandle(handle);
		//	
		//});

		//std::cout<<"SUCCESS! Type any key.";

		//std::cin.get();
		//
		//std::wstring str = L"Hello!";
		//DWORD ret_size{};

		//if (!DeviceIoControl(
		//	file_ptr.get(),
		//	DEVICE_SEND,
		//	reinterpret_cast<LPVOID>(str.data()),
		//	str.size() * sizeof(wchar_t) + 1,
		//	nullptr,
		//	0,
		//	&ret_size,
		//	nullptr
		//	))
		//{
		//	std::cout<<"Error DeviceIoControl! "<<GetLastError()<<std::endl;
		//}
		//else
		//{
		//	std::cout<<"OK!"<<ret_size<<std::endl;
		//}
		//
		//std::cout<<"SUCCESS! Type any key.";

		//std::cin.get();
		//
		//char szinBuff[80]; ZeroMemory(&szinBuff,sizeof(szinBuff));
		//		
		//
		//if (!DeviceIoControl(
		//	file_ptr.get(),
		//	DEVICE_REC,
		//	nullptr,
		//	0,
		//	&szinBuff,
		//	sizeof(szinBuff),
		//	&ret_size,
		//	nullptr
		//	))
		//{
		//	std::cout<<"Error DeviceIoControl! "<<GetLastError()<<std::endl;
		//}
		//else
		//{
		//	//out_buff.resize(ret_size);
		//	std::cout<<"OK! SIZE - "<<ret_size;
		//	std::cout<<"MESSAGE - " <<szinBuff<<std::endl;
		//}
		//
		///*char outBuffer[] = "This is a test string";
		//DWORD outCount = sizeof(outBuffer);
		//DWORD bW;

		//if (!::WriteFile(file_ptr.get(),
		//	outBuffer,
		//	outCount,
		//	&bW,nullptr))
		//{
		//	std::cout<<"Error write!"<<std::endl;
		//}

		//std::cin.get();
		//std::cin>>bW;*/
		//
		
	}
	catch (const ved::c_win_api_exception & error)
	{
		std::wcout<<error.GetMessageW()<<std::endl;
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

