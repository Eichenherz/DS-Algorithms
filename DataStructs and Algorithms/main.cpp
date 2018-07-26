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
	std::vector<int> test { 1,0,0,-12,2,5,64,-88,79,41,15,36,16,43,29,47,81,59,38,3,58,49,66 };

	for ( int e : test )
		std::cout << e << ' ';
	std::cout << std::endl;

	Heapsort( test.begin(), test.end() );

	for ( int e : test )
		std::cout << e << ' ';
	std::cout << std::endl;
	return 0;
}

