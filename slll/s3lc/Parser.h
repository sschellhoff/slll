#pragma once

#include <string>
#include <memory>

#include "Siever.h"
#include "Token.h"
#include "IAST.h"
#include "VariablesEnvironment.h"

namespace slll {
	class Parser
	{
	private:
		Siever lexer;
		ast program();
		ast functiondefinition();
		ast codeblock(VariablesEnvironment *env);
		ast statement(VariablesEnvironment *env);
		ast expression(VariablesEnvironment *env);
		ast addsub(VariablesEnvironment *env);
		ast addsubext(VariablesEnvironment *env, ast left);
		ast multdivmod(VariablesEnvironment *env);
		ast multdivmodext(VariablesEnvironment *env, ast left);
		ast relation(VariablesEnvironment *env);
		ast relationext(VariablesEnvironment *env, ast left);
		ast equality(VariablesEnvironment *env);
		ast equalityext(VariablesEnvironment *env, ast left);
		ast conjunct(VariablesEnvironment *env);
		ast conjunctext(VariablesEnvironment *env, ast left);
		ast disjunct(VariablesEnvironment *env);
		ast disjunctext(VariablesEnvironment *env, ast left);
		ast factor(VariablesEnvironment *env);
		ast literal(VariablesEnvironment *env);
		ast if_statement(VariablesEnvironment *env);
		ast while_statement(VariablesEnvironment *env);
		ast declaration(VariablesEnvironment *env, unsigned int varid);
		ast assignment(VariablesEnvironment *env, unsigned int varid);
		Token currentToken;
	public:
		Parser(std::string sourcecode);
		~Parser();
		Parser(const Parser &c) = delete;

		ast Parse();
	};

}