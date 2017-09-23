#pragma once

template<typename T>
class Vector
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	/*
	*
	*/
	explicit Vector( int size = 0 );
			 Vector( const Vector& src );
			 Vector( Vector&& src );
			~Vector();

	Vector&  operator=( const Vector& src );
	Vector&  operator=( Vector&& src );
	T&		 operator[]( const int index );
	const T& operator[]( const int index ) const;


	void	 resize( int n_size );
	void	 reserve( int n_cap );
	void	 push_back( const T& obj );
	void	 pop_back();
	T&		 back();
	const T& back() const;
	bool	 empty() const;
	int		 size() const;
	int		 capacity() const;

	iterator		begin();
	const_iterator	begin();
	iterator		end();
	const_iterator	end();

private:
	T*						p_objects = nullptr;
	int						capacity;
	int						size;
	static constexpr int	SPARE_CAP = 16;
};


/////////////////////////////////////////////////
////			IMPLEMENTATION
template<typename T>
inline Vector<T>::Vector( int size )
	:
	size	 { size },
	capacity { size + SPARE_CAP }
{
	p_objects = new T [capacity];
}

template<typename T>
inline Vector<T>::Vector( const Vector & src )
	:
	size	 { src.size },
	capacity { src.capacity }
{
	p_objects = new T[ capacity ];

	for ( int i = 0; i < size; ++i )
		this [i] = src [i];
}

template<typename T>
inline Vector<T>::Vector( Vector && src )
	:
	size	  { src.size },
	capacity  { src.capacity },
	p_objects { src.p_objects }
{
	src.p_objects = nullptr;
}

template<typename T>
inline Vector<T>::~Vector()
{
	delete[] p_objects;
	p_objects = nullptr;
}

template<typename T>
inline Vector& Vector<T>::operator=( const Vector & src )
{
	this->size = src.size;
	this->capacity = src.capacity;

	delete[] p_objects;
	p_objects = new T [capacity];

	for ( int i = 0; i < size; ++i )
		this [i] = src [i];

	return *this;
}

template<typename T>
inline Vector& Vector<T>::operator=( Vector && src )
{
	this->size = src.size;
	this->capacity = src.capacity;

	delete[] p_objects;
	this->p_objects = src.p_objects;
	src.p_objects = nullptr;

	return *this;
}

template<typename T>
inline T & Vector<T>::operator[]( const int index )
{
	return p_objects [index];
}

template<typename T>
inline const T & Vector<T>::operator[]( const int index ) const
{
	return p_objects [index];
}

template<typename T>
inline void Vector<T>::resize( int n_size )
{
	if ( n_size > capacity )
		reserve( 2 * n_size );
	size = n_size;
}

template<typename T>
inline void Vector<T>::reserve( int n_cap )
{
	if ( n_cap < size ) return;

	T* array = new T [n_cap];
	for ( int i = 0; i < size; ++i )
		array [i] = p_objects [i];

	capacity = n_cap;

	delete[] p_objects;
	p_objects = array;
	array = nullptr;
}

template<typename T>
inline void Vector<T>::push_back( const T & obj )
{
	if ( size == capacity )
		reserve( 2 * capacity + 1 );
	p_objects [size++] = obj;
}

template<typename T>
inline void Vector<T>::pop_back()
{
	--size;
}

template<typename T>
inline T & Vector<T>::back()
{
	return p_objects [size];
}

template<typename T>
inline const T & Vector<T>::back() const
{
	return p_objects [size];
}

template<typename T>
inline bool Vector<T>::empty() const
{
	return (size == 0);
}

template<typename T>
inline int Vector<T>::size() const
{
	return size;
}

template<typename T>
inline int Vector<T>::capacity() const
{
	return capacity;
}

template<typename T>
inline Vector<T>::iterator Vector<T>::begin()
{
	return &( p_objects [0] );
}

template<typename T>
inline Vector<T>::const_iterator Vector<T>::begin()
{
	return &( p_objects [0] );
}

template<typename T>
inline Vector<T>::iterator Vector<T>::end()
{
	return &( p_objects [size + 1] );
}

template<typename T>
inline Vector<T>::const_iterator Vector<T>::end()
{
	return &( p_objects [size + 1] );
}
