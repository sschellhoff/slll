#pragma once

#include "TokenType.h"
#include <string>

namespace slll {

	class Token
	{
	private:
		TokenType type;
		std::string value;
	public:
		Token(TokenType type, std::string value);
		~Token();

		TokenType Type()const;
		const std::string &Value()const;

		friend std::ostream &operator<<(std::ostream &stream, const Token &token);
	};

}
