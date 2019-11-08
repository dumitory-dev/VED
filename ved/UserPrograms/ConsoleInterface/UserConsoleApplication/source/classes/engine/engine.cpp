#include "engine.h"
namespace  ved
{
	void engine::execute(void)
	{
		this->set_arguments();
		std::wstring name_func{};
		this->arguments_stream_ >> name_func;
		
		if (name_func != L"-start" && name_func != L"-stop")
		{
			if (this->arguments_stream_.eof())
			{
				throw std::runtime_error("invalid argument!(mount)");
			}
		}
		
		const auto res_func = this->functions_.find(name_func);
		if (res_func == this->functions_.cend())
		{
			throw std::runtime_error("Invalid arguments!");
		}

		res_func->second(*this);

	}

	void  engine::set_arguments(void)
	{

		this->arguments_stream_ = ved::command_line_argument::get_command_lines_stream();

		if (this->arguments_stream_.eof())
		{
			throw std::runtime_error("Invalid arguments!");
		}
	}

	void engine::mount(void)
	{



		std::wstring path;
		std::wstring password;
		wchar_t letter;

		this->arguments_stream_ >> path;
		this->arguments_stream_ >> password;
		this->arguments_stream_ >> letter;

		const std::string password_a(password.cbegin(), password.cend());
		this->ved_manager_->mount(path, password_a, letter);

	}

	void engine::create_and_mount()
	{

		//this->arguments_stream_;


		std::wstring path;
		std::wstring password;
		unsigned long long size;
		wchar_t letter;
		int mode;

		this->arguments_stream_ >> path;
		this->arguments_stream_ >> password;
		this->arguments_stream_ >> size;
		this->arguments_stream_ >> letter;
		this->arguments_stream_ >> mode;

		size = size * 1024 * 1024;

		this->ved_manager_->mount_ex(path, size, { password.cbegin(),password.cend() }, letter, static_cast<Crypt>(mode));

	}

	void engine::un_mount(void)
	{
		
		wchar_t letter;
		this->arguments_stream_ >> letter;

		this->ved_manager_->un_mount(letter);


	}

	void engine::create_file()
	{

		std::wstring path;
		std::wstring password;
		unsigned long long size;
		int mode;

		this->arguments_stream_ >> path;
		this->arguments_stream_ >> size;
		this->arguments_stream_ >> password;
		this->arguments_stream_ >> mode;

		size = size * 1024 * 1024;

		this->ved_manager_->create_file(path, size, { password.cbegin(),password.cend() }, static_cast<Crypt>(mode));


	}

	void engine::start_driver(void)
	{
		std::wstring startup_flag;

		this->arguments_stream_ >> startup_flag;

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
			{L"-start",&engine::start_driver},
			{L"-stop",&engine::start_driver},
			{L"-help",&engine::start_driver}
		 */
		std::wcout << L"\n---HELP---\n";
		std::wcout << L"\n-create - create image file. Params:\n1.Path file\n2.Size file\n3.Password\n4.Mode crypt(1 - RC4, 2 - AES)\n\n";
		std::wcout << L"\n-mount - mount disk from file. Params:\n1.Path file\n2.Password\n3.Letter disk\n\n";
		std::wcout << L"\n-camount - create file and mount disk. Params:\n1.Path file\n2.Password\n3.Size file\n4.Letter disk\n5.Mode crypt(1 - RC4, 2 - AES)\n\n";
		std::wcout << L"\n-unmount - Unmount disk. Params:\n1.Letter disk\n\n";
		std::wcout << L"\n-start - Install and start driver. Params:\n1.Mode(optional) (-auto - autostart driver at system startup)\n";

	}

	void engine::show_mounted_disks(void) const
	{
		const auto data = this->ved_manager_->get_mounted_disks();
		if (data.empty())
		{
			std::wcout<<L"\nNo mounted drives!"<<std::endl;
			return;
		}

		for (const auto & open_file_information : data)
		{
			std::wcout<<"\n"<<"Path file - "<<open_file_information.FileName<<std::endl;
		}

		
		
	}
}
