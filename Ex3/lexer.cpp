#include "stdafx.h"
#include "lexer.h"

lexer::lexer ( const std::string str )
	: m_str ( str ), m_position ( 1 ), m_column ( 1 ), m_line ( 1 ), m_lastKind ( none ),
	  m_tokens ( std::vector <token> () )
{
	m_ptr = &m_str[0];
	refresh ();
}

lexer::~lexer ()
{
	delete m_ptr;
}

void lexer::tokenize ()
{
	switch ( m_current )
	{
		case '\t' :
		{
			m_lastKind = tab;
			m_position += 3;

			break;
		}

		case '\n' :
		{
			m_lastKind = new_line;

			m_line++;
			m_column = 1;

			break;
		}

		case ' ' :
		{
			m_lastKind = whitespace;
			break;
		}

		case '!' :
		{
			m_lastKind = exclamation_mark;
			break;
		}

		case '\"' :
		{
			m_lastKind = double_quote;
			break;
		}

		case '\'' :
		{
			m_lastKind = single_quote;
			break;
		}

		case '@' :
		{
			m_lastKind = at;
			break;
		}

		case '#' :
		{
			m_lastKind = hash;
			break;
		}

		case '£' :
		{
			m_lastKind = pound;
			break;
		}

		case '$' :
		{
			m_lastKind = dollar;
			break;
		}

		case '€' :
		{
			m_lastKind = euro;
			break;
		}

		case '%' :
		{
			m_lastKind = percent;
			break;
		}

		case '&' :
		{
			m_lastKind = ampersand;
			break;
		}

		case '{' :
		{
			m_lastKind = curly_brace_l;
			break;
		}

		case '}' :
		{
			m_lastKind = curly_brace_r;
			break;
		}

		case '[' :
		{
			m_lastKind = square_brace_l;
			break;
		}

		case ']' :
		{
			m_lastKind = square_brace_r;
			break;
		}

		case '(' :
		{
			m_lastKind = paranthesis_l;
			break;
		}

		case ')' :
		{
			m_lastKind = paranthesis_r;
			break;
		}

		case '=' :
		{
			m_lastKind = equals;
			break;
		}

		case '?' :
		{
			m_lastKind = question_mark;
			break;
		}

		case '`' :
		{
			m_lastKind = grave_accent;
			break;
		}

		case '´' :
		{
			m_lastKind = diacritical_mark;
			break;
		}

		case '^' :
		{
			m_lastKind = caret;
			break;
		}

		case '~' :
		{
			m_lastKind = tilde;
			break;
		}

		case '*' :
		{
			m_lastKind = asterisk;
			break;
		}

		case '-' :
		{
			m_lastKind = hyphen;
			break;
		}

		case '_' :
		{
			m_lastKind = underscore;
			break;
		}

		case '.' :
		{
			m_lastKind = period;
			break;
		}

		case ':' :
		{
			m_lastKind = colon;
			break;
		}

		case ',' :
		{
			m_lastKind = comma;
			break;
		}

		case ';' :
		{
			m_lastKind = semicolon;
			break;
		}

		case '<' :
		{
			m_lastKind = arrow_l;
			break;
		}

		case '>' :
		{
			m_lastKind = arrow_r;
			break;
		}

		case '|' :
		{
			m_lastKind = pipe;
			break;
		}

		case '½' :
		{
			m_lastKind = one_half;
			break;
		}

		case '§' :
		{
			m_lastKind = section;
			break;
		}

		default :
		{
			m_position++;

			if ( isalpha ( m_current ) )
			{
				parseAlpha ();
				m_lastKind = m_position - m_lastStart > 1 ? string : character;
			}
			else if ( isdigit ( m_current ) )
			{
				parseNumeric ();
				m_lastKind = m_position - m_lastKind > 1 ? number : digit;
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
	eat ();

	m_lastEnd = m_position;

	if ( m_lastKind == whitespace )
	{
		return;
	}

	m_tokens.push_back ( token ( m_lastKind, m_lastStart, m_lastEnd, col, ln, m_lastData ) );
}

void lexer::advanceUntilEnd ()
{
	while ( true )
	{
		if ( m_next == '\0' )
		{
			advance ();
			break;
		}

		advance ();
	}
}

void lexer::eat ()
{
	m_lastData.push_back ( m_current );

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

const char* lexer::getPointer () const
{
	return m_ptr;
}

uint16_t lexer::getPosition () const
{
	return m_position;
}

uint16_t lexer::getColumn () const
{
	return m_column;
}

uint16_t lexer::getLine () const
{
	return m_line;
}

char lexer::getCurrent () const
{
	return m_current;
}

char lexer::getNext () const
{
	return m_next;
}

char lexer::getPrevious () const
{
	return m_prev;
}

void lexer::parseAlpha ()
{
	while ( isalpha ( m_next ) )
	{
		eat ();
	}
}

void lexer::parseNumeric ()
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
