#pragma once

#include <string>

namespace slll {

	class Function
	{
	private:
		std::string name;
		unsigned int numParams;
	public:
		Function(std::string name, unsigned int paramCount);
		~Function();
		unsigned int GetParameterCount()const;
		const std::string &Name()const;
	};

}