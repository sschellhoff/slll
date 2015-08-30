#pragma once

#include "IAST.h"
#include "Function.h"
#include "VariablesEnvironment.h"

namespace slll {

	class FunctionDefinitionASTNode : public IAST
	{
	private:
		Function function;
		ast code;
		std::unique_ptr<VariablesEnvironment> parametersEnvironment;
	public:
		FunctionDefinitionASTNode(Function function, ast code);
		FunctionDefinitionASTNode(Function function, ast code, std::unique_ptr<VariablesEnvironment> parametersEnvironment);
		~FunctionDefinitionASTNode();
		FunctionDefinitionASTNode(const FunctionDefinitionASTNode &n) = delete;
		FunctionDefinitionASTNode(FunctionDefinitionASTNode &&n);
		void AcceptVisitor(IVisitor *visitor);
		const std::string &Name()const;
		IAST *Code()const;
		VariablesEnvironment *GetParametersEnvironment()const;
	};

}