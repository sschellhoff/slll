#include "IntConstASTNode.h"
#include "IVisitor.h"

using namespace slll;

IntConstASTNode::IntConstASTNode(int val)
{
	value = val;
}

IntConstASTNode::~IntConstASTNode()
{
}

IntConstASTNode::IntConstASTNode(IntConstASTNode &&n) {
	n.value = this->value;
}

int slll::IntConstASTNode::Value() const
{
	return value;
}

void IntConstASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}