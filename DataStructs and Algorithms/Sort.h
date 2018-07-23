#pragma once

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

template<class Iter>
void Merge_Sort_Recursive( Iter src_beg, Iter src_end, 
						   Iter trg_beg, Iter trg_end )
{
	auto range_lenght = std::distance( src_beg, src_end );
	if ( range_lenght < 2 )
	{
		return;
	}

	auto mid_pt = range_lenght >> 1;
	Iter src_mid = src_beg;
	std::advance( src_mid, mid_pt );
	Iter trg_mid = trg_beg;
	std::advance( trg_mid, mid_pt );

	std::cout << "\n";
	print_test( src_beg, src_mid, src_end, trg_beg, trg_mid, trg_end );

	Merge_Sort_Recursive( trg_beg, trg_mid, src_beg, src_mid );
	Merge_Sort_Recursive( trg_mid, trg_end, src_mid, src_end );

	std::merge( src_beg, src_mid, 
				src_mid, src_end,
				trg_beg );

	std::cout << "\nMerged:\n";
	print_test( src_beg, src_mid, src_end, trg_beg, trg_mid, trg_end );
}

template<class Iter>
void Merge_Sort( Iter beg, Iter end )
{
	using T = typename std::iterator_traits<Iter>::value_type;
	std::vector<T> aux( beg, end );

	Merge_Sort_Recursive( aux.begin(), aux.end(), beg, end );
}

template<class Iter>
void print_test( Iter src_beg, Iter src_mid, Iter src_end,
				 Iter trg_beg, Iter trg_mid, Iter trg_end )
{
	std::cout << "Src : " << "\n";
	for ( auto temp = src_beg; temp != src_mid; ++temp )
	{
		std::cout << *temp << ' ';
	}
	std::cout << ' ' << "Mid :" << *src_mid << ' '<<' ';
	for ( auto temp = src_mid+1; temp != src_end; ++temp )
	{
		std::cout << *temp << ' ';
	}
	std::cout << std::endl;

	std::cout << "Trg : " << "\n";
	for ( auto temp = trg_beg; temp != trg_mid; ++temp )
	{
		std::cout << *temp << ' ';
	}
	std::cout << ' ' << "Mid :" << *trg_mid << ' '<<' ';
	for ( auto temp = trg_mid + 1; temp != trg_end; ++temp )
	{
		std::cout << *temp << ' ';
	}
	std::cout << std::endl;
}