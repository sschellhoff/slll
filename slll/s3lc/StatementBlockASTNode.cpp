#include "StatementBlockASTNode.h"
#include "IVisitor.h"

using namespace slll;

StatementBlockASTNode::StatementBlockASTNode(slll::VariablesEnvironment *parentEnvironment):environment(std::make_unique<slll::VariablesEnvironment>(parentEnvironment))
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

const std::list<std::unique_ptr<IAST>> *StatementBlockASTNode::Children() const {
	return &children;
}

VariablesEnvironment *StatementBlockASTNode::VariablesEnvironment() const {
	return environment.get();
}