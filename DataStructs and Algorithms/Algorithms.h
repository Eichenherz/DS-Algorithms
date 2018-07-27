#pragma once

#include "List.h"
#include "Vector.h"
#include <iostream>
#include <random>
#include <math.h>
#include <string>
#include "Stack.h"

template<typename T>
void Print_Lots( const List<T>& l, const List<T>& p )
{
	//lists are sorted in ascending order
	auto	pos_itr = l.cbegin();
	int		pos_jump = 0;

	for ( auto iter = p.cbegin(); iter != p.cend(); ++iter )
		if ( *iter <= l.size() - 1 )
		{
			auto pos = *iter;

			for ( int i = 0; i < pos - pos_jump; ++i ) ++pos_itr;

			pos_jump = pos;

			std::cout << *pos_itr << " ";
		}

}

//To support most types of containers
template<class Iter, typename T>
typename List<T>::iterator find( Iter begin, Iter end, const T& obj )
{
	for ( ; begin != end; ++begin ) {
		if ( *begin == obj ) return begin;
	}
	return end;
}

template<typename T>
List<T> intersection( const List<T>& alpha, const List<T>& beta )
{
	List<T> temp;

	if ( alpha.empty() || beta.empty() ) { return temp; }

	auto a_iter = alpha.cbegin();
	auto b_iter = beta.cbegin();

	while ( a_iter != alpha.cend() && b_iter != beta.cend() )
	{
		if ( *a_iter == *b_iter )
		{
			temp.push_back( *a_iter );
			++a_iter;
			++b_iter;
		}
		else if ( *a_iter < *b_iter ) { ++a_iter; }
		else if ( *a_iter > *b_iter ) { ++b_iter; }
	}

	return temp;
}

template<typename T>
List<T> reunion( const List<T>& alpha, const List<T>& beta )
{
	List<T> temp;

	if ( alpha.empty() && beta.empty() ) { return temp; }

	auto a_iter = alpha.cbegin();
	auto b_iter = beta.cbegin();

	while ( a_iter != alpha.cend() && b_iter != beta.cend() )
	{
		if ( *a_iter < *b_iter ) 
		{
			temp.push_back( *a_iter );
			++a_iter;
		}
		else if ( *a_iter > *b_iter )
		{
			temp.push_back( *b_iter );
			++b_iter; 
		}
		else if ( *a_iter == *b_iter )
		{
			temp.push_back( *a_iter );
			++a_iter;
			++b_iter;
		}
	}

	for ( ; a_iter != alpha.cend(); ++a_iter )
			temp.push_back( *a_iter );
	for ( ; b_iter != beta.cend(); ++b_iter )
			temp.push_back( *b_iter );

	return temp;

}

//Not tera efficient though
int josephus( int N )
{
	Vector<int> bitset;
	// bitset[0] shifted MSB to LSB
	bitset.push_back( 1 );
	for (; N != 1; N /= 2 )
		bitset.push_back( N % 2 );

	int result = 0;
	for ( auto pos = bitset.size() - 1; pos != 0; --pos )
		result += bitset [pos] * int(std::exp2( pos ));

	return ++result;
}

//To be completed
void/*int*/ josephus_M( int N, int M )
{
	//if ( M == 0 ) return N;


}

//Just for ints
template<class Container>
void Generate_Rand_Uniform( Container& container, int n_obj )
{
	std::mt19937 rng( std::random_device {}( ) );
	std::uniform_int_distribution<int> dist;
	if ( n_obj % 2 == 0 )
	{
		std::uniform_int_distribution<int> dist( -n_obj / 2, n_obj / 2 );
		for ( ; n_obj != 0; --n_obj )
			container.push_back( dist( rng ) );
	}

	else
	{
		std::uniform_int_distribution<int> dist( -( n_obj + 1 ) / 2, n_obj / 2 );
		for ( ; n_obj != 0; --n_obj )
			container.push_back( dist( rng ) );
	}

}

