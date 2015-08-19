#include <iostream>

#include "Siever.h"
#include "Parser.h"

int main(int argc, const char *argv[]) {

	slll::Siever lexer("");

	slll::Token t(slll::error, "");
	while ((t = lexer.NextToken()).Type() != slll::TokenType::eof) {
		std::cout << t.Type() << std::endl;
	}

	slll::Parser p(slll::Siever("1+2+3"));

	std::system("pause");
	return 0;
}