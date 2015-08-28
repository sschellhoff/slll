#pragma once

#include <vector>

#include "Function.h"

namespace slll {

	class FunctionsEnvironment
	{
	private:
		std::vector<Function> functions;
	public:
		FunctionsEnvironment();
		~FunctionsEnvironment();
		void AddDefinition(Function func);
	};

}