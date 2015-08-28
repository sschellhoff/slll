#include "Parser.h"

#include "ParseException.h"
#include "VariableRedeclarationException.h"
#include "VariableNotFoundExeption.h"
#include "BinaryOperator.h"

#include "IntConstASTNode.h"
#include "BinOpASTNode.h"
#include "PrintIntStatementASTNode.h"
#include "PrintNewLineStatementASTNode.h"
#include "StatementBlockASTNode.h"
#include "DeclarationASTNode.h"
#include "AssignmentASTNode.h"
#include "VariableASTNode.h"
#include "NegationASTNode.h"
#include "IfASTNode.h"
#include "IfElseASTNode.h"
#include "WhileASTNode.h"
#include "ComplementASTNode.h"

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

ast Parser::statement(VariablesEnvironment *env) {
	if (currentToken.Type() == TokenType::lbra) {
		currentToken = lexer.NextToken();
		auto result = std::make_unique<StatementBlockASTNode>(env);
		while (currentToken.Type() != TokenType::rbra && currentToken.Type() != TokenType::eof) {
			result->Add(statement(result->VariablesEnvironment()));
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
	} else if (currentToken.Type() == TokenType::if_ident) {
		return if_statement(env);
	} else if(currentToken.Type() == TokenType::while_ident) {
		return while_statement(env);
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

ast Parser::expression(VariablesEnvironment *env) {
	return disjunct(env);
}

ast Parser::disjunct(VariablesEnvironment *env) {
	auto left = conjunct(env);
	return disjunctext(env, std::move(left));
}

ast Parser::disjunctext(VariablesEnvironment *env, ast left) {
	BinaryOperator op;
	switch (currentToken.Type()) {
	case TokenType::boolOr:
		op = BinaryOperator::boolOr;
		break;
	default:
		return left;
	}
	currentToken = lexer.NextToken();
	auto leftNew = std::make_unique<BinOpASTNode>(std::move(left), conjunct(env), op);
	return disjunctext(env, std::move(leftNew));
}

ast Parser::conjunct(VariablesEnvironment *env) {
	auto left = equality(env);
	return conjunctext(env, std::move(left));
}

ast Parser::conjunctext(VariablesEnvironment *env, ast left) {
	BinaryOperator op;
	switch (currentToken.Type()) {
	case TokenType::boolAnd:
		op = BinaryOperator::boolAnd;
		break;
	default:
		return left;
	}
	currentToken = lexer.NextToken();
	auto leftNew = std::make_unique<BinOpASTNode>(std::move(left), equality(env), op);
	return conjunctext(env, std::move(leftNew));
}

ast Parser::equality(VariablesEnvironment *env) {
	auto left = relation(env);
	return equalityext(env, std::move(left));
}

ast Parser::equalityext(VariablesEnvironment *env, ast left) {
	BinaryOperator op;
	switch (currentToken.Type()) {
	case TokenType::eq:
		op = BinaryOperator::equals;
		break;
	case TokenType::ne:
		op = BinaryOperator::unEquals;
		break;
	default:
		return left;
	}
	currentToken = lexer.NextToken();
	auto leftNew = std::make_unique<BinOpASTNode>(std::move(left), relation(env), op);
	return equalityext(env, std::move(leftNew));
}

ast Parser::relation(VariablesEnvironment *env) {
	auto left = addsub(env);
	return relationext(env, std::move(left));
}

ast Parser::relationext(VariablesEnvironment *env, ast left) {
	BinaryOperator op;
	switch (currentToken.Type()) {
	case TokenType::lt:
		op = BinaryOperator::less;
		break;
	case TokenType::gt:
		op = BinaryOperator::greater;
		break;
	case TokenType::le:
		op = BinaryOperator::lessEquals;
		break;
	case TokenType::ge:
		op = BinaryOperator::greaterEquals;
		break;
	default:
		return left;
	}
	currentToken = lexer.NextToken();
	auto leftNew = std::make_unique<BinOpASTNode>(std::move(left), addsub(env), op);
	return relationext(env, std::move(leftNew));
}

ast Parser::addsub(VariablesEnvironment *env) {
	auto left = multdivmod(env);
	return addsubext(env, std::move(left));
}

ast Parser::addsubext(VariablesEnvironment *env, ast left) {
	BinaryOperator op;
	switch (currentToken.Type()) {
	case TokenType::add:
		op = BinaryOperator::add;
		break;
	case TokenType::sub:
		op = BinaryOperator::sub;
		break;
	default:
		return left;
	}
	currentToken = lexer.NextToken();
	auto leftNew = std::make_unique<BinOpASTNode>(std::move(left), multdivmod(env), op);
	return addsubext(env, std::move(leftNew));
}

ast Parser::multdivmod(VariablesEnvironment *env) {
	auto left = factor(env);
	return multdivmodext(env, std::move(left));
}

ast Parser::multdivmodext(VariablesEnvironment *env, ast left) {
	BinaryOperator op;
	switch (currentToken.Type()) {
		case TokenType::mult:
			op = BinaryOperator::mult;
			break;
		case TokenType::div:
			op = BinaryOperator::div;
			break;
		case TokenType::mod:
			op = BinaryOperator::mod;
			break;
		default:
			return left;
	}
	currentToken = lexer.NextToken();
	auto leftNew = std::make_unique<BinOpASTNode>(std::move(left), factor(env), op);
	return multdivmodext(env, std::move(leftNew));
}

ast Parser::factor(VariablesEnvironment *env) {
	if (currentToken.Type() == TokenType::intconst || currentToken.Type() == TokenType::identifier) {
		return literal(env);
	}
	else if (currentToken.Type() == TokenType::sub) {
		currentToken = lexer.NextToken();
		return std::make_unique<NegationASTNode>(literal(env));
	} else if(currentToken.Type() == TokenType::neg) {
		currentToken = lexer.NextToken();
		return std::make_unique<ComplementASTNode>(literal(env));
	} else if (currentToken.Type() == TokenType::lpar) {
		currentToken = lexer.NextToken();
		auto result = disjunct(env);
		if (currentToken.Type() != TokenType::rpar) {
			throw ParseException();
		}
		currentToken = lexer.NextToken();
		return result;
	}
	throw ParseException();
}

ast Parser::literal(VariablesEnvironment *env) {
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

ast Parser::if_statement(VariablesEnvironment *env) {
	if (currentToken.Type() == TokenType::if_ident) {
		currentToken = lexer.NextToken();
		auto condition = expression(env);
		auto thenBlock = statement(env);
		if (currentToken.Type() == TokenType::else_ident) {
			currentToken = lexer.NextToken();
			auto elseBlock = statement(env);
			return std::make_unique<IfElseASTNode>(std::move(condition), std::move(thenBlock), std::move(elseBlock));
		}
		return std::make_unique<IfASTNode>(std::move(condition), std::move(thenBlock));
	}
	throw ParseException();
}

ast Parser::while_statement(VariablesEnvironment *env) {
	if (currentToken.Type() == TokenType::while_ident) {
		currentToken = lexer.NextToken();
		auto condition = expression(env);
		auto body = statement(env);
		return std::make_unique<WhileASTNode>(std::move(condition), std::move(body));
	}
	throw ParseException();
}

ast Parser::declaration(VariablesEnvironment *env, unsigned int varid) {
	if (currentToken.Type() == TokenType::decl) {
		currentToken = lexer.NextToken();
		return std::make_unique<DeclarationASTNode>(varid, expression(env));
	}
	throw ParseException();
}

ast Parser::assignment(VariablesEnvironment *env, unsigned int varid) {
	if (currentToken.Type() == TokenType::assign) {
		currentToken = lexer.NextToken();
		return std::make_unique<AssignmentASTNode>(varid, expression(env));
	}
	throw ParseException();
}