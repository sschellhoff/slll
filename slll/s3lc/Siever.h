#pragma once

#include <string>
#include "Token.h"
#include "Scanner.h"

namespace slll {

	class Siever
	{
	private:
		Scanner scanner;
		Token buffer;
		bool bufferUsed;
	public:
		Siever(std::string sourcecode);
		~Siever();

		Token NextToken();
	};

}