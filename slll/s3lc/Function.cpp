#include "Function.h"

using namespace slll;

Function::Function(std::string name):name(name) {
}


Function::~Function() {
}

size_t Function::GetParameterCount()const {
	return parameters.size();
}

const std::string &Function::Name()const {
	return name;
}