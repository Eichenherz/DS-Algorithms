#pragma once

#include <string>
#include <unordered_map>
#include <array>
#include <numeric>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cassert>

using doc_vector = std::unordered_map<std::string, int>;

bool Contain_Key( const doc_vector& v, const std::string& key )
{
	return v.find( key ) != v.cend();
}

double	Mag( const doc_vector& v )
{
	double mag = 0.0f;

	for ( const auto& word : v )
	{
		mag += ( word.second * word.second );
	}

	return sqrt( mag );
}

void Translate( std::string& s )
{
	for ( auto& c : s )
		c = std::tolower( c );
}

doc_vector Word_Freq( std::ifstream& is )
{
	doc_vector	vec;
	std::string	input_str;

	is.seekg( 0, std::ios_base::end );
	auto lenght = is.tellg();

	input_str.resize( lenght );
	is.seekg( 0, std::ios_base::beg );
	is.read( &input_str [0], lenght );

	Translate( input_str );

	std::istringstream	str_stream( input_str );
	std::string			token;

	while ( str_stream >> token )
	{
		++vec [token];
	}

	return vec;
}

double Doc_Dist( std::ifstream& f1, std::ifstream& f2 )
{
	doc_vector v1 = Word_Freq( f1 );
	doc_vector v2 = Word_Freq( f2 );

	double mag = Mag(v1) * Mag(v2);
	if ( mag == 0.0f ) return mag;

	double dot_prod = 0.0f;

	for ( const auto& word : v2 )
	{
		if ( Contain_Key(v1,  word.first ) )
		{
			dot_prod += double( word.second * v1 [word.first] );
		}
	}

	return dot_prod / mag;
}