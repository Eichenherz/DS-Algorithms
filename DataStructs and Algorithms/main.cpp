// DataStructsandAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"
#include "Stack.h"
#include <iostream>
#include "Algorithms.h"
#include <algorithm>


int main()
{
	auto postfix = To_Postfix( "6 * ( 2 + 3 + (5 * 8) + 3 )" );
	std::cout << postfix << std::endl;
	std::cout << Postfix_Eval( postfix );
	return 0;
}

