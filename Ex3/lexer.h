#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "token.h"

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
	class token;

	class lexer
	{
	public:
		explicit lexer ( std::string );

		void advance ();
		void advanceUntilEnd ();

		void tokenize ();
		void eat ();

		void parseAlpha ();
		void parseNumeric ();

		void refresh ();

		uint16_t getPosition () const;
		uint16_t getColumn () const;
		uint16_t getLine () const;

		const char* getPointer() const;

		char getCurrent () const;
		char getNext () const;
		char getPrevious () const;

		std::vector <token> tokens () const;

	private:
		std::string m_str;
		const char* m_ptr { };

		char m_current { }, m_next { }, m_prev { };

		uint16_t m_position = 1;
		uint16_t m_column   = 1;
		uint16_t m_line     = 1;

		uint16_t m_lastStart { }, m_lastEnd { };

		token_kind m_lastKind;
		std::string m_lastData;

		std::vector <token> m_tokens { };
	};
}
