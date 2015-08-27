#pragma once

#include "IAST.h"

namespace slll {

	class PrintNewLineStatementASTNode : public IAST
	{
	public:
		PrintNewLineStatementASTNode();
		~PrintNewLineStatementASTNode();
		void AcceptVisitor(IVisitor *visitor);
	};

}