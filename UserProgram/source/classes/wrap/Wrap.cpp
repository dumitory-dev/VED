#include "Wrap.h"
namespace ved {
	
	handle::handle(HANDLE h) noexcept : h_(h) { }

	handle::~handle(void) noexcept
	{

		if (this->h_)
			::CloseHandle(this->h_);

	}


	handle::operator HANDLE(void) const noexcept
	{

		return this->h_;

	}


	bool handle::operator !(void) const noexcept
	{
		
		return this->h_ == nullptr || this->h_ == INVALID_HANDLE_VALUE;
		
	}


}
