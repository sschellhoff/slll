#pragma once

#include <memory>

#include "IAST.h"

namespace slll {

	class AssignmentASTNode : public IAST
	{
	private:
		unsigned int variable_id;
		ast expression;
	public:
		AssignmentASTNode(unsigned int variable_id, ast expression);
		~AssignmentASTNode();
		AssignmentASTNode(const AssignmentASTNode &r) = delete;
		AssignmentASTNode(AssignmentASTNode &&n);
		unsigned int VariableId()const;
		IAST *Expression()const;
		void AcceptVisitor(IVisitor *visitor);
	};

}