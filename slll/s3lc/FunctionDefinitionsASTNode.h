#pragma once

#include <list>
#include <memory>
#include "IAST.h"
#include "FunctionsEnvironment.h"

namespace slll {

	class FunctionDefinitionsASTNode : public IAST
	{
	private:
		std::unique_ptr<FunctionsEnvironment> environment;
		std::list<ast> children;
	public:
		FunctionDefinitionsASTNode();
		~FunctionDefinitionsASTNode();
		FunctionDefinitionsASTNode(const FunctionDefinitionsASTNode &n) = delete;
		FunctionDefinitionsASTNode(FunctionDefinitionsASTNode &&n);
		void AcceptVisitor(IVisitor *visitor);
		void Add(std::unique_ptr<IAST> child);
		const std::list<std::unique_ptr<IAST>> *Children() const;
		FunctionsEnvironment *Environment() const;
	};

}