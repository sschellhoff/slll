#include "Function.h"

using namespace slll;

Function::Function(std::string name, unsigned int paramCount):name(name), numParams(paramCount) {
}


Function::~Function() {
}

unsigned int Function::GetParameterCount()const {
	return numParams;
}

const std::string &Function::Name()const {
	return name;
}