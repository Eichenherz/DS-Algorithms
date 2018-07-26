#pragma once

#include <vector>

template <typename Comp>
class Heap
{
public:
	explicit Heap( size_t capacity = 100 );
	explicit Heap( const std::vector<Comp>& elements );

	bool is_empty() const;
	void insert( const Comp& c );
	void insert( Comp&& c );
	void make_empty();

	virtual const Comp& find_extrema() const;
	virtual void delete_extrema();

protected:
	virtual void build_heap();
	virtual void precolate();

protected:
	size_t					size;
	std::vector<Comp> array;

};

template<typename Comp>
class Max_Heap : public Heap
{

};