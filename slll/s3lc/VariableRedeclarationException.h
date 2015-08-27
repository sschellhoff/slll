#pragma once

#include <exception>

namespace slll {

	class VariableRedeclarationException : std::exception
	{
	public:
		VariableRedeclarationException();
		~VariableRedeclarationException();
	};

}