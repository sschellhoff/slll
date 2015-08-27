#pragma once
#include <memory>

#include "IAST.h"

namespace slll {

	class WhileASTNode : public IAST
	{
	private:
		ast condition;
		ast body;
	public:
		WhileASTNode(ast condition, ast body);
		~WhileASTNode();
		WhileASTNode(const WhileASTNode &r) = delete;
		WhileASTNode(WhileASTNode &&n);
		IAST *Condition()const;
		IAST *Body()const;
		void AcceptVisitor(IVisitor *visitor);
	};

}