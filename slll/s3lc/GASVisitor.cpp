#include "GASVisitor.h"

#include <sstream>

#include "UnknownOperatorException.h"

#include "IntConstASTNode.h"
#include "BinOpASTNode.h"
#include "StatementBlockASTNode.h"
#include "DeclarationASTNode.h"
#include "AssignmentASTNode.h"
#include "VariableASTNode.h"
#include "NegationASTNode.h"
#include "IfASTNode.h"
#include "IfElseASTNode.h"
#include "WhileASTNode.h"
#include "ComplementASTNode.h"
#include "FunctionDefinitionASTNode.h"
#include "FunctionDefinitionsASTNode.h"
#include "FunctionCallASTNode.h"
#include "ReturnASTNode.h"

using namespace slll;

GASVisitor::GASVisitor(std::ostream &out):out(out)
{
}


GASVisitor::~GASVisitor()
{
}

std::string GASVisitor::NewMarker() {
	std::stringstream ss;
	ss << "M" << nextMarkerId++;
	return ss.str();
}

void GASVisitor::Visit(const IntConstASTNode * node)
{
	int n = node->Value();
	out << "movl $" << node->Value() << ", %eax" << std::endl;
}

void GASVisitor::Visit(const BinOpASTNode * node)
{
	auto op = node->Op();
	node->Left()->AcceptVisitor(this);
	switch (op) {
	case BinaryOperator::add:
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "addl (%esp), %eax" << std::endl
			<< "addl $4, %esp" << std::endl;
		break;
	case BinaryOperator::sub:
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "subl %eax, (%esp)" << std::endl
			<< "pop %eax" << std::endl;
		break;
	case BinaryOperator::mult:
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "imull (%esp), %eax" << std::endl
			<< "addl $4, %esp" << std::endl;
		break;
	case BinaryOperator::div:
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "movl %eax, %ebx" << std::endl
			<< "pop %eax" << std::endl
			<< "movl $0, %edx" << std::endl
			<< "idiv %ebx" << std::endl;
		break;
	case BinaryOperator::mod:
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "movl %eax, %ebx" << std::endl
			<< "pop %eax" << std::endl
			<< "movl $0, %edx" << std::endl
			<< "idiv %ebx" << std::endl
			<< "movl %edx, %eax" << std::endl;
		break;
	case BinaryOperator::boolAnd:
	{
		auto falseMarker = NewMarker();
		out << "cmpl $0, %eax" << std::endl
			<< "je " << falseMarker << std::endl;
		node->Right()->AcceptVisitor(this);
		out << falseMarker << ":" << std::endl;
	}
	break;
	case BinaryOperator::boolOr:
	{
		auto trueMarker = NewMarker();
		out << "cmpl $1, %eax" << std::endl
			<< "je " << trueMarker << std::endl;
		node->Right()->AcceptVisitor(this);
		out << trueMarker << ":" << std::endl;
	}
	break;
	case BinaryOperator::equals:
	{
		auto eqMarker = NewMarker();
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "cmpl %eax, (%esp)" << std::endl
			<< "movl $1, %eax" << std::endl
			<< "je " << eqMarker << std::endl
			<< "movl $0, %eax" << std::endl
			<< eqMarker << ":" << std::endl
			<< "addl $4, %esp" << std::endl;
	}
		break;
	case BinaryOperator::unEquals:
	{
		auto uneqMarker = NewMarker();
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "cmpl %eax, (%esp)" << std::endl
			<< "movl $1, %eax" << std::endl
			<< "jne " << uneqMarker << std::endl
			<< "movl $0, %eax" << std::endl
			<< uneqMarker << ":" << std::endl
			<< "addl $4, %esp" << std::endl;
	}
	break;
	case BinaryOperator::less:
	{
		auto lMarker = NewMarker();
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "cmpl %eax, (%esp)" << std::endl
			<< "movl $1, %eax" << std::endl
			<< "jl " << lMarker << std::endl
			<< "movl $0, %eax" << std::endl
			<< lMarker << ":" << std::endl
			<< "addl $4, %esp" << std::endl;
	}
	break;
	case BinaryOperator::greater:
	{
		auto gMarker = NewMarker();
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "cmpl %eax, (%esp)" << std::endl
			<< "movl $1, %eax" << std::endl
			<< "jg " << gMarker << std::endl
			<< "movl $0, %eax" << std::endl
			<< gMarker << ":" << std::endl
			<< "addl $4, %esp" << std::endl;
	}
	break;
	case BinaryOperator::lessEquals:
	{
		auto leMarker = NewMarker();
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "cmpl %eax, (%esp)" << std::endl
			<< "movl $1, %eax" << std::endl
			<< "jle " << leMarker << std::endl
			<< "movl $0, %eax" << std::endl
			<< leMarker << ":" << std::endl
			<< "addl $4, %esp" << std::endl;
	}
	break;
	case BinaryOperator::greaterEquals:
	{
		auto geMarker = NewMarker();
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "cmpl %eax, (%esp)" << std::endl
			<< "movl $1, %eax" << std::endl
			<< "jge " << geMarker << std::endl
			<< "movl $0, %eax" << std::endl
			<< geMarker << ":" << std::endl
			<< "addl $4, %esp" << std::endl;
	}
	break;
	default:
		throw UnknownOperatorException();
	}
}

