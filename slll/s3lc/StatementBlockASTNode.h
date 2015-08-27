#pragma once

#include "IAST.h"
#include "Environment.h"
#include <memory>
#include <vector>

namespace slll {

	class StatementBlockASTNode: public IAST
	{
	private:
		std::unique_ptr<Environment> environment;
		std::vector<std::unique_ptr<IAST>> children;
	public:
		StatementBlockASTNode(Environment *parentEnvironment);
		~StatementBlockASTNode();
		StatementBlockASTNode(const StatementBlockASTNode &n) = delete;
		StatementBlockASTNode(StatementBlockASTNode &&n);
		void AcceptVisitor(IVisitor *visitor);
		void Add(std::unique_ptr<IAST> child);
		const std::vector<std::unique_ptr<IAST>> *Children() const;
		Environment *Environment() const;
	};

}