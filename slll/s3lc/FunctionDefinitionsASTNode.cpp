#include "FunctionDefinitionsASTNode.h"
#include "IVisitor.h"

using namespace slll;

FunctionDefinitionsASTNode::FunctionDefinitionsASTNode():environment(std::make_unique<FunctionsEnvironment>())
{
}


FunctionDefinitionsASTNode::~FunctionDefinitionsASTNode()
{
}

FunctionDefinitionsASTNode::FunctionDefinitionsASTNode(FunctionDefinitionsASTNode &&n) {
	children = std::move(n.children);
}

void FunctionDefinitionsASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}

void FunctionDefinitionsASTNode::Add(std::unique_ptr<IAST> child) {
	children.push_back(std::move(child));
}

const std::list<std::unique_ptr<IAST>> *FunctionDefinitionsASTNode::Children() const {
	return &children;
}

FunctionsEnvironment *FunctionDefinitionsASTNode::Environment() const {
	return environment.get();
}