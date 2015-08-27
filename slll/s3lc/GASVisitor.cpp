#include "GASVisitor.h"

#include "IntConstASTNode.h"
#include "BinOpASTNode.h"
#include "PrintIntStatementASTNode.h"
#include "PrintNewLineStatementASTNode.h"
#include "StatementBlockASTNode.h"
#include "DeclarationASTNode.h"
#include "AssignmentASTNode.h"
#include "VariableASTNode.h"
#include "NegationASTNode.h"

using namespace slll;

GASVisitor::GASVisitor(std::ostream &out):out(out)
{
}


GASVisitor::~GASVisitor()
{
}

void GASVisitor::WriteProgramPrefix() {
	out << ".text" << std::endl
		<< ".globl _prog" << std::endl
		<< "_prog:" << std::endl
		<< "push %ebp" << std::endl
		<< "mov %esp, %ebp" << std::endl;
}

void GASVisitor::WriteProgramSuffix() {
	out << "pop %ebp" << std::endl
		<< "ret" << std::endl;
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
	case TokenType::add:
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "addl (%esp), %eax" << std::endl
			<< "addl $4, %esp" << std::endl;
		break;
	case TokenType::sub:
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "subl %eax, (%esp)" << std::endl
			<< "pop %eax" << std::endl;
		break;
	case TokenType::mult:
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "imull (%esp), %eax" << std::endl
			<< "addl $4, %esp" << std::endl;
		break;
	case TokenType::div:
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "movl %eax, %ebx" << std::endl
			<< "pop %eax" << std::endl
			<< "movl $0, %edx" << std::endl
			<< "idiv %ebx" << std::endl;
		break;
	case TokenType::mod:
		out << "push %eax" << std::endl;
		node->Right()->AcceptVisitor(this);
		out << "movl %eax, %ebx" << std::endl
			<< "pop %eax" << std::endl
			<< "movl $0, %edx" << std::endl
			<< "idiv %ebx" << std::endl
			<< "movl %edx, %eax" << std::endl;
		break;
	default:
		out << "wrong operator" << std::endl;
	}
}

void GASVisitor::Visit(const PrintIntStatementASTNode *n) {
	n->Expression()->AcceptVisitor(this);
	out << "pushl %eax" << std::endl
		<< "call _print_int" << std::endl
		<< "addl $4, %esp" << std::endl;
}

void GASVisitor::Visit(const PrintNewLineStatementASTNode *n) {
	out << "call _print_nl" << std::endl;
}

void GASVisitor::Visit(const StatementBlockASTNode *n) {
	environmentStack.push(n->Environment());
	auto size = n->Environment()->GetSize();
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
	out << "movl -" << environmentStack.top()->GetRelativeAdress(n->Variable()) << "(%ebp), %eax" << std::endl;
}

void GASVisitor::Visit(const NegationASTNode *n) {
	n->Expression()->AcceptVisitor(this);
	out << "negl %eax" << std::endl;
}