// DataStructsandAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"
#include <iostream>
#include "Algorithms.h"
#include <algorithm>


int main()
{
	List<int> test;
	List<int> src;
	Generate_Rand_Uniform( test, 10 );
	Generate_Rand_Uniform( src, 9 );
	for ( auto& elem : test )
		std::cout << elem << " ";
	std::cout << std::endl;
	test.insert( src.end() - 1, 666 );
	for ( auto& elem : test )
		std::cout << elem << " ";
	std::cout << std::endl;
	test.erase( test.begin() + 3);
	for ( auto& elem : test )
		std::cout << elem << " ";
	std::cout << std::endl;
	return 0;
}

