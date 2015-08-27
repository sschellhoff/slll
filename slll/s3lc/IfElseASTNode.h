#pragma once
#include <memory>

#include "IAST.h"

namespace slll {

	class IfElseASTNode : public IAST
	{
	private:
		ast condition;
		ast thenBody;
		ast elseBody;
	public:
		IfElseASTNode(ast condition, ast thenBody, ast elseBody);
		~IfElseASTNode();
		IfElseASTNode(const IfElseASTNode &r) = delete;
		IfElseASTNode(IfElseASTNode &&n);
		IAST *Condition()const;
		IAST *ThenBody()const;
		IAST *ElseBody()const;
		void AcceptVisitor(IVisitor *visitor);
	};

}