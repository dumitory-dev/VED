#include "source/classes/engine/engine.h"
#include "classes/copy_sparse/copy_sparse.h"

int main(int argc, wchar_t ** argv)
{
	try
	{

		std::vector<OPEN_FILE_INFORMATION> data(10);

		POPEN_FILE_INFORMATION file = data.data();

		file[1].DriveLetter = 'A';
			file[0].DriveLetter = 'A';
	/*	auto res = ved::command_line_argument::get_command_lines_vector();
		std::wcout<<res[0]<<res[1]<<std::endl;
		std::cout<<"In progress..."<<std::endl;
		ved::copy_sparse::copy(res[0],res[1]);
		std::cout<<"Ok!"<<std::endl;*/
		//ved::engine::get_instance().execute();
							
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


