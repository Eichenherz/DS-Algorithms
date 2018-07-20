// DataStructsandAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Doc_Dist.h"
#include <iostream>


using namespace std;

int main()
{
	std::ifstream file1( "f1.txt" );
	std::ifstream file2( "f2.txt" );

	auto dist = Doc_Dist( file1, file2 );

	std::cout << "Doc dist is :" << dist * double( 100.0f );
	return 0;
}

