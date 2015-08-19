#pragma once

namespace slll {
	enum TokenType
	{
		add,		// addition operator		+
		sub,		// subtraction operator		-
		mult,		// multiplication operator	*
		div,		// division operator		/
		mod,		// modulo operator			%
		lt,			// less than operator		<
		gt,			// greater than operator	>
		le,			// less equals operator		<=
		ge,			// greater equals operator	>=
		eq,			// equals operator			==
		ne,			// not equals operator		!=
		neg,		// negation operator		!
		assign,		// assignment operator		=
		decl,		// declaration operator		:=
		lpar,		// left prenthesis			(
		rpar,		// right parenthesis		)
		lbra,		// left bracket				{
		rbra,		// right bracket			}
		sep,		// seperator				;
		opsep,		// operand seperator		,
		intconst,	// integer constant			1337
		identifier, // identifier				foobar
		eof,		// end of file				<eof>
		error		// error
	};

}