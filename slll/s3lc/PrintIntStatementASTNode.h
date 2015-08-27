#pragma once

#include "IAST.h"

namespace slll {

	class PrintIntStatementASTNode : public IAST
	{
	private:
		ast expression;
	public:
		PrintIntStatementASTNode(ast expression);
		~PrintIntStatementASTNode();
		IAST *Expression()const;
		void AcceptVisitor(IVisitor *visitor);
	};

}