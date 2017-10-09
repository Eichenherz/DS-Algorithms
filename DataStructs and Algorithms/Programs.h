#pragma once

#include "Stack.h"
#include <assert.h>
#include <iostream>

void Symbol_Balancing( void )
{
	Stack<char> stack;

	for ( char temp = '\0'; temp != 'D'; std::cin.get( temp ) )
	{
		switch ( temp )
		{
		case '(':
			stack.push( temp );
			break;
		case '{':
			stack.push( temp );
			break;
		case ')':
			assert( !stack.empty() );
			if ( stack.top() == '(' ) stack.pop();
			else assert( 0 );
			break;
		case '}':
			assert( !stack.empty() );
			if ( stack.top() == '{' ) stack.pop();
			else assert( 0 );
			break;
		}
	}

	assert( stack.empty() );
}