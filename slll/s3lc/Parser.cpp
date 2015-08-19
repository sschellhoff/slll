#include "Parser.h"
#include "IntConstASTNode.h"
#include "BinOpASTNode.h"
#include "ParseException.h"

using namespace slll;

Parser::Parser(std::string sourcecode) :lexer(sourcecode), currentToken(lexer.NextToken()) {
}

Parser::~Parser() {
}

ast Parser::Parse() {
	auto result{ expression() };
	if (currentToken.Type() != TokenType::eof) {
		throw ParseException();
	}
	return result;
}

ast Parser::expression() {
	auto left = factor();
	return expressionext(std::move(left));
}

ast Parser::expressionext(ast left) {
	switch (currentToken.Type()) {
	case TokenType::add:
	case TokenType::sub:
	case TokenType::mult:
	case TokenType::div:
	case TokenType::mod:
		currentToken = lexer.NextToken();
		return std::make_unique<BinOpASTNode>(std::move(left), factor());
	case TokenType::eof:
		return left;
	}
	throw ParseException();
}

ast Parser::factor() {
	if (currentToken.Type() == TokenType::intconst) {
		currentToken = lexer.NextToken();
		return std::make_unique<IntConstASTNode>();
	}
	throw ParseException();
}