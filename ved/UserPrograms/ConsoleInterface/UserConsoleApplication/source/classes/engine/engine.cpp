#include "engine.h"
namespace  ved
{
	void engine::execute(void)
	{
		this->set_arguments();
		std::wstring name_func{};
		this->arguments_stream_>>name_func;
		const auto res_func = this->functions_.find(name_func);
		if (res_func == this->functions_.cend())
		{
			throw std::runtime_error("Invalid arguments!");
		}
		res_func->second(*this);
		
	}
	
	void  engine::set_arguments(void)
	{
	
		this->arguments_stream_ = ved::CommandLineArgument::get_command_lines_stream();
		
		if (this->arguments_stream_.eof())
		{
			throw std::runtime_error("Invalid arguments!");
		}
	}

	void engine::mount(void)
	{
				
		if (this->arguments_stream_.eof())
		{
			throw std::runtime_error("invalid argument!(mount)");
		}
		
		std::wstring path;
		std::wstring password;
		wchar_t letter;
		
		this->arguments_stream_>>path;
		this->arguments_stream_>>password;
		this->arguments_stream_>>letter;
				
		const std::string password_a(password.cbegin(),password.cend());
		this->ved_manager_->mount(path,password_a,letter);
		
	}

	void engine::create_and_mount()
	{

		//this->arguments_stream_;

		if (this->arguments_stream_.eof())
		{
			throw std::runtime_error("invalid argument!(create_and_mount)");
		}

		std::wstring path;
		std::wstring password;
		unsigned long long size;
		wchar_t letter;
		int mode;


		this->arguments_stream_>>path;
		this->arguments_stream_>>password;
		this->arguments_stream_>>size;
		this->arguments_stream_>>letter;
		this->arguments_stream_>>mode;

		size = size * 1024 * 1024;

		std::string password_a(password.cbegin(),password.cend());
		
		this->ved_manager_->mount_ex(path,size,password_a,letter,static_cast<Crypt>(mode));
		
	}

	void engine::un_mount(void)
	{
		if (this->arguments_stream_.eof())
		{
			throw std::runtime_error("invalid argument!(un_mount)");
		}
		wchar_t letter;
		this->arguments_stream_>>letter;

		this->ved_manager_->un_mount(letter);
		
		
	}

	void engine::run_driver(void)
	{
		std::wstring startup_flag;

	    this->arguments_stream_>>startup_flag;
		
		if (startup_flag.empty())
		{
			this->ved_manager_->run_driver();
		}
		
		if (!startup_flag.empty() && startup_flag != L"-auto")
		{
			throw std::runtime_error("invalid argument!(un_mount)");
		}
				
		this->ved_manager_->run_driver(SERVICE_AUTO_START);
				
	}

	void engine::stop_driver(void) const
	{
		
		this->ved_manager_->stop_driver();
		
	}

	void engine::help(void) const
	{
		/*
		 * {L"-mount",&engine::mount},
			{L"-camount",&engine::create_and_mount},
			{L"-unmount",&engine::un_mount},
			{L"-start",&engine::run_driver},
			{L"-stop",&engine::run_driver},
			{L"-help",&engine::run_driver}
		 */
		std::wcout<<L"\n---HELP---\n";
		std::wcout<<L"\n-mount - mount disk from file. Params:\n1.Path file\n2.Password\n3.Letter disk\n\n";
		std::wcout<<L"\n-camount - create file and mount disk. Params:\n1.Path file\n2.Password\n3.Size file\n4.Letter disk\n5.Mode crypt(1 - RC4, 2 - AES)\n\n";
		std::wcout<<L"\n-unmount - Unmount disk. Params:\n1.Letter disk\n\n";
		std::wcout<<L"\n-start - Install and start driver. Params:\n1.Mode(optional) (-auto - autostart driver at system startup)\n";
		
	}
}
