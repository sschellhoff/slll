#include "StatementBlockASTNode.h"
#include "IVisitor.h"

using namespace slll;

StatementBlockASTNode::StatementBlockASTNode(slll::Environment *parentEnvironment):environment(std::make_unique<slll::Environment>(parentEnvironment))
{
}


StatementBlockASTNode::~StatementBlockASTNode()
{
}


StatementBlockASTNode::StatementBlockASTNode(StatementBlockASTNode &&n) {
	environment = std::move(n.environment);
	children = std::move(n.children);
}

void StatementBlockASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}

void StatementBlockASTNode::Add(std::unique_ptr<IAST> child) {
	children.push_back(std::move(child));
}

const std::vector<std::unique_ptr<IAST>> *StatementBlockASTNode::Children() const {
	return &children;
}

Environment *StatementBlockASTNode::Environment() const {
	return environment.get();
}