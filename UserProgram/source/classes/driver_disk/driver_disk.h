#pragma once
#include "../../stdafx.h"
#include "../define_device/define_device_manager.h"
#include "../device/device.h"

#define DEVICE_BASE_NAME	L"\\FileDisk"
#define DEVICE_DIR_NAME		L"\\Device"	DEVICE_BASE_NAME
#define DEVICE_NAME_PREFIX	DEVICE_DIR_NAME	


#define IOCTL_FILE_DISK_OPEN_FILE	CTL_CODE(FILE_DEVICE_DISK, 0x800, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_FILE_DISK_CLOSE_FILE	CTL_CODE(FILE_DEVICE_DISK, 0x801, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_FILE_ADD_DEVICE CTL_CODE(FILE_DEVICE_DISK, 0x802, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_GET_FREE_DEVICE CTL_CODE(FILE_DEVICE_DISK, 0x803, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)

namespace ved
{
	class driver_disk
	{
	public:
		
		typedef struct _OPEN_FILE_INFORMATION {

			LARGE_INTEGER	FileSize;
			WCHAR			DriveLetter;
			USHORT			FileNameLength;
			USHORT			PasswordLength;
			CHAR			Password[16];
			WCHAR			FileName[1];

			static _OPEN_FILE_INFORMATION* make(
				const std::wstring& file_name,
				size_t file_size,
				char drive_letter,
				const std::string& file_password);

			
		}OPEN_FILE_INFORMATION, * POPEN_FILE_INFORMATION;


		driver_disk(const driver_disk& other) = delete;
		driver_disk(driver_disk&& other) noexcept = delete;
		driver_disk& operator=(const driver_disk& other) = delete;
		driver_disk& operator=(driver_disk&& other) noexcept = delete;

		static driver_disk& get_instance(void)
		{
			static driver_disk driver{};
			return driver;
		}
		
		void mount_disk(POPEN_FILE_INFORMATION open_file) const;

		void un_mount_disk(WCHAR letter);


	private:
		driver_disk(void):main_device_(this->path_main_device_)
		{
			this->main_device_.connect();
		}
		~driver_disk(void) = default;


		const wchar_t * letter_prefix_ = LR"(\\.\)";
		const wchar_t * drive_prefix_ = L":\\";
		const std::wstring path_main_device_ =  L"\\\\.\\TestLink";
				
		device main_device_{};
	
		
	};
}