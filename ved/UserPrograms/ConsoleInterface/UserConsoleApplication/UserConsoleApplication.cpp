#include "classes/driver_disk/driver_disk.h"

int main(void)
{
	try
	{

		auto & disk = ved::driver_disk::get_instance();
		disk.connect_to_main_device(DEVICE_SYM_LINK);

		LARGE_INTEGER size;
		size.QuadPart = 100 * 1024 * 1024;
		const auto ptr = ved::driver_disk::make_file_info(L"C:\\test.img",size,L'K',"1230000000000000",Crypt::RC4);
		disk.create_file_disk(ptr);
				
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


