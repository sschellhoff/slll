#pragma once

#include "Token.h"
#include <string>

namespace slll {

	class Scanner
	{
	public:
		Scanner(std::string sourcecode);
		~Scanner();

		Token NextToken() const;
	};

}

