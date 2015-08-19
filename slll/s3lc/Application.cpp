#include <iostream>
#include "Siever.h"

int main(int argc, const char *argv[]) {

	auto lexer = slll::Siever("");

	slll::Token t(slll::error, "");
	while ((t = lexer.NextToken()).Type() != slll::TokenType::eof) {
		std::cout << t.Type() << std::endl;
	}

	std::system("pause");
	return 0;
}