#pragma once

#include "IAST.h"

namespace slll {

	class NegationASTNode : public IAST
	{
	private:
		ast expression;
	public:
		NegationASTNode(ast expression);
		~NegationASTNode();
		NegationASTNode(const NegationASTNode &n) = delete;
		NegationASTNode(NegationASTNode &&n);
		IAST *Expression()const;
		void AcceptVisitor(IVisitor *visitor);
	};

}