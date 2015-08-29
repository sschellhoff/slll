#pragma once

#include "IAST.h"

#include <string>

namespace slll {

	class FunctionCallASTNode : public IAST
	{
	private:
		std::string name;
	public:
		FunctionCallASTNode(std::string name);
		~FunctionCallASTNode();
		FunctionCallASTNode(const FunctionCallASTNode &n) = delete;
		FunctionCallASTNode(FunctionCallASTNode &&n);
		const std::string &Name()const;
		void AcceptVisitor(IVisitor *visitor);
	};

}