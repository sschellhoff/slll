#pragma once

#include <memory>

#include "IAST.h"
#include "TokenType.h"

namespace slll {

	class BinOpASTNode : public IAST
	{
	private:
		ast left;
		ast right;
		TokenType op;
	public:
		BinOpASTNode(ast left, ast right, TokenType op);
		~BinOpASTNode();
		BinOpASTNode(const BinOpASTNode &r) = delete;
		BinOpASTNode(BinOpASTNode &&n);
		IAST *Left()const;
		IAST *Right()const;
		TokenType Op()const;
		void AcceptVisitor(IVisitor *visitor);
	};

}