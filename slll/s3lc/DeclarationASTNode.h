#pragma once

#include <memory>

#include "IAST.h"

namespace slll {

	class DeclarationASTNode : public IAST
	{
	private:
		unsigned int variable_id;
		ast expression;
	public:
		DeclarationASTNode(unsigned int variable_id, ast expression);
		~DeclarationASTNode();
		DeclarationASTNode(const DeclarationASTNode &r) = delete;
		DeclarationASTNode(DeclarationASTNode &&n);
		unsigned int VariableId()const;
		IAST *Expression()const;
		void AcceptVisitor(IVisitor *visitor);
	};

}