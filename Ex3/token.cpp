#include "stdafx.h"
#include "token.h"
#include "enums.h"

namespace parser
{
	token::token ( const token_kind kind, const int start, const int end, const int column, const int line,
	               const std::string data )
		: kind ( kind ), position ( start ), end ( end ), column ( column ), line ( line ), length ( end - start ),
		  data ( data )
	{
	}

	token::token ()
		: kind ( token_kind::none ), position ( 0 ), end ( 0 ), column ( 0 ), line ( 0 ), length ( 0 ), data ()
	{
	}

	token token::token_unknown = token ( token_kind::unknown, 0, 0, 0, 0, "" );
}
