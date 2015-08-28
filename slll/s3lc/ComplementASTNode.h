#pragma once

#include "IAST.h"

namespace slll {

	class ComplementASTNode : public IAST
	{
	private:
		ast expression;
	public:
		ComplementASTNode(ast expression);
		~ComplementASTNode();
		ComplementASTNode(const ComplementASTNode &n) = delete;
		ComplementASTNode(ComplementASTNode &&n);
		IAST *Expression()const;
		void AcceptVisitor(IVisitor *visitor);
	};

}