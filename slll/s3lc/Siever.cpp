#include "Siever.h"

using namespace slll;

Siever::Siever(std::string sourcecode):scanner(sourcecode) {
}


Siever::~Siever() {
}

slll::Siever::Siever(Siever && s) :scanner(std::move(s.scanner)) {
}

Token slll::Siever::NextToken() {
	return scanner.NextToken();
}
