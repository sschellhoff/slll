#include "ReturnASTNode.h"

#include "IVisitor.h"

using namespace slll;

ReturnASTNode::ReturnASTNode(slll::VariablesEnvironment *varEnvironment) : varEnvironment(varEnvironment), hasResult(false)
{
}

ReturnASTNode::ReturnASTNode(slll::VariablesEnvironment *varEnvironment, ast result) : varEnvironment(varEnvironment), result(std::move(result)), hasResult(true)
{
}


ReturnASTNode::~ReturnASTNode()
{
}

bool ReturnASTNode::HasResult()const {
	return hasResult;
}

ReturnASTNode::ReturnASTNode(ReturnASTNode &&n):result(std::move(n.result)), hasResult(n.hasResult) {
}

IAST *ReturnASTNode::Result()const {
	return result.get();
}

void ReturnASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}

VariablesEnvironment *ReturnASTNode::VariablesEnvironment()const {
	return varEnvironment;
}