// DataStructsandAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"
#include "Stack.h"
#include <iostream>
#include "Algorithms.h"
#include <algorithm>
#include "AVLTree.h"

using namespace std;

int main()
{
	AVLTree<int> t;
	int NUMS = 2000000;
	const int GAP = 37;
	int i;

	cout << "Checking... (no more output means success)" << endl;

	for ( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
		t.insert( i );
	t.remove( 0 );
	for ( i = 1; i < NUMS; i += 2 )
		t.remove( i );

	if ( NUMS < 40 )
		t.printTree();
	if ( t.min() != 2 || t.max() != NUMS - 2 )
		cout << "FindMin or FindMax error!" << endl;

	for ( i = 2; i < NUMS; i += 2 )
		if ( !t.contains( i ) )
			cout << "Find error1!" << endl;

	for ( i = 1; i < NUMS; i += 2 )
	{
		if ( t.contains( i ) )
			cout << "Find error2!" << endl;
	}

	AVLTree<int> t2;
	t2 = t;

	for ( i = 2; i < NUMS; i += 2 )
		if ( !t2.contains( i ) )
			cout << "Find error1!" << endl;

	for ( i = 1; i < NUMS; i += 2 )
	{
		if ( t2.contains( i ) )
			cout << "Find error2!" << endl;
	}

	cout << "End of test..." << endl;
	return 0;
}

