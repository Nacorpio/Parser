#include "stdafx.h"
#include "lexer.h"
#include "token.h"

namespace parser
{
	lexer::lexer ( const std::string str )
		: m_str ( str ), m_lastKind ( token_kind::none )
	{
		m_ptr = &m_str[0];
		refresh ();
	}

	void lexer::tokenize ()
	{
		switch ( m_current )
		{
			case '\t' :
			{
				m_lastKind = token_kind::tab;
				m_position += 3;

				break;
			}

			case '\n' :
			{
				m_lastKind = token_kind::new_line;

				m_line++;
				m_column = 1;

				break;
			}

			case ' ' :
			{
				m_lastKind = token_kind::whitespace;
				break;
			}

			case '!' :
			{
				m_lastKind = token_kind::exclamation_mark;
				break;
			}

			case '\"' :
			{
				m_lastKind = token_kind::double_quote;
				break;
			}

			case '\'' :
			{
				m_lastKind = token_kind::single_quote;
				break;
			}

			case '@' :
			{
				m_lastKind = token_kind::at;
				break;
			}

			case '#' :
			{
				m_lastKind = token_kind::hash;
				break;
			}

			case '£' :
			{
				m_lastKind = token_kind::pound;
				break;
			}

			case '$' :
			{
				m_lastKind = token_kind::dollar;
				break;
			}

			case '€' :
			{
				m_lastKind = token_kind::euro;
				break;
			}

			case '%' :
			{
				m_lastKind = token_kind::percent;
				break;
			}

			case '&' :
			{
				m_lastKind = token_kind::ampersand;
				break;
			}

			case '{' :
			{
				m_lastKind = token_kind::curly_brace_l;
				break;
			}

			case '}' :
			{
				m_lastKind = token_kind::curly_brace_r;
				break;
			}

			case '[' :
			{
				m_lastKind = token_kind::square_brace_l;
				break;
			}

			case ']' :
			{
				m_lastKind = token_kind::square_brace_r;
				break;
			}

			case '(' :
			{
				m_lastKind = token_kind::paranthesis_l;
				break;
			}

			case ')' :
			{
				m_lastKind = token_kind::paranthesis_r;
				break;
			}

			case '=' :
			{
				m_lastKind = token_kind::equals;
				break;
			}

			case '?' :
			{
				m_lastKind = token_kind::question_mark;
				break;
			}

			case '`' :
			{
				m_lastKind = token_kind::grave_accent;
				break;
			}

			case '´' :
			{
				m_lastKind = token_kind::diacritical_mark;
				break;
			}

			case '^' :
			{
				m_lastKind = token_kind::caret;
				break;
			}

			case '~' :
			{
				m_lastKind = token_kind::tilde;
				break;
			}

			case '*' :
			{
				m_lastKind = token_kind::asterisk;
				break;
			}

			case '-' :
			{
				m_lastKind = token_kind::hyphen;
				break;
			}

			case '_' :
			{
				m_lastKind = token_kind::underscore;
				break;
			}

			case '.' :
			{
				m_lastKind = token_kind::period;
				break;
			}

			case ':' :
			{
				m_lastKind = token_kind::colon;
				break;
			}

			case ',' :
			{
				m_lastKind = token_kind::comma;
				break;
			}

			case ';' :
			{
				m_lastKind = token_kind::semicolon;
				break;
			}

			case '<' :
			{
				m_lastKind = token_kind::arrow_l;
				break;
			}

			case '>' :
			{
				m_lastKind = token_kind::arrow_r;
				break;
			}

			case '|' :
			{
				m_lastKind = token_kind::pipe;
				break;
			}

			case '½' :
			{
				m_lastKind = token_kind::one_half;
				break;
			}

			case '§' :
			{
				m_lastKind = token_kind::section;
				break;
			}

			default :
			{
				m_position++;

				if ( isalpha ( m_current ) )
				{
					parse_alpha ();
					m_lastKind = m_position - m_lastStart > 1 ? token_kind::string : token_kind::character;
				}
				else if ( isdigit ( m_current ) )
				{
					parse_numeric ();
					m_lastKind = m_position - m_lastStart > 1 ? token_kind::number : token_kind::digit;
				}
			}
		}
	}

	void lexer::advance ()
	{
		m_lastData.clear ();
		m_lastStart = m_position;

		const int col = m_column;
		const int ln  = m_line;

		tokenize ();

		m_lastData.push_back ( m_current );

		eat ();

		m_lastEnd = m_position;

		if ( m_lastKind == token_kind::whitespace )
		{
			return;
		}

		m_tokens.push_back ( token ( m_lastKind, m_lastStart, m_lastEnd, col, ln, m_lastData ) );
	}

	void lexer::advance_until_end ()
	{
		// Keep iterating until we hit NULL
		while ( m_next != '\0' )
		{
			advance ();
		}

		// Advance through the last token
		advance ();
	}

	void lexer::advance_while ( const std::function <bool  ( lexer& )> func )
	{
		while ( func ( *this ) )
		{
			eat ();
		}
	}

	void lexer::advance_until ( const std::function <bool  ( lexer& )> func )
	{
		while ( !func ( *this ) )
		{
			eat ();
		}
	}

	void lexer::advance_while ( const std::function <bool  ( lexer& )> func, std::vector <char>& results )
	{
		while ( func ( *this ) )
		{
			results.push_back ( current () );
			eat ();
		}
	}

	void lexer::advance_until ( const std::function <bool  ( lexer& )> func, std::vector <char>& results )
	{
		while ( !func ( *this ) )
		{
			results.push_back ( current () );
			eat ();
		}
	}

	void lexer::eat ()
	{
		m_ptr++;
		m_position++;
		m_column++;

		refresh ();
	}

	void lexer::refresh ()
	{
		m_current = *m_ptr;

		m_next = *( m_ptr + 1 );
		m_prev = *( m_ptr - 1 );
	}

	const char* lexer::Ptr () const
	{
		return m_ptr;
	}

	uint16_t lexer::get_position () const
	{
		return m_position;
	}

	uint16_t lexer::get_column () const
	{
		return m_column;
	}

	uint16_t lexer::get_line () const
	{
		return m_line;
	}

	char lexer::current () const
	{
		return m_current;
	}

	char lexer::next () const
	{
		return m_next;
	}

	char lexer::previous () const
	{
		return m_prev;
	}

	void lexer::parse_alpha ()
	{
		while ( isalpha ( m_next ) )
		{
			eat ();
		}
	}

	void lexer::parse_numeric ()
	{
		while ( isdigit ( m_next ) )
		{
			eat ();
		}
	}

	std::vector <token> lexer::tokens () const
	{
		return m_tokens;
	}
}
