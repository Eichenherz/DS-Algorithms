#pragma once

//////////////////////////////////////
////******************************////
////        List CONTAINER        ////
////******************************////
//////////////////////////////////////
////  TODO: add assertions & 
////                  extra polish
////				& testing
//////////////////////////////////////
template<typename T>
class List
{
public:
	class const_iterator
	{
	public:
		const_iterator()
			:
			p_node{ nullptr }
		{}

		bool					operator==( const const_iterator& ref ) const
		{
			return ( p_node == ref.p_node );
		}
		bool					operator!=( const const_iterator& ref ) const
		{
			return !( *this == ref );
		}

		const const_iterator&	operator++()
		{
			this->p_node = p_node->next;
			return *this;
		}
		const const_iterator&	operator++( int )
		{
			const const_iterator temp = *this;
			++( *this );
			return temp;
		}
		const const_iterator&	operator--()
		{
			this->p_node = p_node->prev;
			return *this;
		}
		const const_iterator&	operator--( int )
		{
			const const_iterator temp = *this;
			--( *this );
			return temp;
		}
		const const_iterator	operator-( int n ) const
		{
			auto temp = *this;
			for ( int i = n; i > 0; --i ) --temp;

			return temp;
		}
		const const_iterator	operator+( int n ) const
		{
			auto temp = *this;
			for ( int i = 0; i < n; ++i ) ++temp;

			return temp;
		}
		const T&				operator*() const
		{
			return p_node->data;
		}

	protected:
		struct Node* p_node;
		const_iterator( Node* p )
			:
			p_node(p)
		{}
		friend class List<T>;
	};
	class iterator : public const_iterator
	{
	public:
		iterator()
		{}
		
		iterator&	operator++()
		{
			this->p_node = p_node->next;
			return *this;
		}
		iterator&	operator++( int )
		{
			iterator temp = *this;
			++( *this );
			return temp;
		}
		iterator&	operator--()
		{
			this->p_node = p_node->prev;
			return *this;
		}
		iterator&	operator--( int )
		{
			iterator temp = *this;
			--( *this );
			return temp;
		}
		iterator	operator-( int n )
		{
			auto temp = *this;
			for ( int i = n; i > 0; --i ) --temp;

			return temp;
		}
		iterator	operator+( int n )
		{
			auto temp = *this;
			for ( int i = 0; i < n; ++i ) ++temp;

			return temp;
		}
		T&			operator*()
		{
			return p_node->data;
		}
		
	protected:
		iterator( Node* p )
			:
			const_iterator{ p }
		{}
		friend class List<T>;
	};
	/**
	**
	**/
	 List();
	 List( const List& other );
	~List();
	List<T>& operator=( const List& other );

	T&		 back();
	const T& back() const;
	T&		 front();
	const T& front() const;

	void push_back( const T& elem );
	void push_front( const T& elem );
	void pop_back();
	void pop_front();

	iterator insert( iterator pos, const T & elem );
	iterator erase( iterator pos );
	void	 clear();

	int	 size() const;
	bool empty() const;

	iterator		begin();
	const_iterator	cbegin() const;
	iterator		end();
	const_iterator	cend() const;


private:
	struct	Node
	{
		Node( const T&	obj = T {},
			  Node*		p = nullptr, 
			  Node*		n = nullptr ) :
			data( obj ),
			prev( p ),
			next( n )
		{}
		
		T		data;
		Node*	prev;
		Node*	next;
	};
	Node*	head;
	Node*	tail;
	int		lenght;

};

template<typename T>
inline List<T>::List()
	:
	head	( new Node() ),
	tail	( new Node() ),
	lenght	( 0 )
{
	head->next = tail;
	tail->prev = head;
}

template<typename T>
inline List<T>::List( const List & other )
{
	*this = other;
}

template<typename T>
inline List<T>::~List()
{
	clear();
	delete head;
	delete tail;
	tail = head = nullptr;
}

template<typename T>
inline List<T> & List<T>::operator=( const List & other )
{
	clear();

	head = new Node();
	tail = new Node();
	lenght = 0;

	head->next = tail;
	tail->prev = head;

	for ( auto iter = other.cbegin(); iter != other.cend(); ++iter )
		this->push_back( *iter );

	return *this;
}

template<typename T>
inline T & List<T>::back()
{
	return ( tail->prev ).data;
}

template<typename T>
inline const T & List<T>::back() const
{
	return ( tail->prev ).data;
}

template<typename T>
inline T & List<T>::front()
{
	return ( head->next ).data;
}

template<typename T>
inline const T & List<T>::front() const
{
	return ( head->next ).data;
}

template<typename T>
inline void List<T>::push_back( const T & elem )
{
	auto temp = new Node( elem, tail->prev, tail );
	tail->prev->next = temp;
	tail->prev = temp;
	++lenght;
}

template<typename T>
inline void List<T>::push_front( const T & elem )
{
	auto temp = new Node( elem, head, head->next );
	head->next->prev = temp;
	head->next = temp;
	++lenght;
}

template<typename T>
inline void List<T>::pop_back()
{
	auto temp = tail->prev;
	tail->prev = temp->prev;
	temp->prev->next = tail;

	delete temp;
	--lenght;
}

template<typename T>
inline void List<T>::pop_front()
{
	auto temp = head->next;
	head->next = temp->next;
	temp->next->prev = head;

	delete temp;
	--lenght;
}

template<typename T>
inline typename List<T>::iterator List<T>::insert( typename List<T>::iterator pos, const T & elem )
{
	auto temp = new Node( elem, pos.p_node->prev, pos.p_node );

	pos.p_node->prev->next = temp;
	pos.p_node->prev = temp;
	++lenght;

	return iterator { temp };
}

template<typename T>
inline typename List<T>::iterator List<T>::erase( typename List<T>::iterator pos )
{
	auto temp = pos.p_node;
	iterator iter { temp->next };

	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	--lenght;

	delete temp;
	return iter;
}

template<typename T>
inline void List<T>::clear()
{
	while ( !empty() )
		pop_back();
}

template<typename T>
inline int List<T>::size() const
{
	return lenght;
}

template<typename T>
inline bool List<T>::empty() const
{
	return lenght == 0;
}

template<typename T>
inline typename List<T>::iterator List<T>::begin()
{
	return iterator { head->next };
}

template<typename T>
inline typename List<T>::const_iterator List<T>::cbegin() const
{
	return const_iterator { head->next };
}

template<typename T>
inline typename List<T>::iterator List<T>::end()
{
	return iterator { tail };
}

template<typename T>
inline typename List<T>::const_iterator List<T>::cend() const
{
	return const_iterator { tail };
}

