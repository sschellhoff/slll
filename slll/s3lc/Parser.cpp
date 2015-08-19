#include "Parser.h"

using namespace slll;

Parser::Parser(std::string sourcecode) :lexer(sourcecode) {
}

Parser::Parser(Siever &&lexer):lexer(std::move(lexer)) {
}

Parser::~Parser() {
}

void Parser::Parse() {
}