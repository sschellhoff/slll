#pragma once

#include <string>
#include "Token.h"
#include "Scanner.h"

namespace slll {

	class Siever
	{
	private:
		Scanner scanner;
	public:
		Siever(std::string sourcecode);
		~Siever();
		Siever(Siever &&s);
		Siever(const Siever &c) = delete;

		Token NextToken();
	};

}