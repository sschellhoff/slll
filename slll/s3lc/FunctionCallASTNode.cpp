#include "FunctionCallASTNode.h"

#include "IVisitor.h"

using namespace slll;

FunctionCallASTNode::FunctionCallASTNode(std::string name):name(name)
{
}


FunctionCallASTNode::~FunctionCallASTNode()
{
}

FunctionCallASTNode::FunctionCallASTNode(FunctionCallASTNode &&n):name(n.name) {
}

const std::string &FunctionCallASTNode::Name()const {
	return name;
}

void FunctionCallASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}
