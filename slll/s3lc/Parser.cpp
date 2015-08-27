#include "Parser.h"

#include "ParseException.h"
#include "VariableRedeclarationException.h"
#include "VariableNotFoundExeption.h"

#include "IntConstASTNode.h"
#include "BinOpASTNode.h"
#include "PrintIntStatementASTNode.h"
#include "PrintNewLineStatementASTNode.h"
#include "StatementBlockASTNode.h"
#include "DeclarationASTNode.h"
#include "AssignmentASTNode.h"
#include "VariableASTNode.h"
#include "NegationASTNode.h"

using namespace slll;

Parser::Parser(std::string sourcecode) :lexer(sourcecode), currentToken(lexer.NextToken()) {
}

Parser::~Parser() {
}

ast Parser::Parse() {
	auto result{ statement(nullptr) };
	if (currentToken.Type() != TokenType::eof) {
		throw ParseException();
	}
	return result;
}

ast Parser::statement(Environment *env) {
	if (currentToken.Type() == TokenType::lbra) {
		currentToken = lexer.NextToken();
		auto result = std::make_unique<StatementBlockASTNode>(env);
		while (currentToken.Type() != TokenType::rbra && currentToken.Type() != TokenType::eof) {
			result->Add(statement(result->Environment()));
		}
		if (currentToken.Type() != TokenType::rbra) {
			throw ParseException("missing right bracket of statement block");
		}
		currentToken = lexer.NextToken();
		return std::move(result);
	} else if (currentToken.Type() == TokenType::printi_ident) {
		currentToken = lexer.NextToken();
		return std::make_unique<PrintIntStatementASTNode>(expression(env));
	} else if (currentToken.Type() == TokenType::println) {
		currentToken = lexer.NextToken();
		return std::make_unique<PrintNewLineStatementASTNode>();
	} else if (currentToken.Type() == TokenType::identifier) {
		auto name = currentToken.Value();
		currentToken = lexer.NextToken();
		if (currentToken.Type() == TokenType::decl) {
			if (env->Contains(name)) {
				throw VariableRedeclarationException();
			}
			auto var = env->AddVariable(name, 4); //TODO make size variable
			return declaration(env, var);
		} else if (currentToken.Type() == TokenType::assign) {
			if (!env->ExistsInScope(name)) {
				throw VariableNotFoundExeption();
			}
			auto var = env->GetId(name);
			return assignment(env, var);
		}
	}
	throw ParseException();
}

ast Parser::expression(Environment *env) {
	auto left = term(env);
	return expressionext(env, std::move(left));
}

ast Parser::expressionext(Environment *env, ast left) {
	switch (currentToken.Type()) {
	case TokenType::add:
	case TokenType::sub:
		auto tt = currentToken.Type();
		currentToken = lexer.NextToken();
		auto leftNew = std::make_unique<BinOpASTNode>(std::move(left), term(env), tt);
		return expressionext(env, std::move(leftNew));
	}
	return left;
}

ast Parser::term(Environment *env) {
	auto left = factor(env);
	return termext(env, std::move(left));
}

ast Parser::termext(Environment *env, ast left) {
	switch (currentToken.Type()) {
		case TokenType::mult:
		case TokenType::div:
		case TokenType::mod:
			auto tt = currentToken.Type();
			currentToken = lexer.NextToken();
			auto leftNew = std::make_unique<BinOpASTNode>(std::move(left), factor(env), tt);
			return termext(env, std::move(leftNew));
	}
	return left;
}

ast Parser::factor(Environment *env) {
	if (currentToken.Type() == TokenType::intconst || currentToken.Type() == TokenType::identifier) {
		return literal(env);
	}
	else if (currentToken.Type() == TokenType::sub) {
		currentToken = lexer.NextToken();
		return std::make_unique<NegationASTNode>(literal(env));
	} else if (currentToken.Type() == TokenType::lpar) {
		currentToken = lexer.NextToken();
		auto result = expression(env);
		if (currentToken.Type() != TokenType::rpar) {
			throw ParseException();
		}
		currentToken = lexer.NextToken();
		return result;
	}
	throw ParseException();
}

ast Parser::literal(Environment *env) {
	if (currentToken.Type() == TokenType::intconst) {
		int val = atoi(currentToken.Value().c_str());
		currentToken = lexer.NextToken();
		return std::make_unique<IntConstASTNode>(val);
	} else if (currentToken.Type() == TokenType::identifier && env->ExistsInScope(currentToken.Value())) {
		auto var = env->GetId(currentToken.Value());
		currentToken = lexer.NextToken();
		return std::make_unique<VariableASTNode>(var);
	}
	throw ParseException();
}

ast Parser::declaration(Environment *env, unsigned int varid) {
	if (currentToken.Type() == TokenType::decl) {
		currentToken = lexer.NextToken();
		return std::make_unique<DeclarationASTNode>(varid, expression(env));
	}
	throw ParseException();
}

ast Parser::assignment(Environment *env, unsigned int varid) {
	if (currentToken.Type() == TokenType::assign) {
		currentToken = lexer.NextToken();
		return std::make_unique<AssignmentASTNode>(varid, expression(env));
	}
	throw ParseException();
}