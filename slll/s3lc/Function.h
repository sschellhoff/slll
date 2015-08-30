#pragma once

#include <string>
#include <vector>

#include "Variable.h"

namespace slll {

	class Function
	{
	private:
		std::string name;
		std::vector<Variable> parameters;
	public:
		Function(std::string name);
		Function(std::string name, std::vector<Variable> parameters);
		~Function();
		size_t GetParameterCount()const;
		const std::string &Name()const;
	};

}