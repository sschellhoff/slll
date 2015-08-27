#pragma once

#include <exception>

namespace slll {

	class VariableNotFoundExeption : std::exception
	{
	public:
		VariableNotFoundExeption();
		~VariableNotFoundExeption();
	};

}