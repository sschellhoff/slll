#include "ComplementASTNode.h"
#include "IVisitor.h"

using namespace slll;

ComplementASTNode::ComplementASTNode(ast expression) :expression(std::move(expression))
{
}


ComplementASTNode::~ComplementASTNode()
{
}

ComplementASTNode::ComplementASTNode(ComplementASTNode &&n) {
	expression = std::move(n.expression);
}

IAST *ComplementASTNode::Expression()const {
	return expression.get();
}

void ComplementASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}
