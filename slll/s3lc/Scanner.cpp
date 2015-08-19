#include "Scanner.h"

#include <ctype.h>

using namespace slll;

Scanner::Scanner(std::string sourcecode):sourcecode(sourcecode), pointer(0)
{
}

Scanner::~Scanner()
{
}

Token Scanner::NextToken()
{
	while (pointer < sourcecode.length() && isspace(sourcecode[pointer])) {
		pointer++;
	}
	if (pointer >= sourcecode.length()) {
		return Token(TokenType::eof, "");
	}
	if (pointer + 1 < sourcecode.length() && sourcecode[pointer] == '/' && sourcecode[pointer + 1] == '/') {
		while (pointer < sourcecode.length() && sourcecode[pointer] != '\n') {
			pointer++;
		}
		return NextToken();
	}
	if (pointer + 1 < sourcecode.length() && sourcecode[pointer] == '/' && sourcecode[pointer + 1] == '*') {
		pointer += 2;
		while (pointer < sourcecode.length()) {
			if (pointer + 1 >= sourcecode.length()) {
				return Token(TokenType::error, "missing command end");
			}
			if (sourcecode[pointer] == '*' && sourcecode[pointer + 1] == '/') {
				pointer += 2;
				return NextToken();
			}
			pointer++;
		}
	}
	if (isdigit(sourcecode[pointer])) {
		int v = sourcecode[pointer] - '0';
		pointer++;
		while (pointer < sourcecode.length() && isdigit(sourcecode[pointer])) {
			v *= 10;
			v += sourcecode[pointer] - '0';
			pointer++;
		}
		return Token(TokenType::intconst, std::to_string(v));
	}
	if (isalpha(sourcecode[pointer])) {
		int start = pointer;
		pointer++;
		while (pointer < sourcecode.length() && isalnum(sourcecode[pointer])) {
			pointer++;
		}
		return Token(TokenType::identifier, sourcecode.substr(start, pointer - start));
	}
	switch (sourcecode[pointer++]) {
	case '+':
		return Token(TokenType::add, "");
	case '-':
		return Token(TokenType::sub, "");
	case '*':
		return Token(TokenType::mult, "");
	case '/':
		return Token(TokenType::div, "");
	case '%':
		return Token(TokenType::mod, "");
	case '=':
		if (pointer < sourcecode.length() && sourcecode[pointer] == '=') {
			pointer++;
			return Token(TokenType::eq, "");
		}
		return Token(TokenType::assign, "");
	case '!':
		if (pointer < sourcecode.length() && sourcecode[pointer] == '=') {
			pointer++;
			return Token(TokenType::ne, "");
		}
		return Token(TokenType::neg, "");
	case '(':
		return Token(TokenType::lpar, "");
	case ')':
		return Token(TokenType::rpar, "");
	case '{':
		return Token(TokenType::lbra, "");
	case '}':
		return Token(TokenType::rbra, "");
	case ';':
		return Token(TokenType::sep, "");
	case ',':
		return Token(TokenType::opsep, "");
	case '<':
		if (pointer < sourcecode.length() && sourcecode[pointer] == '=') {
			pointer++;
			return Token(TokenType::le, "");
		}
		return Token(TokenType::lt, "");
	case '>':
		if (pointer < sourcecode.length() && sourcecode[pointer] == '=') {
			pointer++;
			return Token(TokenType::ge, "");
		}
		return Token(TokenType::gt, "");
	case ':':
		if (pointer < sourcecode.length() && sourcecode[pointer] == '=') {
			pointer++;
			return Token(TokenType::decl, "");
		}
		return Token(TokenType::error, "wrong lexical value");
	default:
		return Token(TokenType::error, "wrong lexical value");
	}

	return Token(TokenType::error, "unknown lexical value");
}