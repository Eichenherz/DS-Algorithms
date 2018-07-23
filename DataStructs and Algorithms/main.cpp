// DataStructsandAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sort.h"
#include "Algorithms.h"
#include <iostream>
#include <random>


using namespace std;

int main()
{
	std::vector<int> test {1,0,0,-12,64,2,5,-88};

	/*
	std::mt19937 rng( std::random_device {}( ) );
	std::uniform_int_distribution<int> dist;
	int n_obj = 8;
	if ( n_obj % 2 == 0 )
	{
	std::uniform_int_distribution<int> dist( -n_obj / 2, n_obj / 2 );
	for ( ; n_obj != 0; --n_obj )
	test.push_back( dist( rng ) );
	}

	else
	{
	std::uniform_int_distribution<int> dist( -( n_obj + 1 ) / 2, n_obj / 2 );
	for ( ; n_obj != 0; --n_obj )
	test.push_back( dist( rng ) );
	}
	*/

	for ( int e : test )
		std::cout << e << ' ';
	std::cout << std::endl;

	Merge_Sort( test.begin(), test.end() );

	for ( int e : test )
		std::cout << e << ' ';
	std::cout << std::endl;
	return 0;
}

