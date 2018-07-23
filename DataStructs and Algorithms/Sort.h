#pragma once

#include <vector>
#include <algorithm>
#include <iterator>

template<typename T>
std::vector<T> Merge( std::vector<T>& v, std::vector<T>& u )
{
	std::vector<T> m;
	size_t i = 0, j = 0;
	while ( ( i != v.size() ) && ( j != u.size() ) )
	{
		if ( v[i] < u[j] )
		{
			m.push_back( v [i] );
			++i;
		}
		else
		{
			m.push_back( u [j] );
			++j;
		}
	}

	for ( ; i != v.size(); ++i ) m.push_back( v [i] );
	for ( ; j != u.size(); ++j ) m.push_back( u [j] );

	return m;
}

template<typename T>
std::vector<T>& Merge_Sort( std::vector<T>& v )
{
	size_t mid = v.size() / 2;
	if ( mid > 0 )
	{
		std::vector<T> left_half, right_half; // use std::move for expensive types
		std::copy( std::begin( v ), std::begin( v ) + mid, std::back_inserter( left_half ) );
		std::copy( std::begin( v ) + mid, std::end( v ), std::back_inserter( right_half ) );

		left_half = Merge_Sort( left_half );
		right_half = Merge_Sort( right_half );

		v = Merge( left_half, right_half );

		return v;
	}
	else return v;


}