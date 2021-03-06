// Ex3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "lexer.h"

int main ()
{
	parser::lexer m_lexer ( "This is my string, and I'm 12 years old." );

	std::vector <char> m_captured;
	m_lexer.advance_until ( [] ( parser::lexer l ) { return l.current () == '1'; }, m_captured );

	std::cin.get ();
	return 0;
}
