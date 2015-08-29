#pragma once

namespace slll {
	class IntConstASTNode;
	class BinOpASTNode;
	class PrintIntStatementASTNode;
	class StatementBlockASTNode;
	class DeclarationASTNode;
	class AssignmentASTNode;
	class VariableASTNode;
	class NegationASTNode;
	class IfASTNode;
	class IfElseASTNode;
	class WhileASTNode;
	class ComplementASTNode;
	class FunctionDefinitionASTNode;
	class FunctionDefinitionsASTNode;
	class FunctionCallASTNode;
	class ReturnASTNode;

	class IVisitor
	{
	public:
		IVisitor();
		virtual ~IVisitor() = 0;
		virtual void Visit(const IntConstASTNode *n) = 0;
		virtual void Visit(const BinOpASTNode *n) = 0;
		virtual void Visit(const PrintIntStatementASTNode *n) = 0;
		virtual void Visit(const StatementBlockASTNode *n) = 0;
		virtual void Visit(const DeclarationASTNode *n) = 0;
		virtual void Visit(const AssignmentASTNode *n) = 0;
		virtual void Visit(const VariableASTNode *n) = 0;
		virtual void Visit(const NegationASTNode *n) = 0;
		virtual void Visit(const IfASTNode *n) = 0;
		virtual void Visit(const IfElseASTNode *n) = 0;
		virtual void Visit(const WhileASTNode *n) = 0;
		virtual void Visit(const ComplementASTNode *n) = 0;
		virtual void Visit(const FunctionDefinitionASTNode *n) = 0;
		virtual void Visit(const FunctionDefinitionsASTNode *n) = 0;
		virtual void Visit(const FunctionCallASTNode *n) = 0;
		virtual void Visit(const ReturnASTNode *n) = 0;		
	};

}