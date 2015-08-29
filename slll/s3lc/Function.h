#pragma once

#include <string>
#include <vector>

namespace slll {

	class Function
	{
	private:
		std::string name;
		std::vector<std::string> parameters;
	public:
		Function(std::string name);
		~Function();
		size_t GetParameterCount()const;
		const std::string &Name()const;
	};

}