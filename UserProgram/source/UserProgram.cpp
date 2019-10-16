#include "stdafx.h"
#define USERMODE
#include "classes/file/File.h"
#include <Windows.h>
#include "classes/install_manager/install_manager.h"
#include <Shlobj.h>

#define DEVICE_BASE_NAME	"\\FileDisk"
#define DEVICE_DIR_NAME		"\\Device"	DEVICE_BASE_NAME
#define DEVICE_NAME_PREFIX	DEVICE_DIR_NAME	DEVICE_BASE_NAME

typedef struct _OPEN_FILE_INFORMATION {
	LARGE_INTEGER	FileSize;
	UCHAR			DriveLetter;
	USHORT			FileNameLength;
	USHORT			PasswordLength;
	CHAR			Password[16];
	WCHAR			FileName[1];
}OPEN_FILE_INFORMATION, * POPEN_FILE_INFORMATION;

#define IOCTL_FILE_DISK_OPEN_FILE	CTL_CODE(FILE_DEVICE_DISK, 0x800, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_FILE_DISK_CLOSE_FILE	CTL_CODE(FILE_DEVICE_DISK, 0x801, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_FILE_ADD_DEVICE CTL_CODE(FILE_DEVICE_DISK, 0x802, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_GET_FREE_DEVICE CTL_CODE(FILE_DEVICE_DISK, 0x803, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)


POPEN_FILE_INFORMATION create_file_info(const std::wstring& file_name, size_t file_size, char drive_letter, const std::string& file_password)
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

	std::copy(file_password.cbegin(), file_password.cend(), file_info->Password);
	file_info->PasswordLength = file_password.length();

	return file_info;

}


int mount(POPEN_FILE_INFORMATION open_file, size_t number_device)
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
		std::wcout << GetLastError() << "Error create file!\n";
		std::wcout << DeviceName << std::endl;
		DefineDosDeviceA(DDD_REMOVE_DEFINITION, &VolumeName[4], NULL);
		return -1;
	}
	std::wcout << "Ok!";

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
		std::wcout << GetLastError() << std::endl;
		return -1;
	}
	std::wcout << "Ok!";
	CloseHandle(Device);

	SHChangeNotify(SHCNE_DRIVEADD, SHCNF_PATH, DriveName, NULL);
	std::wcout << "Ok!";

	return 0;
}


void AddDevice()
{
	ved::file::settings settings{};

	settings.dw_creation_disposition = OPEN_EXISTING;
	settings.dw_desired_access = GENERIC_READ | GENERIC_WRITE;
	settings.dw_flags_and_attributes = FILE_FLAG_NO_BUFFERING;
	settings.ws_file_name = L"\\\\.\\TestLink";

	const auto ptr = ved::file::create(settings);
	std::wcout << "Ok - device open\nSend ioctl code...\n" << std::endl;

	DWORD ret = 0;
	auto res = DeviceIoControl(
		ptr->operator void* (), // Handle драйвера из функции CreateFile
		IOCTL_FILE_ADD_DEVICE, // Комманда
		(LPVOID)0,
		(DWORD)0,
		(LPVOID)NULL,
		(DWORD)0,
		(LPDWORD)& ret,
		NULL
	);

	if (res)
	{
		std::wcout << "Ok! Number device - " << ret << std::endl;
	}

}

void mount_disk(void)
{
	std::wcin.ignore();
	std::wcin.clear();
	
	std::wcout << "Type file name:" << std::endl;

	std::wstring file_name;
	std::wcin>>file_name;
	std::wcout << file_name << std::endl;
	std::wcout << "Type file password:" << std::endl;
	std::string password(16, '0');
	std::cin>>password;
	password.resize(16, '0');
	size_t file_size = 0;
	std::wcout << "Type file size:" << std::endl;
	std::wcin >> file_size;
	char drive_letter;
	std::wcout << "Type driver letter:" << std::endl;
	std::cin >> drive_letter;
	size_t number = 0;
	std::wcout << "Type number_device:" << std::endl;
	std::wcin >> number;



	mount(
		create_file_info(file_name, file_size, drive_letter, password),
		number
	);
}

