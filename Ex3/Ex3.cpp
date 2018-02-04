// Ex3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include "lexer.h"

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
char m_current, m_next, m_prev;

token_kind m_lastKind;

uint16_t m_position;
uint16_t m_column;
uint16_t m_line;

uint16_t m_lastStart;
uint16_t m_lastEnd;

std::string m_lastData;
std::vector <token> m_tokens;

int main ()
{
	lexer l = lexer ( "This is my string, and I'm 12 years old." );
	l.advanceUntilEnd ();

	for ( const token t : l.GetTokens () )
	{
		std::cout << t.data << std::endl;
	}

	std::cin.get ();
	return 0;
}
