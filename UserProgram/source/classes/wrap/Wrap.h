#pragma once
#include "../../stdafx.h"
#include "../../classes/exceptions/Exception.h"

namespace ved {

	class handle 
	{
			
	public:

		handle(const handle&) = delete;
		handle(handle&&) = delete;
		handle& operator = (const handle&) = delete;
		handle& operator = (handle&&) = delete;
				
		explicit handle(HANDLE = {}) noexcept;
		
		virtual ~handle(void) noexcept;

		operator HANDLE (void) const noexcept;
		
		bool operator ! (void) const noexcept;
					
	private:
		
		HANDLE h_{};

	};

}
