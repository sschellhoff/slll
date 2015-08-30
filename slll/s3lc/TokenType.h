#pragma once

namespace slll {
	enum class TokenType
	{
		add,			// addition operator		+
		sub,			// subtraction operator		-
		mult,			// multiplication operator	*
		div,			// division operator		/
		mod,			// modulo operator			%
		lt,				// less than operator		<
		gt,				// greater than operator	>
		le,				// less equals operator		<=
		ge,				// greater equals operator	>=
		eq,				// equals operator			==
		ne,				// not equals operator		!=
		boolAnd,		// and operator				&&
		boolOr,			// or operator				||
		neg,			// negation operator		!
		assign,			// assignment operator		=
		decl,			// declaration operator		:=
		lpar,			// left prentheses			(
		rpar,			// right parentheses		)
		lbra,			// left bracket				{
		rbra,			// right bracket			}
		lindexbra,		// left index bracket		[
		rindexbra,		// right index bracket		]
		sep,			// seperator				;
		opsep,			// operand seperator		,
		intconst,		// integer constant			1337
		identifier,		// identifier				foobar
		if_ident,		// if identifier			if
		else_ident,		// else identifier			else
		for_ident,		// for identifier			for
		while_ident,	// while identifier			while
		return_ident,	// return identifier		return
		break_ident,	// break identifier			break
		continue_ident,	// continue identifier		continue
		eof,			// end of file				<eof>
		error			// error
	};

}