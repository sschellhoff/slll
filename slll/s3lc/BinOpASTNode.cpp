#include "BinOpASTNode.h"
#include "IVisitor.h"

using namespace slll;

BinOpASTNode::BinOpASTNode(ast left, ast right, TokenType op): left(std::move(left)), right(std::move(right)), op(op)
{
}


BinOpASTNode::~BinOpASTNode()
{
}

BinOpASTNode::BinOpASTNode(BinOpASTNode &&n) {
	n.left = std::move(this->left);
	n.right = std::move(this->right);
	n.op = this->op;
}

IAST *BinOpASTNode::Left() const
{
	return left.get();
}

IAST * slll::BinOpASTNode::Right() const
{
	return right.get();
}

TokenType slll::BinOpASTNode::Op() const
{
	return op;
}

void BinOpASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}