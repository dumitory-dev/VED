#include "stdafx.h"
#define USERMODE
#include "classes/file/File.h"
#include <Windows.h>
#include <Shlobj.h>
#ifndef __T
#ifdef _NTDDK_
#define __T(x) L ## x
#else
#define __T(x) x
#endif
#endif
#ifndef _T
#define _T(x) __T(x)
#endif)
#define DEVICE_BASE_NAME	_T("\\FileDisk")
#define DEVICE_DIR_NAME		_T("\\Device")	DEVICE_BASE_NAME
#define DEVICE_NAME_PREFIX	DEVICE_DIR_NAME	DEVICE_BASE_NAME
typedef struct _OPEN_FILE_INFORMATION {
	LARGE_INTEGER	FileSize;
	UCHAR			DriveLetter;
	USHORT			FileNameLength;
	USHORT			PasswordLength;
	CHAR			Password[16];
	WCHAR			FileName[1];
}OPEN_FILE_INFORMATION, *POPEN_FILE_INFORMATION;

#define IOCTL_FILE_DISK_OPEN_FILE	CTL_CODE(FILE_DEVICE_DISK, 0x800, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_FILE_DISK_CLOSE_FILE	CTL_CODE(FILE_DEVICE_DISK, 0x801, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_FILE_ADD_DEVICE CTL_CODE(FILE_DEVICE_DISK, 0x802, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_GET_FREE_DEVICE CTL_CODE(FILE_DEVICE_DISK, 0x803, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)


POPEN_FILE_INFORMATION create_file_info(const std::wstring & file_name, size_t file_size, char drive_letter, const std::string & file_password )
{
	if (file_name.empty() 
		||
		!file_size
		||
		file_password.length() != 16
		)
	{
		throw std::invalid_argument("Failed create_file_info! Invalid arguments!");
	}
	
	POPEN_FILE_INFORMATION file_info{};
	file_info = static_cast<POPEN_FILE_INFORMATION>(malloc(sizeof(OPEN_FILE_INFORMATION) + file_name.length() * sizeof(WCHAR) + 7));
	memset(
            file_info,
            0,
            sizeof(OPEN_FILE_INFORMATION) + file_name.length() * sizeof(WCHAR) + 7
            );

	wcscpy(file_info->FileName, L"\\??\\");
    wcscat(file_info->FileName, file_name.c_str());
	
	file_info->FileNameLength = static_cast<USHORT>(wcslen(file_info->FileName));
	file_info->FileSize.QuadPart = file_size * 1024 * 1024;
	file_info->DriveLetter = drive_letter;
	
	std::copy(file_password.cbegin(),file_password.cend(),file_info->Password);
	file_info->PasswordLength = file_password.length();

	return file_info;
	
}


int mount(POPEN_FILE_INFORMATION open_file,size_t number_device)
{
	
	char    		VolumeName[] = R"(\\.\ :)";
    char    		DriveName[] = " :\\";
    char    		DeviceName[255];
	DWORD			BytesReturned;
	//filedisk /mount  1 c:\\tmp\\cdimage.iso /cd i:\n
		
	
	VolumeName[4] = open_file->DriveLetter;
	DriveName[0] = open_file->DriveLetter;

	 HANDLE Device = CreateFileA(
		 VolumeName,
		 GENERIC_READ | GENERIC_WRITE,
		 FILE_SHARE_READ | FILE_SHARE_WRITE,
		 NULL,
		 OPEN_EXISTING,
		 FILE_FLAG_NO_BUFFERING,
		 NULL
	 );
	if (Device != INVALID_HANDLE_VALUE)
    {
        CloseHandle(Device);
        SetLastError(ERROR_BUSY);
       // PrintLastError(&VolumeName[4]);
        return -1;
    }
	
	sprintf_s(DeviceName, DEVICE_DIR_NAME "%u", number_device);
	
	if (!DefineDosDeviceA(
        DDD_RAW_TARGET_PATH,
        &VolumeName[4],
        DeviceName
        ))
    {
       // PrintLastError(&VolumeName[4]);
        return -1;
    }

	 Device = CreateFileA(
        VolumeName,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_NO_BUFFERING,
        NULL
        );
	 
	
    if (Device == INVALID_HANDLE_VALUE)
    {
		std::cout<<GetLastError()<<"Error create file!\n";
    	std::wcout<<DeviceName<<std::endl;
        DefineDosDeviceA(DDD_REMOVE_DEFINITION, &VolumeName[4], NULL);
        return -1;
    }
	std::cout<<"Ok!";

	if (!DeviceIoControl(
			Device,
			IOCTL_FILE_DISK_OPEN_FILE,
			open_file,
			sizeof(OPEN_FILE_INFORMATION) + (open_file->FileNameLength * sizeof(WCHAR)) - sizeof(WCHAR),
			NULL,
			0,
			&BytesReturned,
			NULL
			))
		{
			//PrintLastError("FileDisk:");
			DefineDosDeviceA(DDD_REMOVE_DEFINITION, &VolumeName[4], NULL);
			CloseHandle(Device);
		    std::cout<<GetLastError()<<std::endl;
			return -1;
		}
	std::cout<<"Ok!";
	CloseHandle(Device);

    SHChangeNotify(SHCNE_DRIVEADD, SHCNF_PATH, DriveName, NULL);
	std::cout<<"Ok!";

	return 0;
}


