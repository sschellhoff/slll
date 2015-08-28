#pragma once

#include "IAST.h"

namespace slll {

	class FunctionDefinitionASTNode : public IAST
	{
	public:
		FunctionDefinitionASTNode();
		~FunctionDefinitionASTNode();
		FunctionDefinitionASTNode(const FunctionDefinitionASTNode &n) = delete;
		FunctionDefinitionASTNode(FunctionDefinitionASTNode &&n);
	};

}