void GASVisitor::Visit(const StatementBlockASTNode *n) {
	environmentStack.push(n->VariablesEnvironment());
	auto size = n->VariablesEnvironment()->GetSize();
	out << "subl $" << size << ", %esp" << std::endl;
	auto children = n->Children();
	for (auto it = children->begin(); it != children->end(); it++) {
		it->get()->AcceptVisitor(this);
	}
	out << "addl $" << size << ", %esp" << std::endl;
	environmentStack.pop();
}

void GASVisitor::Visit(const DeclarationASTNode *n) {
	n->Expression()->AcceptVisitor(this);
	out << "movl %eax, -" << environmentStack.top()->GetRelativeAdress(n->VariableId()) << "(%ebp)" << std::endl;
}

void GASVisitor::Visit(const AssignmentASTNode *n) {
	n->Expression()->AcceptVisitor(this);
	out << "movl %eax, -" << environmentStack.top()->GetRelativeAdress(n->VariableId()) << "(%ebp)" << std::endl;
}

void GASVisitor::Visit(const VariableASTNode *n) {
	out << "movl " << environmentStack.top()->GetRelativeAdress(n->Variable()) << "(%ebp), %eax" << std::endl;
}

void GASVisitor::Visit(const NegationASTNode *n) {
	n->Expression()->AcceptVisitor(this);
	out << "negl %eax" << std::endl;
}

void GASVisitor::Visit(const IfASTNode *n) {
	auto marker = NewMarker();
	n->Condition()->AcceptVisitor(this);
	out << "cmpl $0, %eax" << std::endl
		<< "je " << marker << std::endl;
	n->ThenBody()->AcceptVisitor(this);
	out << marker << ":" << std::endl;
}

void GASVisitor::Visit(const IfElseASTNode *n) {
	auto elseMarker = NewMarker();
	auto endMarker = NewMarker();
	n->Condition()->AcceptVisitor(this);
	out << "cmpl $0, %eax" << std::endl
		<< "je " << elseMarker << std::endl;
	n->ThenBody()->AcceptVisitor(this);
	out << "jmp " << endMarker << std::endl
		<< elseMarker << ":" << std::endl;
	n->ElseBody()->AcceptVisitor(this);
	out << endMarker << ":" << std::endl;
}

void GASVisitor::Visit(const WhileASTNode *n) {
	auto startMarker = NewMarker();
	auto endMarker = NewMarker();
	out << startMarker << ":" << std::endl;
	n->Condition()->AcceptVisitor(this);
	out << "cmpl $0, %eax" << std::endl
		<< "je " << endMarker << std::endl;
	n->Body()->AcceptVisitor(this);
	out << "jmp " << startMarker << std::endl
		<< endMarker << ":" << std::endl;
}

void GASVisitor::Visit(const ComplementASTNode *n) {
	out << "push $1" << std::endl;
	n->Expression()->AcceptVisitor(this);
	out << "subl %eax, (%esp)" << std::endl
		<< "pop %eax" << std::endl;
}

void GASVisitor::Visit(const FunctionDefinitionASTNode *n) {
	out << ".globl _" << n->Name() << std::endl
		<< "_" << n->Name() << ":" << std::endl
		<< "push %ebp" << std::endl
		<< "mov %esp, %ebp" << std::endl;
	n->Code()->AcceptVisitor(this);
	out << "pop %ebp" << std::endl
		<< "ret" << std::endl;
}

void GASVisitor::Visit(const FunctionDefinitionsASTNode *n) {
	//auto funcEnv = n->Environment();
	//TODO write functiondefinitions
	auto functions = n->Children();
	for (auto it = functions->begin(); it != functions->end(); it++) {
		it->get()->AcceptVisitor(this);
	}
}

void GASVisitor::Visit(const FunctionCallASTNode *n) {
	auto params = n->GetParameters();
	if (params->size() != 0) {
		for (auto it = params->rbegin(); it != params->rend(); it++) {
			(*it)->AcceptVisitor(this);
			out << "push %eax" << std::endl;
		}
	}
	out << "call _" << n->Name() << std::endl
		<< "addl $" << params->size() * 4 << ", %esp" << std::endl; //TODO make size variable
}

void GASVisitor::Visit(const ReturnASTNode *n) {
	auto size = n->VariablesEnvironment()->GetSize() + n->VariablesEnvironment()->GetSizeFromParentsWithoutParamEnv();
	out << "addl $" << size << ", %esp" << std::endl;

	if (n->HasResult()) {
		n->Result()->AcceptVisitor(this);
	}
	out << "pop %ebp" << std::endl
		<< "ret" << std::endl;
}