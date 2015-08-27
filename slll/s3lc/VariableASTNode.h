#pragma once
#include "IAST.h"
#include "IVisitor.h"

namespace slll {

	class VariableASTNode : public IAST
	{
	private:
		unsigned int variable_id;
	public:
		VariableASTNode(unsigned int variable_id);
		~VariableASTNode();
		VariableASTNode(const VariableASTNode &n) = delete;
		VariableASTNode(VariableASTNode &&n);
		unsigned int Variable()const;
		void AcceptVisitor(IVisitor *visitor);
	};

}