#include "classes/driver_disk/driver_disk.h"
int main(void)
{
	try
	{
		
		ved::driver_disk & driver = ved::driver_disk::get_instance();
		driver.connect_to_main_device(L"\\??\\TestLink");
		LARGE_INTEGER size;
		size.QuadPart = 10000;
		size.QuadPart *= 1024;
		size.QuadPart *= 1024;
		driver.create_file_disk(ved::driver_disk::OPEN_FILE_INFORMATION::make(L"C:\\test228.img",size,L'J',"1230000000000000"));
		
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


