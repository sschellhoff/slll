#include "PrintNewLineStatementASTNode.h"
#include "IVisitor.h"

using namespace slll;

PrintNewLineStatementASTNode::PrintNewLineStatementASTNode()
{
}


PrintNewLineStatementASTNode::~PrintNewLineStatementASTNode()
{
}

void PrintNewLineStatementASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}