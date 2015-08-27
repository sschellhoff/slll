#include "IfASTNode.h"
#include "IVisitor.h"

using namespace slll;

IfASTNode::IfASTNode(ast condition, ast thenBody):condition(std::move(condition)), thenBody(std::move(thenBody))
{
}


IfASTNode::~IfASTNode()
{
}

IfASTNode::IfASTNode(IfASTNode &&n) {
	n.condition = std::move(this->condition);
	n.thenBody = std::move(this->thenBody);
}

IAST *IfASTNode::Condition()const {
	return condition.get();
}

IAST *IfASTNode::ThenBody()const {
	return thenBody.get();
}

void IfASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}