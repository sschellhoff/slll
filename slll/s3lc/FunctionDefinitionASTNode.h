#pragma once

#include "IAST.h"
#include "Function.h"

namespace slll {

	class FunctionDefinitionASTNode : public IAST
	{
	private:
		Function function;
		ast code;
	public:
		FunctionDefinitionASTNode(Function function, ast code);
		~FunctionDefinitionASTNode();
		FunctionDefinitionASTNode(const FunctionDefinitionASTNode &n) = delete;
		FunctionDefinitionASTNode(FunctionDefinitionASTNode &&n);
		void AcceptVisitor(IVisitor *visitor);
		const std::string &Name()const;
		IAST *Code()const;
	};

}