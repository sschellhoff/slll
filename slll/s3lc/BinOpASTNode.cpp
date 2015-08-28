#include "BinOpASTNode.h"
#include "IVisitor.h"

using namespace slll;

BinOpASTNode::BinOpASTNode(ast left, ast right, BinaryOperator op): left(std::move(left)), right(std::move(right)), op(op)
{
}


BinOpASTNode::~BinOpASTNode()
{
}

BinOpASTNode::BinOpASTNode(BinOpASTNode &&n) {
	left = std::move(n.left);
	right = std::move(n.right);
	op = n.op;
}

IAST *BinOpASTNode::Left() const
{
	return left.get();
}

IAST * slll::BinOpASTNode::Right() const
{
	return right.get();
}

BinaryOperator slll::BinOpASTNode::Op() const
{
	return op;
}

void BinOpASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}