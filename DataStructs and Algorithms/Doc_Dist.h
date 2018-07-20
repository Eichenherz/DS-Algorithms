#pragma once

#include <string>
#include <unordered_map>
#include <array>
#include <numeric>
#include <cctype>
#include <algorithm>
#include <istream>
#include <sstream>

struct doc_vector
{
	std::unordered_map<std::string, int> v;

	bool	Contain_Key( const std::pair<const std::string&, int> key ) const
	{
		return v.find( key.first ) != v.cend();
	}
	double	Mag() const
	{
		double mag = 0.0f;

		for ( const auto& word : v )
		{
			mag += ( word.second * word.second );
		}

		return sqrt( mag );
	}
};

class Formatter
{
public:
	void operator()( std::string& raw_string )
	{
		transform( raw_string.begin(), raw_string.end(), raw_string.begin(),
				   [this]( unsigned char c )
				   {
					   return table [c];
				   } );
	}

private:
	class Xlat_Table
	{
	public:
		Xlat_Table()
		{
			for ( int i = 0; i < table_size; ++i )
			{
				if ( std::isalpha( i ) ) table [i] = std::tolower( i );
				else if ( std::isdigit( i ) ) table [i] = i;
				else table [i] = ' ';
			}
		}

		unsigned char operator[]( size_t i )
		{
			return table [i];
		}

	private:
		static const int table_size = std::numeric_limits<unsigned char>::max();
		std::array<unsigned char, table_size> table;
	};

	static Xlat_Table table;
};

doc_vector Word_Freq( std::istream& is )
{
	doc_vector	vec;
	std::string	input_str;

	is.seekg( 0, std::ios::end );
	size_t lenght = is.tellg();
	is.seekg( 0, std::ios::beg );
	is.read( &input_str [0], lenght );

	Formatter( input_str );
	
	std::istringstream	str_stream( input_str );
	std::string			token;

	while ( str_stream >> token )
	{
		++vec.v [token];
	}

	return vec;
}

double Doc_Dist( std::istream& f1, std::istream& f2 )
{
	doc_vector v1 = Word_Freq( f1 );
	doc_vector v2 = Word_Freq( f2 );

	double mag = v1.Mag() * v2.Mag();
	double dot_prod = 0.0f;

	for ( const auto& word : v2.v )
	{
		if ( v1.Contain_Key( word ) )
		{
			dot_prod += double( word.second * v1.v [word.first] );
		}
	}

	return dot_prod / mag;
}