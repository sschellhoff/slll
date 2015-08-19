#pragma once

#include <string>
#include <memory>

#include "Siever.h"
#include "Token.h"
#include "IAST.h"

using ast = std::unique_ptr<slll::IAST>;

namespace slll {
	class Parser
	{
	private:
		Siever lexer;
		ast expression();
		ast expressionext(ast left);
		ast factor();
		Token currentToken;
	public:
		Parser(std::string sourcecode);
		~Parser();
		Parser(const Parser &c) = delete;

		ast Parse();
	};

}