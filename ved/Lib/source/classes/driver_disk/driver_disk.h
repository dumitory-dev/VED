#pragma once
#include "../define_device/define_device_manager.h"
#include "../device/device.h"
#include "open_file_info.h"


namespace ved
{
	class driver_disk
	{
	public:
			

		static std::unique_ptr<OPEN_FILE_INFORMATION> make_file_info(
				const std::wstring& file_name,
				LARGE_INTEGER file_size,
				WCHAR drive_letter,
				const std::string& file_password,
				enum Crypt mode_crypt
			);
		
		driver_disk(const driver_disk& other) = delete;
		driver_disk(driver_disk&& other) noexcept = delete;
		driver_disk& operator=(const driver_disk& other) = delete;
		driver_disk& operator=(driver_disk&& other) noexcept = delete;

		static driver_disk& get_instance(void)
		{
			static driver_disk driver{};
			
			return driver;
		}

		void connect_to_main_device(const std::wstring& path)
		{
			this->main_device_ = device(path);
			this->main_device_.connect();
			this->path_main_device_ = path;
		}

		auto is_connected(void) const noexcept {

			return this->main_device_.is_connect();
		}

		
		void mount_disk(const std::unique_ptr<OPEN_FILE_INFORMATION> & open_file) const;

		void create_file_disk(const std::unique_ptr<OPEN_FILE_INFORMATION> & open_file) const;

		static void un_mount_disk(WCHAR letter);


	private:
		driver_disk(void) = default;
		~driver_disk(void) = default;
		
		[[nodiscard]] size_t get_free_number_device(void)const;

		std::wstring path_main_device_{};

		device main_device_{};


	};

}

