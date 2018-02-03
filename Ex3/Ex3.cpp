// Ex3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>

enum token_kind;
class token;

void tokenize ();
void advance ();
void refresh ();

void parseAlpha ();
void parseNumeric ();

void eat ();

std::string m_str;

const char* m_ptr;
char m_current, m_next;

token_kind m_lastKind;

uint16_t m_position;
uint16_t m_column;
uint16_t m_line;

uint16_t m_lastStart;
uint16_t m_lastEnd;

std::string m_lastData;
std::vector <token> m_tokens;

enum token_kind
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

class token
{
public:
	token ( const token_kind kind, const int start, const int end, const int column, const int line,
	        const std::string data )
		: kind ( kind ), position ( start ), end ( end ), column ( column ), line ( line ), length ( end - start ),
		  data ( data )
	{
	}

	token ()
		: kind ( none ), position ( 0 ), end ( 0 ), column ( 0 ), line ( 0 ), length ( 0 ), data ()
	{
	}

	static token token_unknown;

	token_kind kind;

	uint16_t position;
	uint16_t end;

	uint16_t column;
	uint16_t line;

	uint16_t length;

	std::string data;
};

token token::token_unknown = token ( unknown, 0, 0, 0, 0, "" );

void refresh ()
{
	m_current = *m_ptr;
	m_next    = *( m_ptr + 1 );
}

void advance ()
{
	m_lastData.clear ();
	m_lastStart = m_position;

	const int col = m_column;
	const int ln  = m_line;

	tokenize ();
	eat ();

	m_lastEnd = m_position;

	if (m_lastKind == whitespace)
	{
		return;
	}

	m_tokens.push_back ( token ( m_lastKind, m_lastStart, m_lastEnd, col, ln, m_lastData ) );
}

int main ()
{
	m_tokens = std::vector <token> ();

	m_position = 1;
	m_column   = 1;
	m_line     = 1;

	m_str = "This is my string, and I'm 12 years old.";
	m_ptr = &m_str[0];

	refresh ();

	while ( true )
	{
		if ( m_next == '\0' )
		{
			advance ();
			break;
		}

		advance ();
	}

	for ( const token t : m_tokens )
	{
		std::cout << t.data << std::endl;
	}

	std::cin.get ();
	return 0;
}

void tokenize ()
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

void eat ()
{
	m_lastData.push_back ( m_current );

	m_ptr++;
	m_position++;
	m_column++;

	refresh ();
}

void parseAlpha ()
{
	m_position++;

	while ( isalpha ( m_next ) )
	{
		eat ();
	}
}

void parseNumeric ()
{
	m_position++;

	while ( isdigit ( m_next ) )
	{
		eat ();
	}
}
