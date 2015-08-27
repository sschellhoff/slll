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
	n.variable_id = variable_id;
	n.expression = std::move(expression);
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