void unmount(char DriveLetter)
{

	char    		VolumeName[] = R"(\\.\ :)";
	char    		DriveName[] = " :\\";
	char    		DeviceName[255];
	DWORD			BytesReturned;

	VolumeName[4] = DriveLetter;
    DriveName[0] = DriveLetter;

	HANDLE Device = CreateFileA(
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
        std::wcout<<"Error CreateFileA! GetLastError - "<<GetLastError();
    	return;
    }

	 //if (!DeviceIoControl(
  //      Device,
  //      FSCTL_LOCK_VOLUME,
  //      NULL,
  //      0,
  //      NULL,
  //      0,
  //      &BytesReturned,
  //      NULL
  //      ))
  //  {
  //      //PrintLastError(&VolumeName[4]);
	 //	 std::wcout<<"Error DeviceIoControl! GetLastError - "<<GetLastError();
  //       CloseHandle(Device);
  //       return;
  //  }

	if (!DeviceIoControl(
        Device,
        IOCTL_FILE_DISK_CLOSE_FILE,
        NULL,
        0,
        NULL,
        0,
        &BytesReturned,
        NULL
        ))
    {

		std::wcout<<"Error DeviceIoControl(IOCTL_FILE_DISK_CLOSE_FILE)! GetLastError - "<<GetLastError();
        CloseHandle(Device);
        return;
    }

	if (!DeviceIoControl(
        Device,
        FSCTL_DISMOUNT_VOLUME,
        NULL,
        0,
        NULL,
        0,
        &BytesReturned,
        NULL
        ))
    {

		std::wcout<<"Error DeviceIoControl(FSCTL_DISMOUNT_VOLUME)! GetLastError - "<<GetLastError();
        CloseHandle(Device);
        return;
    }
		
	
	CloseHandle(Device);

	 if (!DefineDosDeviceA(
        DDD_REMOVE_DEFINITION,
        &VolumeName[4],
        NULL
        ))
    {
          std::wcout<<"Error DeviceIoControl(DDD_REMOVE_DEFINITION)! GetLastError - "<<GetLastError();
        return;
    }

    SHChangeNotify(SHCNE_DRIVEREMOVED, SHCNF_PATH, DriveName, NULL);
	
}

void unmount_disk()
{
	char letter = 0;
	std::wcout<<"Type letter disk...\n";
	std::cin>>letter;
	unmount(letter);
}


void run_driver(void)
{
	const std::wstring device_name = L"TestMyDriver";
	const std::wstring path = L"%SystemRoot%\\System32\\Drivers\\MyDriver.sys";

	ved::install_manager::install_service(path,device_name);
	ved::install_manager::load_service(device_name);
		
}

void stop_driver(void)
{
	const std::wstring device_name = L"TestMyDriver";
	const std::wstring path = L"%SystemRoot%\\System32\\Drivers\\MyDriver.sys";

	ved::install_manager::uninstall_service(device_name);
	ved::install_manager::unload_service(device_name);
		
}

int wmain(void)
{
	try
	{
		SetConsoleCP(1251);
	    SetConsoleOutputCP(1251);
		setlocale(LC_ALL,"");
		 
		size_t choose = 0;
		std::wcout<<L"1. - Add device\n2. - Mount disk\n3. - Un mount disk\n4. - Install and run driver\n5. - Stop and delete driver";
		std::wcin >> choose;

		switch (choose)
		{
		case 1:
			AddDevice();
			break;
		case 2:
			mount_disk();
			break;
		case 3:
			unmount_disk();
			break;
		case 4:
			run_driver();
			break;
		case 5:
			stop_driver();
		break;
		default:
			throw std::invalid_argument("Invalid parameter!");
		}


		
		//std::wcout<<std::endl;
		//const std::string buffer = "Test";
		//const std::vector<BYTE> buffer_bytes(buffer.cbegin(), buffer.cend());

		//ved::file::settings settings{};

		//settings.dw_creation_disposition = OPEN_EXISTING;
		//settings.dw_desired_access =  GENERIC_READ | GENERIC_WRITE;
		//settings.dw_flags_and_attributes = FILE_FLAG_NO_BUFFERING;
		//settings.ws_file_name = L"\\\\.\\TestLink";
		//
		//const auto ptr = ved::file::create(settings);
		//std::wcout<<"Ok - device open\nSend ioctl code...\n"<<std::endl;

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
		//	std::wcout<<"Ok! Number device - "<<ret<<std::endl;
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

		//std::wcout<<"SUCCESS! Type any key.";

		//std::wcin.get();
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
		//	std::wcout<<"Error DeviceIoControl! "<<GetLastError()<<std::endl;
		//}
		//else
		//{
		//	std::wcout<<"OK!"<<ret_size<<std::endl;
		//}
		//
		//std::wcout<<"SUCCESS! Type any key.";

		//std::wcin.get();
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
		//	std::wcout<<"Error DeviceIoControl! "<<GetLastError()<<std::endl;
		//}
		//else
		//{
		//	//out_buff.resize(ret_size);
		//	std::wcout<<"OK! SIZE - "<<ret_size;
		//	std::wcout<<"MESSAGE - " <<szinBuff<<std::endl;
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
		//	std::wcout<<"Error write!"<<std::endl;
		//}

		//std::wcin.get();
		//std::wcin>>bW;*/
		//

	}
	catch (const ved::driver_exception & error)
	{
		std::wcout << error.GetMessageW() << std::endl;
	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	catch (...)
	{
	}
	std::wcin.ignore();
	std::wcin.clear();
	std::wcin.get();

}

