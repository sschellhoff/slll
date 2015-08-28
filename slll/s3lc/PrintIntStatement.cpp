#include "PrintIntStatementASTNode.h"
#include "IVisitor.h"

using namespace slll;

PrintIntStatementASTNode::PrintIntStatementASTNode(ast expression):expression(std::move(expression))
{
}


PrintIntStatementASTNode::~PrintIntStatementASTNode()
{
}

PrintIntStatementASTNode::PrintIntStatementASTNode(PrintIntStatementASTNode &&n) {
	expression = std::move(n.expression);
}

IAST *PrintIntStatementASTNode::Expression()const {
	return expression.get();
}

void PrintIntStatementASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}