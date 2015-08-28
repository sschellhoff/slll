#include "NegationASTNode.h"
#include "IVisitor.h"

using namespace slll;

NegationASTNode::NegationASTNode(ast expression):expression(std::move(expression))
{
}


NegationASTNode::~NegationASTNode()
{
}

NegationASTNode::NegationASTNode(NegationASTNode &&n) {
	expression = std::move(n.expression);
}

IAST *NegationASTNode::Expression()const {
	return expression.get();
}

void NegationASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}
