#pragma once

#include <memory>

#include "IAST.h"

using ast = std::unique_ptr<slll::IAST>;

namespace slll {

	class BinOpASTNode : public IAST
	{
	private:
		ast left;
		ast right;
	public:
		BinOpASTNode(ast left, ast right);
		~BinOpASTNode();
	};

}