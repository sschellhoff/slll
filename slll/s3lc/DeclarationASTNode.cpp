#include "DeclarationASTNode.h"
#include "IVisitor.h"

using namespace slll;

DeclarationASTNode::DeclarationASTNode(unsigned int variable_id, ast expression):variable_id(variable_id), expression(std::move(expression))
{
}


DeclarationASTNode::~DeclarationASTNode()
{
}

DeclarationASTNode::DeclarationASTNode(DeclarationASTNode &&n) {
	variable_id = n.variable_id;
	expression = std::move(n.expression);
}

unsigned int DeclarationASTNode::VariableId()const {
	return variable_id;
}

IAST *DeclarationASTNode::Expression()const {
	return expression.get();
}

void DeclarationASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}