#pragma once

#include <memory>

namespace slll {
	class IAST;
	class IVisitor;
}
using ast = std::unique_ptr<slll::IAST>;

namespace slll {

	class IAST
	{
	public:
		IAST();
		virtual ~IAST() = 0;
		IAST(const IAST &t) = delete;
		//virtual IAST(IAST &&t) = 0;
		virtual void AcceptVisitor(IVisitor *visitor) = 0;
	};

}