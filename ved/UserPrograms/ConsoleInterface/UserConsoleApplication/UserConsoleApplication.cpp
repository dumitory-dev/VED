#include "classes/driver_disk/driver_disk.h"
#include "classes/install_manager/install_manager.h"

int main(void)
{
	try
	{
		//const std::wstring device_name = L"TestMyDriver!";
		//const std::wstring path = L"%SystemRoot%\\System32\\Drivers\\Driver.sys";

		//ved::install_manager::install_service(path, device_name);
		//ved::install_manager::load_service(device_name);
		auto & disk = ved::driver_disk::get_instance();
		disk.connect_to_main_device(DEVICE_SYM_LINK);

		LARGE_INTEGER size;
		size.QuadPart = 10 * 1024 * 1024;
		 auto ptr = ved::driver_disk::make_file_info(L"C:\\test4.img",size,L'J',"1230000000000000",Crypt::RC4);
				
		disk.create_file_disk(ptr);
		ptr->CryptMode = Crypt::CryptPrev;
		disk.mount_disk(ptr);

		//ved::define_device_manager::make_path_letter(L'K');
		
	}

	catch (const ved::driver_exception & error)
	{
		std::wcout<<error.GetMessageW()<<std::endl;
	}
	catch (const ved::c_win_api_exception & error)
	{
		std::wcout<<error.GetMessageW()<<std::endl;
	}
	catch(const std::exception & error)
	{
		std::wcout<<error.what()<<std::endl;
	}
	catch (...)
	{
		std::wcout<<"error!"<<std::endl;
	}
  
}


