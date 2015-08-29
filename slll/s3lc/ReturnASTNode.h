#pragma once

#include "IAST.h"

#include "VariablesEnvironment.h"

namespace slll {

	class ReturnASTNode : public IAST
	{
	private:
		ast result;
		bool hasResult;
		VariablesEnvironment *varEnvironment;
	public:
		ReturnASTNode(VariablesEnvironment *varEnvironment);
		ReturnASTNode(VariablesEnvironment *varEnvironment, ast result);
		~ReturnASTNode();
		ReturnASTNode(const ReturnASTNode &n) = delete;
		ReturnASTNode(ReturnASTNode &&n);
		IAST *Result()const;
		void AcceptVisitor(IVisitor *visitor);
		bool HasResult()const;
		VariablesEnvironment *VariablesEnvironment()const;
	};

}