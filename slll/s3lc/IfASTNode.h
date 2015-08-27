#pragma once
#include <memory>

#include "IAST.h"

namespace slll {

	class IfASTNode : public IAST
	{
	private:
		ast condition;
		ast thenBody;
	public:
		IfASTNode(ast condition, ast thenBody);
		~IfASTNode();
		IfASTNode(const IfASTNode &r) = delete;
		IfASTNode(IfASTNode &&n);
		IAST *Condition()const;
		IAST *ThenBody()const;
		void AcceptVisitor(IVisitor *visitor);
	};

}