#include "BinOpASTNode.h"

using namespace slll;

BinOpASTNode::BinOpASTNode(ast left, ast right): left(std::move(left)), right(std::move(right))
{
}


BinOpASTNode::~BinOpASTNode()
{
}
