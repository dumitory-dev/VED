
#include "classes/install_manager/install_manager.h"
#include "interface/i_ved_manager.h"
#include "source/classes/comand_line_argument/comand_line_argument.h"
#include "source/classes/engine/engine.h"
#include "classes/ved_manager/ved_manager.h"


int main(int argc, char ** argv)
{
	try
	{
		 ved::engine::get_instance().execute();
			
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


