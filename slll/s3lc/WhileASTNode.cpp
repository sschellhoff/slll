#include "WhileASTNode.h"
#include "IVisitor.h"

using namespace slll;

WhileASTNode::WhileASTNode(ast condition, ast body) :condition(std::move(condition)), body(std::move(body))
{
}


WhileASTNode::~WhileASTNode()
{
}

WhileASTNode::WhileASTNode(WhileASTNode &&n) {
	n.condition = std::move(this->condition);
	n.body = std::move(this->body);
}

IAST *WhileASTNode::Condition()const {
	return condition.get();
}

IAST *WhileASTNode::Body()const {
	return body.get();
}

void WhileASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}