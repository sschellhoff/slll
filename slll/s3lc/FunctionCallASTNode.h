#pragma once

#include "IAST.h"

#include <string>
#include <vector>

namespace slll {

	class FunctionCallASTNode : public IAST
	{
	private:
		std::string name;
		std::vector<std::unique_ptr<IAST>> parameters;
	public:
		FunctionCallASTNode(std::string name);
		FunctionCallASTNode(std::string name, std::vector<std::unique_ptr<IAST>> &parameters);
		~FunctionCallASTNode();
		FunctionCallASTNode(const FunctionCallASTNode &n) = delete;
		FunctionCallASTNode(FunctionCallASTNode &&n);
		const std::string &Name()const;
		const std::vector<std::unique_ptr<IAST>> *GetParameters()const;
		void AcceptVisitor(IVisitor *visitor);
	};

}