#include <iostream>

#include "Siever.h"
#include "Parser.h"

int main(int argc, const char *argv[]) {

	slll::Siever lexer("1+2");

	slll::Token t(slll::error, "");
	while ((t = lexer.NextToken()).Type() != slll::TokenType::eof) {
		std::cout << t.Type() << std::endl;
	}

	slll::Parser p("1+2");
	p.Parse();
	std::system("pause");
	return 0;
}