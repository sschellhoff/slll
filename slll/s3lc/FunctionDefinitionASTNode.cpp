#include "FunctionDefinitionASTNode.h"

#include "IVisitor.h"

using namespace slll;

FunctionDefinitionASTNode::FunctionDefinitionASTNode(Function function, ast code):function(function), code(std::move(code)) {
}

FunctionDefinitionASTNode::FunctionDefinitionASTNode(Function function, ast code, std::unique_ptr<VariablesEnvironment> parametersEnvironment) : function(function), code(std::move(code)), parametersEnvironment(std::move(parametersEnvironment)) {
}

FunctionDefinitionASTNode::~FunctionDefinitionASTNode() {
}

FunctionDefinitionASTNode::FunctionDefinitionASTNode(FunctionDefinitionASTNode &&n):function(n.function), code(std::move(n.code)) {
}

void FunctionDefinitionASTNode::AcceptVisitor(IVisitor *visitor) {
	visitor->Visit(this);
}

const std::string &FunctionDefinitionASTNode::Name()const {
	return function.Name();
}

IAST *FunctionDefinitionASTNode::Code()const {
	return code.get();
}

VariablesEnvironment *FunctionDefinitionASTNode::GetParametersEnvironment()const {
	return parametersEnvironment.get();
}