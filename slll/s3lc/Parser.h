#pragma once

#include <string>

#include "Siever.h"

namespace slll {
	class Parser
	{
	private:
		Siever lexer;
	public:
		Parser(std::string sourcecode);
		Parser(Siever &&lexer);
		~Parser();
		Parser(const Parser &c) = delete;

		void Parse();
	};

}