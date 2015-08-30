#include "FunctionCallASTNode.h"

#include "IVisitor.h"

using namespace slll;

FunctionCallASTNode::FunctionCallASTNode(std::string name):name(name)
{
}

FunctionCallASTNode::FunctionCallASTNode(std::string name, std::vector<std::unique_ptr<IAST>> &parameters):name(name), parameters(std::move(parameters)) {
	//this->parameters = std::move(parameters);
}

FunctionCallASTNode::~FunctionCallASTNode()
{
}

FunctionCallASTNode::FunctionCallASTNode(FunctionCallASTNode &&n):name(n.name) {
}

const std::string &FunctionCallASTNode::Name()const {
	return name;
}

const std::vector<std::unique_ptr<IAST>> *FunctionCallASTNode::GetParameters()const {
	return &parameters;
}

void FunctionCallASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}
