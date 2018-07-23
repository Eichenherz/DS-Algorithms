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
	std::vector<int> test;

	std::mt19937 rng( std::random_device {}( ) );
	std::uniform_int_distribution<int> dist;
	int n_obj = 10;
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

	for ( int e : test )
		std::cout << e << ' ';
	std::cout << std::endl;

	test = Merge_Sort( test );

	for ( int e : test )
		std::cout << e << ' ';
	std::cout << std::endl;
	return 0;
}

