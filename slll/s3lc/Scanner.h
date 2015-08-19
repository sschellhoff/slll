#pragma once

#include "Token.h"
#include <string>

namespace slll {

	class Scanner
	{
	private:
		std::string sourcecode;
		size_t pointer;
	public:
		Scanner(std::string sourcecode);
		~Scanner();

		Token NextToken();
	};

}

