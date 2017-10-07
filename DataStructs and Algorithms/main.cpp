// DataStructsandAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"
#include <iostream>
#include "Algorithms.h"
#include <algorithm>


int main()
{
	List<int> A;
	List<int> B;
	
	A.push_back(1);
	A.push_back(4);
	A.push_back(7);
	A.push_back(13);
	A.push_back(25);
	B.push_back(1);
	B.push_back(3);
	B.push_back(6);
	B.push_back(8);
	B.push_back(10);
	B.push_back( 13 );
	B.push_back( 19 );
	B.push_back( 25 );
	B.push_back( 30 );


	//Generate_Rand_Uniform( A, 6 );
	//std::sort( A.begin(), A.end() );
	//Generate_Rand_Uniform( B, 4 );
	//std::sort( B.begin(), B.end() );
	


	auto A__B = intersection( A, B );
	auto A_U_B = reunion( A, B );

	for ( auto itr = A__B.cbegin(); itr != A__B.cend(); ++itr )
		std::cout << *itr << " ";
	std::cout << std::endl;
	for ( auto itr = A_U_B.cbegin(); itr != A_U_B.cend(); ++itr )
		std::cout << *itr << " ";
    return 0;
}

