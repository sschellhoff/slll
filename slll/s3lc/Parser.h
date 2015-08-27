#pragma once

#include <string>
#include <memory>

#include "Siever.h"
#include "Token.h"
#include "IAST.h"
#include "Environment.h"

namespace slll {
	class Parser
	{
	private:
		Siever lexer;
		ast statement(Environment *env);
		ast expression(Environment *env);
		ast expressionext(Environment *env, ast left);
		ast term(Environment *env);
		ast termext(Environment *env, ast left);
		ast factor(Environment *env);
		ast literal(Environment *env);
		ast if_statement(Environment *env);
		ast while_statement(Environment *env);
		ast declaration(Environment *env, unsigned int varid);
		ast assignment(Environment *env, unsigned int varid);
		Token currentToken;
	public:
		Parser(std::string sourcecode);
		~Parser();
		Parser(const Parser &c) = delete;

		ast Parse();
	};

}