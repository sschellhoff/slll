#include "VariableASTNode.h"

using namespace slll;

VariableASTNode::VariableASTNode(unsigned int variable_id):variable_id(variable_id)
{
}


VariableASTNode::~VariableASTNode()
{
}

VariableASTNode::VariableASTNode(VariableASTNode &&n) {
	variable_id = n.variable_id;
}

unsigned int slll::VariableASTNode::Variable() const
{
	return variable_id;
}

void VariableASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}