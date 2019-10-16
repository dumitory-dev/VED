#pragma once
#include "../../stdafx.h"

namespace ved
{

	class c_exception
	{

	public:

		c_exception(const c_exception&) = default;
		c_exception(c_exception&&) = default;
		c_exception& operator = (const c_exception&) = default;
		c_exception& operator = (c_exception&&) = default;

	protected:

		std::wstring m_wsMessage{};
		using ULONG = unsigned long;
		ULONG m_ulCode{};

	public:

		explicit c_exception(const std::wstring& ws_message) : c_exception(ws_message, {}) { }

		explicit c_exception(const ULONG ul_code) : c_exception({}, ul_code) { }

		explicit c_exception(const std::wstring& ws_message,
			ULONG ulCode) : m_wsMessage(ws_message), m_ulCode(ulCode) { }

		virtual ~c_exception(void) = default;

		virtual std::wstring GetMessage(void) const
		{

			return this->m_wsMessage;

		}

		auto get_code(void) const noexcept
		{

			return this->m_ulCode;

		}

	};

	class CNotImplementedException : public c_exception
	{

	public:

		CNotImplementedException(void) : c_exception(L"NotImplementedException") { }

	};


	class c_win_api_exception : public c_exception
	{

	public:

		using c_exception::c_exception;

		std::wstring GetMessage(void) const override
		{

			if (!c_exception::m_ulCode)
				return c_exception::m_wsMessage;

			LPVOID lp_msg_buf{};

			if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				{},
				c_exception::m_ulCode,
				MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
				reinterpret_cast<LPWSTR>(&lp_msg_buf),
				{},
				{}))
				return c_exception::m_wsMessage;

			std::wostringstream wos{};
			wos << c_exception::m_wsMessage << std::endl;
			wos << L"Error code " << c_exception::m_ulCode << std::endl;
			wos << reinterpret_cast<LPCWSTR>(lp_msg_buf);

			::LocalFree(lp_msg_buf);

			return wos.str();

		}

	};


	class c_command_line_argument_exception final : public c_win_api_exception
	{

	public:

		using c_win_api_exception::c_win_api_exception;

	};

	class c_convert_exception final : public c_win_api_exception
	{

	public:

		using c_win_api_exception::c_win_api_exception;

	};

	class c_file_storage_exception final : public c_exception
	{

	public:
		using c_exception::c_exception;

	};

	class c_digit_sign_exception final : public c_win_api_exception

	{

	public:
		using c_win_api_exception::c_win_api_exception;

	};

	class handle_exception final : public c_win_api_exception
	{

	public:
		using c_win_api_exception::c_win_api_exception;

	};


	class map_file_exception final : public c_win_api_exception
	{

	public:
		using c_win_api_exception::c_win_api_exception;

	};

	class ThreadPoolException : public c_win_api_exception
	{

	public:
		using c_win_api_exception::c_win_api_exception;

	};

	class IoCompletionPortException : public c_win_api_exception
	{

	public:
		using c_win_api_exception::c_win_api_exception;

	};

	class IFileException : public c_win_api_exception
	{

	public:
		using c_win_api_exception::c_win_api_exception;

	};

	class file_exception final : public c_win_api_exception
	{

	public:
		using c_win_api_exception::c_win_api_exception;

	};

	class HashException : public c_win_api_exception
	{

	public:
		using c_win_api_exception::c_win_api_exception;

	};

	class CIndexOutOfRangeException : public c_exception
	{

	public:

		CIndexOutOfRangeException(void) : c_exception(L"IndexOutOfRangeException") { }

	};

	class driver_exception : public c_win_api_exception
	{
	public:
		using c_win_api_exception::c_win_api_exception;
	};

}