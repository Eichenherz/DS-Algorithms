// DataStructsandAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"
#include <iostream>
#include "Algorithms.h"
#include <algorithm>


int main()
{
	Vector<int> test;
	Generate_Rand_Uniform( test, 10 );
	for ( auto& elem : test )
		std::cout << elem << " ";
	std::cout << std::endl;
	test.insert( test.end() - 1, 666 );
	for ( auto& elem : test )
		std::cout << elem << " ";
	std::cout << std::endl;
	test.erase( test.begin() + 3);
	for ( auto& elem : test )
		std::cout << elem << " ";
	std::cout << std::endl;
	return 0;
}

