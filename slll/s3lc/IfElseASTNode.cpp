#include "IfElseASTNode.h"
#include "IVisitor.h"

using namespace slll;

IfElseASTNode::IfElseASTNode(ast condition, ast thenBody, ast elseBody) :condition(std::move(condition)), thenBody(std::move(thenBody)), elseBody(std::move(elseBody))
{
}


IfElseASTNode::~IfElseASTNode()
{
}

IfElseASTNode::IfElseASTNode(IfElseASTNode &&n) {
	n.condition = std::move(this->condition);
	n.thenBody = std::move(this->thenBody);
	n.elseBody = std::move(this->elseBody);
}

IAST *IfElseASTNode::Condition()const {
	return condition.get();
}

IAST *IfElseASTNode::ThenBody()const {
	return thenBody.get();
}

IAST *IfElseASTNode::ElseBody()const {
	return elseBody.get();
}

void IfElseASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}