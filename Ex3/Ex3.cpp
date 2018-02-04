// Ex3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "lexer.h"

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
