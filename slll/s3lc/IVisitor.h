#pragma once

namespace slll {
	class IntConstASTNode;
	class BinOpASTNode;
	class PrintIntStatementASTNode;
	class PrintNewLineStatementASTNode;
	class StatementBlockASTNode;
	class DeclarationASTNode;
	class AssignmentASTNode;
	class VariableASTNode;
	class NegationASTNode;

	class IVisitor
	{
	public:
		IVisitor();
		virtual ~IVisitor() = 0;
		virtual void Visit(const IntConstASTNode *n) = 0;
		virtual void Visit(const BinOpASTNode *n) = 0;
		virtual void Visit(const PrintIntStatementASTNode *n) = 0;
		virtual void Visit(const PrintNewLineStatementASTNode *n) = 0;
		virtual void Visit(const StatementBlockASTNode *n) = 0;
		virtual void Visit(const DeclarationASTNode *n) = 0;
		virtual void Visit(const AssignmentASTNode *n) = 0;
		virtual void Visit(const VariableASTNode *n) = 0;
		virtual void Visit(const NegationASTNode *n) = 0;
	};

}