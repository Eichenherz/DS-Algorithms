// DataStructsandAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vector.h"
#include <iostream>


int main()
{
	Vector<int> v_test;
	std::cout << v_test.capacity() <<" " << v_test.size() << std::endl;
	v_test.reserve( 100 );
	std::cout << v_test.capacity() << " " << v_test.size() << std::endl;
	for ( int i = 0; i < (v_test.capacity() / 5); ++i )
		v_test.push_back( i % 5 );
	for ( int i = 0; i < v_test.size(); ++i )
		std::cout << v_test [i] << " ";
	std::cout<< std::endl;
	std::cout << v_test.back() << std::endl;
	std::cout << v_test.capacity() << " " << v_test.size() << std::endl;
	v_test.pop_back();
	v_test.pop_back();
	v_test.pop_back();
	for ( int i = 0; i < v_test.size(); ++i )
		std::cout << v_test [i] << " ";
	std::cout << std::endl;
	std::cout << v_test.back() << std::endl;
	std::cout << v_test.capacity() << " " << v_test.size() << std::endl;
	v_test.resize( 15 );
	for ( int i = 0; i < v_test.size(); ++i )
		std::cout << v_test [i] << " ";
	std::cout << std::endl;
	std::cout << v_test.back() << std::endl;
	std::cout << v_test.capacity() << " " << v_test.size() << std::endl;
    return 0;
}

