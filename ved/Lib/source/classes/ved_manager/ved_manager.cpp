#include "ved_manager.h"
namespace ved
{
	void ved_manager::mount(
		const std::wstring& path,
		const std::string& password,
		WCHAR letter)
	{
		this->connected();
		
		LARGE_INTEGER size;
		size.QuadPart = 0;
		const auto disk_info = ved::driver_disk::make_file_info(path,size,letter,password,Crypt::CryptPrev);
		this->driver_.mount_disk(disk_info);
	}

	void ved_manager::mount_ex(
		const std::wstring& path,
		const unsigned long long size, 
		const std::string& password,
		const WCHAR letter,
		const Crypt mode)
	{
		this->connected();
		LARGE_INTEGER size_file;
		size_file.QuadPart = size;
		const auto disk_info = ved::driver_disk::make_file_info(path,size_file,letter,password,mode);
		this->driver_.mount_disk(disk_info);
		
	}
	

	void ved_manager::create_file(
		const std::wstring& path,
		const unsigned long long size,
		const std::string& password,                      
		const Crypt mode)
	{
		this->connected();
		LARGE_INTEGER size_file;
		size_file.QuadPart = size;
		const auto disk_info = ved::driver_disk::make_file_info(path,size_file,L' ',password,mode);
		this->driver_.create_file_disk(disk_info);
		
		
	}
		
	void ved_manager::un_mount(const WCHAR letter)
	{
		this->connected();
		ved::driver_disk::un_mount_disk(letter);
		
	}

	void ved_manager::run_driver(DWORD flag_startup, const std::wstring& path_driver, const std::wstring& name_service)
	{
		
		ved::install_manager::install_service(path_driver,name_service,flag_startup);
		ved::install_manager::load_service(name_service);
						
	}

	void ved_manager::stop_driver(const std::wstring& device_name)
	{
		
		ved::install_manager::unload_service(device_name);
		ved::install_manager::uninstall_service(device_name);
		
	}
}
