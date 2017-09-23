#pragma once

//////////////////////////////////////
////******************************////
////       Vector CONTAINER       ////
////******************************////
//////////////////////////////////////
////  TODO: add assertions & 
////                  extra polish
//////////////////////////////////////
template<typename T>
class Vector
{
public:
	typedef		  T* iterator;
	typedef const T* const_iterator;
	/**
	**
	**/
	explicit Vector( int size = 0 );
			 Vector( const Vector& src );
			 Vector( Vector&& src );
			~Vector();

	Vector<T>&  operator=( const Vector& src );
	Vector<T>&  operator=( Vector&& src );
	T&			operator[]( const int index );
	const T&	operator[]( const int index ) const;


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
	const_iterator	c_begin();
	iterator		end();
	const_iterator	c_end();

private:
	T*						p_objects = nullptr;
	int						cap;
	int						lenght;
	static constexpr int	SPARE_CAP = 16;
};


/////////////////////////////////////////////////
////			IMPLEMENTATION
template<typename T>
inline Vector<T>::Vector( int size )
	:
	lenght { size },
	cap	   { size + SPARE_CAP }
{
	p_objects = new T [cap];
}

template<typename T>
inline Vector<T>::Vector( const Vector & src )
	:
	lenght { src.lenght },
	cap	   { src.cap }
{
	p_objects = new T[ cap ];

	for ( int i = 0; i < lenght; ++i )
		this [i] = src [i];
}

template<typename T>
inline Vector<T>::Vector( Vector && src )
	:
	lenght	  { src.lenght },
	cap		  { src.cap },
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
inline Vector<T>& Vector<T>::operator=( const Vector & src )
{
	this->lenght = src.lenght;
	this->cap = src.cap;

	delete[] p_objects;
	p_objects = new T [cap];

	for ( int i = 0; i < lenght; ++i )
		this [i] = src [i];

	return *this;
}

template<typename T>
inline Vector<T>& Vector<T>::operator=( Vector && src )
{
	this->lenght = src.lenght;
	this->cap = src.cap;

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
	if ( n_size > cap )
		reserve( 2 * n_size );
	lenght = n_size;
}

template<typename T>
inline void Vector<T>::reserve( int n_cap )
{
	if ( n_cap < lenght ) return;

	T* array = new T [n_cap];
	for ( int i = 0; i < lenght; ++i )
		array [i] = p_objects [i];

	cap = n_cap;

	delete[] p_objects;
	p_objects = array;
	array = nullptr;
}

template<typename T>
inline void Vector<T>::push_back( const T & obj )
{
	if ( lenght == cap )
		reserve( 2 * cap + 1 );
	p_objects [lenght++] = obj;
}

template<typename T>
inline void Vector<T>::pop_back()
{
	if ( !empty() )
		--lenght;
}

template<typename T>
inline T & Vector<T>::back()
{
	return p_objects [lenght - 1];
}

template<typename T>
inline const T & Vector<T>::back() const
{
	return p_objects [lenght - 1];
}

template<typename T>
inline bool Vector<T>::empty() const
{
	return ( lenght == 0);
}

template<typename T>
inline int Vector<T>::size() const
{
	return lenght;
}

template<typename T>
inline int Vector<T>::capacity() const
{
	return cap;
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::begin()
{
	return &( p_objects [0] );
}

template<typename T>
inline typename Vector<T>::const_iterator Vector<T>::c_begin()
{
	return &( p_objects [0] );
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::end()
{
	return &( p_objects [lenght] );
}

template<typename T>
inline typename Vector<T>::const_iterator Vector<T>::c_end()
{
	return &( p_objects [lenght] );
}
