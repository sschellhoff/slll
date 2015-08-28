#pragma once

#include "IAST.h"
#include "VariablesEnvironment.h"
#include <memory>
#include <list>

namespace slll {

	class StatementBlockASTNode: public IAST
	{
	private:
		std::unique_ptr<VariablesEnvironment> environment;
		std::list<ast> children;
	public:
		StatementBlockASTNode(VariablesEnvironment *parentEnvironment);
		~StatementBlockASTNode();
		StatementBlockASTNode(const StatementBlockASTNode &n) = delete;
		StatementBlockASTNode(StatementBlockASTNode &&n);
		void AcceptVisitor(IVisitor *visitor);
		void Add(std::unique_ptr<IAST> child);
		const std::list<std::unique_ptr<IAST>> *Children() const;
		VariablesEnvironment *VariablesEnvironment() const;
	};

}