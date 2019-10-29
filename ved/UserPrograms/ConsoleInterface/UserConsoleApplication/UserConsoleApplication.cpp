#include "classes/driver_disk/driver_disk.h"
int main(void)
{
	try
	{
		ved::driver_disk & driver = ved::driver_disk::get_instance();
	}
	catch (...)
	{
	}
  
}


