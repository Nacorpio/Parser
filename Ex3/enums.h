#pragma once
namespace parser
{
	enum class token_kind
	{
		none,
		unknown,

		exclamation_mark,
		hash,
		double_quote,
		single_quote,
		at,
		pound,
		dollar,
		euro,
		currency,
		percent,
		ampersand,
		forward_slash,
		backslash,
		curly_brace_r,
		curly_brace_l,
		paranthesis_r,
		paranthesis_l,
		square_brace_r,
		square_brace_l,
		equals,
		question_mark,
		plus,
		hyphen,
		diacritical_mark,
		grave_accent,
		caret,
		tilde,
		asterisk,
		underscore,
		period,
		comma,
		semicolon,
		colon,
		arrow_l,
		arrow_r,
		pipe,
		section,
		one_half,

		character,
		string,

		digit,
		number,
		decimal,

		tab,
		new_line,
		whitespace,

		eof
	};
}
