#include "Token.h"

using namespace slll;

Token::Token(TokenType type):type(type), value("") {
}

Token::Token(TokenType type, std::string value):type(type), value(value)
{
}

Token::~Token()
{
}

TokenType Token::Type() const
{
	return type;
}

const std::string & Token::Value() const
{
	return value;
}

/*std::ostream & slll::operator<<(std::ostream & stream, const Token & token)
{
	stream << "(" << token.Type() << ", " << token.Value() << ")";
	return stream;
}*/
