#pragma once

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <array>

/*
/======================
/		MERGE SORT
/======================
*/
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

template<class Iter>
void Mergesort( Iter beg, Iter end )
{
	const auto range = std::distance( beg, end );
	if ( range < 2 )
	{
		return;
	}
	Iter mid = beg;
	std::advance( mid, range >> 1 );

	Mergesort( beg, mid );
	Mergesort( mid, end );

	std::inplace_merge( beg, mid, end );
}
/*
/======================
/		HEAP SORT
/======================
*/
template<class Iter>
void Heapsort( Iter begin, Iter end )
{
	using dist_type = typename std::iterator_traits<Iter>::difference_type;
	const dist_type size = end - begin;

	//Build heap
	for ( auto index = ( size - 1 ) >> 1; index >= 0; --index )
	{
		Precolate( begin, index, size );
	}

	//Sort heap
	for ( auto index = size - 1; index > 0; --index )
	{
		std::swap( begin [0], begin [index] );
		Precolate( begin, 0, index );
	}
	
}

template<class Iter, typename Idx, typename Dist>
void Precolate( Iter iter, Idx idx, Dist dist )
{
	Idx		child = ( idx << 1 ) + 1;

	if ( dist <= child )
	{
		return;
	}
	if ( ( child + 1 < dist ) && ( iter [child] < iter [child + 1] ) )
	{
		++child;
	}
	if ( !( iter [idx] < iter [child] ) )
	{
		return;
	}
	
	std::swap( iter [idx], iter [child] );
	Precolate( iter, child, dist );
}

template<class Iter>
void print_( Iter begin, Iter end )
{
	std::cout << '\n';
	for ( auto iter = begin; iter != end; ++iter )
	{
		std::cout << *iter << ' ';
	}
	std::cout << '\n';
}
/*
/======================
/	  RADIX SORT
/======================
*/
// How to sort 10^6 32-bit unsigend ints
template<class Iter>
void Radixsort( Iter beg, Iter end )
{
	using val_type	= typename std::iterator_traits<Iter>::value_type;
	const auto lenght = std::distance( beg, end );


	constexpr int base = 0x100;    // base 2^8 == 256
	constexpr int bit_mask = 0xFF; // 11111111 in binary
	std::array<size_t, base> lsb_array = {};

	
	for ( auto shift = 0, _32bits = 32; shift != _32bits; shift += 8 ) 
	{
		lsb_array.clear();
		for ( auto it = beg; it != end; ++it )
		{
			const auto idx = ( *it >> shift ) & bit_mask;
			++lsb_array [idx];
		}
	}

	// To be completed....
}

/*
/======================
/	INSERTION SORT
/======================
*/

/*
/======================
/	  QUICK SORT
/======================
*/

template<class Iter>
void Quicksort( Iter beg, Iter end )
{

	if ( std::distance( beg, end )  < 2 ) return;

	get_pivot( beg, end ); // position( Pivot ) == beg;
	auto pivot_pt = make_partition( beg, end );

	Quicksort( beg, pivot_pt );
	Quicksort( std::next( pivot_pt ), end );

}

template<class Iter>
void get_pivot( Iter beg, Iter end )
{
	const auto mid_pt = std::distance( beg, end ) >> 1;
	auto mid = std::next( beg, mid_pt );

	// Compute median of 3; // Won't work for 2 elements
	auto med3 = std::max( std::min( *beg, *mid ),
						  std::min( std::max( *beg, *mid ), *( end - 1 ) ) ); 
	// Move median to beg;
	if ( med3 == *mid )
	{
		std::iter_swap( mid, beg );
	}
	else if ( med3 == *( end - 1 ) )
	{
		std::iter_swap( end - 1, beg );
	}
}

template<class Iter>
auto make_partition( Iter beg, Iter end )
{
	const auto pivot = *beg;

	auto p_beg = std::next( beg );
	std::advance( end, -1 );

	for ( ;; )
	{
		while ( *p_beg < pivot && p_beg < end )
		{
			++p_beg;
		}
		while ( *end > pivot && p_beg < end )
		{
			--end;
		}
		if ( p_beg < end )
		{
			std::iter_swap( p_beg, end );
		}
		else
		{
			break;
		}
	}

	if ( *p_beg > pivot && *end < pivot )
	{
		std::iter_swap( p_beg, end );
	}

	while ( *beg < *p_beg )
	{
		std::advance( p_beg, -1 );
	}

	std::iter_swap( beg, p_beg );

	return p_beg;
}

