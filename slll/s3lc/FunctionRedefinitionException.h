#pragma once

#include <exception>

namespace slll {

	class FunctionRedefinitionException : std::exception
	{
	public:
		FunctionRedefinitionException();
		~FunctionRedefinitionException();
	};

}