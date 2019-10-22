#include "stdafx.h"

#define USERMODE
#include "classes/file/File.h"
#include <Windows.h>
#include "classes/install_manager/install_manager.h"
#include <Shlobj.h>
#include "classes/driver_disk/driver_disk.h"

#define DEVICE_BASE_NAME	L"\\FileDisk"
#define DEVICE_DIR_NAME		L"\\Device"	DEVICE_BASE_NAME
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


ved::driver_disk::POPEN_FILE_INFORMATION create_file_info(const std::wstring& file_name, size_t file_size, char drive_letter, const std::string& file_password)
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
	DWORD code = CTL_CODE(FILE_DEVICE_DISK, 0x800, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS);
	ved::driver_disk::POPEN_FILE_INFORMATION file_info{};
	file_info = static_cast<ved::driver_disk::POPEN_FILE_INFORMATION>(malloc(sizeof(OPEN_FILE_INFORMATION) + file_name.length() * sizeof(WCHAR) + 7));
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
	file_info->PasswordLength = static_cast<USHORT>(file_password.length());

	return file_info;

}


int mount(ved::driver_disk::POPEN_FILE_INFORMATION open_file, size_t number_device)
{

	wchar_t    		VolumeName[] = LR"(\\.\ :)";
	wchar_t    		DriveName[] = L" :\\";
	wchar_t    		DeviceName[255];
	DWORD			BytesReturned;
	//filedisk /mount  1 c:\\tmp\\cdimage.iso /cd i:\n


	VolumeName[4] = open_file->DriveLetter;
	DriveName[0] = open_file->DriveLetter;

	HANDLE Device = CreateFile(
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

	wprintf_s(DeviceName, DEVICE_DIR_NAME "%u", number_device);

	if (!DefineDosDevice(
		DDD_RAW_TARGET_PATH,
		&VolumeName[4],
		DeviceName
	))
	{
		// PrintLastError(&VolumeName[4]);
		return -1;
	}

	Device = CreateFile(
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
		DefineDosDevice(DDD_REMOVE_DEFINITION, &VolumeName[4], NULL);
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
		DefineDosDevice(DDD_REMOVE_DEFINITION, &VolumeName[4], NULL);
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
	std::wcin >> file_name;
	std::wcout << file_name << std::endl;
	std::wcout << "Type file password:" << std::endl;
	std::string password(16, '0');
	std::cin >> password;
	password.resize(16, '0');
	size_t file_size = 0;
	std::wcout << "Type file size:" << std::endl;
	std::wcin >> file_size;
	char drive_letter;
	std::wcout << "Type device letter:" << std::endl;
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
		std::wcout << "Error CreateFileA! GetLastError - " << GetLastError();
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

		std::wcout << "Error DeviceIoControl(IOCTL_FILE_DISK_CLOSE_FILE)! GetLastError - " << GetLastError();
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

		std::wcout << "Error DeviceIoControl(FSCTL_DISMOUNT_VOLUME)! GetLastError - " << GetLastError();
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
		std::wcout << "Error DeviceIoControl(DDD_REMOVE_DEFINITION)! GetLastError - " << GetLastError();
		return;
	}

	SHChangeNotify(SHCNE_DRIVEREMOVED, SHCNF_PATH, DriveName, NULL);

}

void unmount_disk()
{
	char letter = 0;
	std::wcout << "Type letter disk...\n";
	std::cin >> letter;
	unmount(letter);
}


void run_driver(void)
{
	const std::wstring device_name = L"TestMyDriver";
	const std::wstring path = L"%SystemRoot%\\System32\\Drivers\\MyDriver.sys";

	ved::install_manager::install_service(path, device_name);
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
		setlocale(LC_ALL, "");
		ved::driver_disk& driver = ved::driver_disk::get_instance();

		/*std::wcout << "Type file name:" << std::endl;

		std::wstring file_name;
		std::wcin >> file_name;
		std::wcout << file_name << std::endl;
		std::wcout << "Type file password:" << std::endl;
		std::string password(16, '0');
		std::cin >> password;
		password.resize(16, '0');
		size_t file_size = 0;
		std::wcout << "Type file size:" << std::endl;
		std::wcin >> file_size;
		char drive_letter;
		std::wcout << "Type device letter:" << std::endl;
		std::cin >> drive_letter;
		size_t number = 0;
		std::wcout << "Type number_device:" << std::endl;
		std::wcin >> number;*/

		//AddDevice();
		//driver.un_mount_disk('Z');
		auto file_info = create_file_info(L"C:\\test2323.img", 100, 'Z', "1234567891234567");

		driver.mount_disk(file_info);
		//mount(file_info,1);



		/*
	   size_t choose = 0;
	   std::wcout<<L"1. - Add device\n2. - Mount disk\n3. - Un mount disk\n4. - Install and run device\n5. - Stop and delete device";
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
	   }*/
			   		 	

	}
	catch (const ved::c_win_api_exception& error)
	{
		std::wcout << error.GetMessageW() << std::endl;
	}
	catch (const ved::driver_exception& error)
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

