#pragma once

#include <iostream>
#include <stack>

#include "IVisitor.h"
#include "Environment.h"

namespace slll {

	class GASVisitor :
		public IVisitor
	{
	private:
		std::ostream &out;
		std::stack<Environment*> environmentStack;
		unsigned int nextMarkerId;
	public:
		GASVisitor(std::ostream &out);
		~GASVisitor();
		void WriteProgramPrefix();
		void WriteProgramSuffix();
		std::string NewMarker();
		void Visit(const IntConstASTNode *node);
		void Visit(const BinOpASTNode *node);
		void Visit(const PrintIntStatementASTNode *n);
		void Visit(const PrintNewLineStatementASTNode *n);
		void Visit(const StatementBlockASTNode *n);
		void Visit(const DeclarationASTNode *n);
		void Visit(const AssignmentASTNode *n);
		void Visit(const VariableASTNode *n);
		void Visit(const NegationASTNode *n);
		void Visit(const IfASTNode *n);
		void Visit(const IfElseASTNode *n);
		void Visit(const WhileASTNode *n);
	};

}
