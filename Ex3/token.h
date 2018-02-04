#pragma once
#include <string>
#include "lexer.h"
#include "enums.h"

namespace parser
{
	class token
	{
	public:
		token ( token_kind kind, int start, int end, int column, int line,
		        std::string data );

		token ();

		static token token_unknown;

		token_kind kind;

		uint16_t position;
		uint16_t end;

		uint16_t column;
		uint16_t line;

		uint16_t length;

		std::string data;
	};
}