void AddDevice()
{
	    ved::file::settings settings{};

		settings.dw_creation_disposition = OPEN_EXISTING;
		settings.dw_desired_access =  GENERIC_READ | GENERIC_WRITE;
		settings.dw_flags_and_attributes = FILE_FLAG_NO_BUFFERING;
		settings.ws_file_name = L"\\\\.\\TestLink";
		
		const auto ptr = ved::file::create(settings);
		std::cout<<"Ok - device open\nSend ioctl code...\n"<<std::endl;

		DWORD ret = 0;
		auto res = DeviceIoControl(
        ptr->operator void*(), // Handle драйвера из функции CreateFile
         IOCTL_FILE_ADD_DEVICE, // Комманда
        (LPVOID)0,
        (DWORD)0,
        (LPVOID)NULL,
        (DWORD)0,
        (LPDWORD)&ret,
        NULL
        );

		if (res)
		{
			std::cout<<"Ok! Number device - "<<ret<<std::endl;
		}
		
}


int main(void)
{
	try
	{
		size_t choose = 0;
		std::cin>>choose;

		if (choose)
		{
			std::cin.ignore();
		std::cin.clear();
		
		std::cout<<"Type file name:"<<std::endl;
		    
		std::wstring file_name;
		std::getline(std::wcin,file_name);
		std::wcout<<file_name<<std::endl;
		std::cout<<"Type file password:"<<std::endl;
		std::string password(16,'0');
		std::getline(std::cin,password);
		password.resize(16,'0');
		size_t file_size = 0;
		std::cout<<"Type file size:"<<std::endl;
		std::cin>>file_size;
		char drive_letter;
		std::cout<<"Type driver letter:"<<std::endl;
		std::cin>>drive_letter;
		size_t number = 0;
		std::cout<<"Type number_device:"<<std::endl;
		std::cin>>number;
		
		
		
		mount(
			create_file_info(file_name,file_size,drive_letter,password),
			number
		);
		
		}
		else
		{
			AddDevice();
		}
		//std::cout<<std::endl;
		//const std::string buffer = "Test";
		//const std::vector<BYTE> buffer_bytes(buffer.cbegin(), buffer.cend());
		
		//ved::file::settings settings{};

		//settings.dw_creation_disposition = OPEN_EXISTING;
		//settings.dw_desired_access =  GENERIC_READ | GENERIC_WRITE;
		//settings.dw_flags_and_attributes = FILE_FLAG_NO_BUFFERING;
		//settings.ws_file_name = L"\\\\.\\TestLink";
		//
		//const auto ptr = ved::file::create(settings);
		//std::cout<<"Ok - device open\nSend ioctl code...\n"<<std::endl;

		//DWORD ret = 0;
		//auto res = DeviceIoControl(
  //      ptr->operator void*(), // Handle драйвера из функции CreateFile
  //       IOCTL_FILE_ADD_DEVICE, // Комманда
  //      (LPVOID)0,
  //      (DWORD)0,
  //      (LPVOID)NULL,
  //      (DWORD)0,
  //      (LPDWORD)&ret,
  //      NULL
  //      );

		//if (res)
		//{
		//	std::cout<<"Ok! Number device - "<<ret<<std::endl;
		//}
		//
		//ptr->write(buffer_bytes);

		//mount();
		
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
	std::cin.ignore();
	std::cin.clear();
	std::cin.get();
   
}

