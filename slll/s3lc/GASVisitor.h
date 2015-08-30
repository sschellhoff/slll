#pragma once

#include <iostream>
#include <stack>

#include "IVisitor.h"
#include "VariablesEnvironment.h"

namespace slll {

	class GASVisitor :
		public IVisitor
	{
	private:
		std::ostream &out;
		std::stack<VariablesEnvironment*> environmentStack;
		unsigned int nextMarkerId;
	public:
		GASVisitor(std::ostream &out);
		~GASVisitor();
		std::string NewMarker();
		void Visit(const IntConstASTNode *node);
		void Visit(const BinOpASTNode *node);
		void Visit(const StatementBlockASTNode *n);
		void Visit(const DeclarationASTNode *n);
		void Visit(const AssignmentASTNode *n);
		void Visit(const VariableASTNode *n);
		void Visit(const NegationASTNode *n);
		void Visit(const IfASTNode *n);
		void Visit(const IfElseASTNode *n);
		void Visit(const WhileASTNode *n);
		void Visit(const ComplementASTNode *n);
		void Visit(const FunctionDefinitionASTNode *n);
		void Visit(const FunctionDefinitionsASTNode *n);
		void Visit(const FunctionCallASTNode *n);
		void Visit(const ReturnASTNode *n);
	};

}
