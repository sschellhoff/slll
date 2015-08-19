#pragma once

namespace slll {

	class IAST
	{
	public:
		IAST();
		~IAST();
		IAST(const IAST &t) = delete;
		IAST(IAST &&t) {}
	};

}