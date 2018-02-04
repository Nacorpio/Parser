// Ex3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "lexer.h"

int main ()
{
	parser::lexer l ( "This is my string, and I'm 12 years old." );
	l.advanceUntilEnd ();

	for ( const parser::token& t : l.tokens () )
	{
		std::cout << t.data << std::endl;
	}

	std::cin.get ();
	return 0;
}
