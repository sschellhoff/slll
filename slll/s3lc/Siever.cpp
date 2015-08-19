#include "Siever.h"

using namespace slll;

Siever::Siever(std::string sourcecode):scanner(sourcecode), buffer(TokenType::error), bufferUsed(false)
{
}


Siever::~Siever()
{
}

slll::Siever::Siever(Siever && s) :scanner(std::move(s.scanner)), buffer(s.buffer) {
}

Token slll::Siever::NextToken()
{
	if (bufferUsed) {
		bufferUsed = false;
		return buffer;
	}
	Token t = scanner.NextToken();
	/*
	while t.Type() == TokenType::error {
		put errors together
	}
	put next token after errors in buffer if there were errors
	set bufferUsed to true
	*/
	return t;
}
