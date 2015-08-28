#pragma once

#include <memory>

#include "IAST.h"
#include "BinaryOperator.h"

namespace slll {

	class BinOpASTNode : public IAST
	{
	private:
		ast left;
		ast right;
		BinaryOperator op;
	public:
		BinOpASTNode(ast left, ast right, BinaryOperator op);
		~BinOpASTNode();
		BinOpASTNode(const BinOpASTNode &r) = delete;
		BinOpASTNode(BinOpASTNode &&n);
		IAST *Left()const;
		IAST *Right()const;
		BinaryOperator Op()const;
		void AcceptVisitor(IVisitor *visitor);
	};

}