void Symbol_Balancing( void )
{
	Stack<char> stack;

	for ( char symb = '\0'; symb != '\n'; std::cin.get( symb ) )
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

//Pseudo Int calculator
int Postfix_Eval( std::string buffer )
{
	//**********************************************//
	// Expression format :							//
	//  a' 'b' 'operator1 operator2' 'c' 'operator3	//
	//  NOTE : Only ' ' counts as CMD space			//
	//**********************************************//


	Stack<int> stack;

	int val = buffer [0] - '0';

	for ( size_t i = 1; i < buffer.length(); ++i )
	{
		if ( buffer [i] != '+' && buffer [i] != '-' && buffer [i] != '*' &&
			 buffer [i] != '/' && buffer [i] != '^' && buffer [i] != ' ' )
		{
			if ( buffer [i - 1] != ' ' ) val = val * 10 + buffer [i] - '0';
			else val = buffer [i] - '0';
		}
		else if ( buffer [i] == ' ' &&  val != 0 )
		{
			stack.push( val );
			val = 0;
		}
		else
		{
			if ( buffer [i] == '+' )
			{
				auto temp = stack.top();
				stack.pop();
				temp += stack.top();
				stack.pop();

				stack.push( temp );
			}
			else if ( buffer [i] == '-' )
			{
				auto temp = -stack.top();
				stack.pop();
				temp += stack.top();
				stack.pop();

				stack.push( temp );
			}
			else if ( buffer [i] == '*' )
			{
				auto temp = stack.top();
				stack.pop();
				temp *= stack.top();
				stack.pop();

				stack.push( temp );
			}
			else if ( buffer [i] == '/' )
			{
				auto temp = 1 / stack.top();
				stack.pop();
				temp *= stack.top();
				stack.pop();

				stack.push( temp );
			}
			else if ( buffer [i] == '^' )
			{
				auto temp = stack.top();
				stack.pop();
				temp *= int(log2( stack.top() ));
				stack.pop();
				temp = int( exp2( temp ) );

				stack.push( temp );
			}
		}
	}

	return stack.top();
}

class Operator_Traits
{
public:
	const enum class Precedence {
		Lower,
		Equal,
		Higher
	};


	Operator_Traits( const char lhs_)
	{
		Init_Iter( lhs_, lhs );
	}

	Precedence precedence( const char rhs_ )
	{
		Init_Iter( rhs_, rhs );

		if ( rhs - lhs > 0 ) return Precedence::Lower;
		else if ( rhs - lhs == 0 ) return Precedence::Equal;
		else return Precedence::Higher; //if ( rhs - lhs < 0 )
	}

private:
	const std::string operators = {
		'+', '-', '*', '/', '^' 
	};
	std::string::const_iterator lhs;
	std::string::const_iterator rhs;

	void Init_Iter( const char chr, std::string::const_iterator itr )
	{
		for ( auto iter = operators.cbegin(); iter != operators.cend(); ++iter ) {
			if ( *iter == chr ) {
				itr = iter;
				break;
			}
		}
	}
};

std::string To_Postfix( const std::string& infix )
{
	// infinx needs to have parenthesis around the subexpression w/ operatos w/ higher precedence
	Stack<char> stack;
	std::string postfix;

	postfix.push_back( *infix.cbegin() );

	for ( auto iter = infix.cbegin() + 1; iter != infix.cend(); ++iter )
	{
		if ( *iter != ' ' ) // Ignore infix whitespace
		{// if ( *iter == operand )
			if ( *iter != '+' && *iter != '-' && *iter != '*' &&
				 *iter != '/' && *iter != '^' && *iter != '(' &&
				 *iter != ')' ) 
			{
				postfix.push_back( ' ' ); // Add whitespaces before ->
				postfix.push_back( *iter );
				postfix.push_back( ' ' );//-> & after inserting operand, as required by the postfix precessing function
			}
			else { // if ( *iter == operator )
				if ( *iter == '(' ) { stack.push( *iter ); }
				else if ( *iter == ')' ) 
				{
					while ( stack.top() != '(' ) {
						if ( stack.top() != '(' ) {
							postfix.push_back( stack.top() ); 
						}
						stack.pop();
					}
					stack.pop();
				}
				else if ( stack.empty() || // Just because I was getting Exception : *nullptr from stack.top()
						  Operator_Traits { *iter }.precedence( stack.top() ) == Operator_Traits::Precedence::Higher )
				{ // Push to stack if *iter > stack.top()
					stack.push( *iter ); 
				}
				else if ( Operator_Traits { *iter }.precedence( stack.top() ) == Operator_Traits::Precedence::Lower ||
						  Operator_Traits { *iter }.precedence( stack.top() ) == Operator_Traits::Precedence::Equal )
				{ //else pop operators from stack to postfix until *iter <= stack.top() is no longer true
					if ( stack.top() != '(' ) {
						postfix.push_back( stack.top() );
						stack.pop();
					}
					stack.push( *iter );
				}
			}
		}

	}

	for ( ; !stack.empty(); postfix.push_back( stack.top() ), stack.pop() );// Clear the stack;


	return postfix;
}

// Postfix to infix function maybe
