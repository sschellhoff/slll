#include "AssignmentASTNode.h"
#include "IVisitor.h"

using namespace slll;

AssignmentASTNode::AssignmentASTNode(unsigned int variable_id, ast expression) :variable_id(variable_id), expression(std::move(expression))
{
}


AssignmentASTNode::~AssignmentASTNode()
{
}

AssignmentASTNode::AssignmentASTNode(AssignmentASTNode &&n) {
	variable_id = n.variable_id;
	expression = std::move(n.expression);
}

unsigned int AssignmentASTNode::VariableId()const {
	return variable_id;
}

IAST *AssignmentASTNode::Expression()const {
	return expression.get();
}

void AssignmentASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}