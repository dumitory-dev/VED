#include "driver_disk.h"
namespace ved
{
	driver_disk::_OPEN_FILE_INFORMATION* driver_disk::_OPEN_FILE_INFORMATION::make(
		const std::wstring& file_name, size_t file_size, WCHAR drive_letter, const std::string& file_password)
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
	
		_OPEN_FILE_INFORMATION* file_info{};
		file_info = static_cast<_OPEN_FILE_INFORMATION*>(malloc(
			sizeof(_OPEN_FILE_INFORMATION*) + file_name.length() * sizeof(WCHAR) + 7));

		if (file_info == nullptr)
		{
			throw std::runtime_error("Error malloc _OPEN_FILE_INFORMATION!");
		}
		
		memset(
			file_info,
			0,
			sizeof(_OPEN_FILE_INFORMATION*) + file_name.length() * sizeof(WCHAR) + 7
		);

		wcscpy(file_info->FileName, L"\\??\\");
		wcscat(file_info->FileName, file_name.c_str());

		file_info->FileNameLength = static_cast<USHORT>(wcslen(file_info->FileName));
		file_info->FileSize.QuadPart = static_cast<LONGLONG>(file_size) * 1024 * 1024;
		file_info->DriveLetter = drive_letter;

		std::copy(file_password.cbegin(), file_password.cend(), file_info->Password);
		file_info->PasswordLength = static_cast<USHORT>(file_password.length());

		return file_info;
	}

	void driver_disk::mount_disk(POPEN_FILE_INFORMATION open_file) const
	{
		size_t number_device{};
				
		number_device = this->main_device_.send_ctl_code(IOCTL_GET_FREE_DEVICE);
		if (!number_device)
		{
			number_device = this->main_device_.send_ctl_code(IOCTL_FILE_ADD_DEVICE);
		}

		const std::wstring path_new_device = DEVICE_DIR_NAME + std::to_wstring(number_device);
				
		ved::define_device_manager define_manager(open_file->DriveLetter);
		
		if (define_manager.check_define())
		{
			throw ved::driver_exception(L"Error check_define!",::GetLastError());
		}
		
		define_manager.add_device(path_new_device);
		
		try
		{
			auto define_device = define_manager.make_device();
			define_device.connect();
			define_device.send_ctl_code(
				IOCTL_FILE_DISK_OPEN_FILE,
				open_file,
				sizeof(_OPEN_FILE_INFORMATION) + open_file->FileNameLength * sizeof(WCHAR) + 7);
			define_manager.report_define();
		
						
		}
		catch (...)
		{
			define_manager.delete_define();
			define_manager.report_delete_define();
			
			throw;
		}

	
	}

	void driver_disk::un_mount_disk(const WCHAR letter)
	{
			
		const ved::define_device_manager define_manager(letter);
		auto device = define_manager.make_device();
		device.connect();
		device.send_ctl_code(IOCTL_FILE_DISK_CLOSE_FILE);
		device.send_ctl_code(FSCTL_DISMOUNT_VOLUME);
		define_manager.delete_define();
		define_manager.report_delete_define();
			
	}
}
