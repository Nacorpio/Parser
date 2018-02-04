// Ex3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "lexer.h"

int main ()
{
	parser::lexer l ( "This is my string, and I'm 12 years old." );
	std::vector <char> results;

	l.advance_until ( [] ( parser::lexer l ) { return l.current () == '1'; }, results );

	std::cin.get ();
	return 0;
}
