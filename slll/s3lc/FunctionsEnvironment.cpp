#include "FunctionsEnvironment.h"
#include "FunctionRedefinitionException.h"

using namespace slll;

FunctionsEnvironment::FunctionsEnvironment()
{
}


FunctionsEnvironment::~FunctionsEnvironment()
{
}

void FunctionsEnvironment::AddDefinition(Function func) {
	for (auto &f : functions) {
		if (f.Name() == func.Name()) {
			if (f.GetParameterCount() == func.GetParameterCount()) {
				return;
			} else {
				throw FunctionRedefinitionException();
			}
		}
	}
	functions.push_back(func);
}