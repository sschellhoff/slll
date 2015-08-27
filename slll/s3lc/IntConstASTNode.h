#pragma once

#include "IAST.h"

namespace slll {

	class IntConstASTNode : public IAST
	{
	private:
		int value;
	public:
		IntConstASTNode(int val);
		~IntConstASTNode();
		IntConstASTNode(const IntConstASTNode &n) = delete;
		IntConstASTNode(IntConstASTNode &&n);
		int Value()const;
		void AcceptVisitor(IVisitor *visitor);
	};

}