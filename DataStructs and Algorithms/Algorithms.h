#pragma once

#include "List.h"
#include "Vector.h"
#include <iostream>
#include <random>
#include <math.h>

//To be made template
void Print_Lots( const List<int>& l, const List<int>& p )
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
template<typename Iter, typename T>
typename List<T>::iterator find( Iter begin, Iter end, const T& obj )
{
	for ( ; begin != end; ++begin )
		if ( *begin == obj ) return begin;
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
int josephus_M( int N, int M )
{
	if ( M == 0 ) return N;


}

//Just for Vectors of ints
void Generate_Rand_Uniform( Vector<int>& list, int n_obj )
{
	std::mt19937 rng( std::random_device {}( ) );
	std::uniform_int_distribution<int> dist;
	if ( n_obj % 2 == 0 )
	{
		std::uniform_int_distribution<int> dist( -n_obj / 2, n_obj / 2 );
		for ( ; n_obj != 0; --n_obj )
			list.push_back( dist( rng ) );
	}

	else
	{
		std::uniform_int_distribution<int> dist( -( n_obj + 1 ) / 2, n_obj / 2 );
		for ( ; n_obj != 0; --n_obj )
			list.push_back( dist( rng ) );
	}

}