#pragma once

#include "Stack.h"
#include <assert.h>
#include <iostream>

void Symbol_Balancing( void )
{
	Stack<char> stack;

	for ( char symb = '\0'; symb != 'D'; std::cin.get( symb ) )
	{
		if ( symb == '(' || symb == '[' || symb == '{' || symb == '/*' )	stack.push( symb );
		else if ( symb == ')' || symb == ']' || symb == '}' || symb == '*/' )
		{
			assert( !stack.empty() );
			switch ( symb )
			{
			case ')': assert( stack.top() == '(' );
				break;
			case ']': assert( stack.top() == '[' );
				break;
			case '}': assert( stack.top() == '{' );
				break;
			case '*/': assert( stack.top() == '/*' );
				break;
			}
			stack.pop();
		}
	}

	assert( stack.empty() );
}