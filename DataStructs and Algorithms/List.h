#pragma once

#include <assert.h>
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
	template<class T>
	class	iterator_
	{
	public:
					iterator_(struct Node* p = nullptr )
			:
			p_node { p }
		{}

		bool		operator==( const iterator_& ref ) const
		{
			return ( p_node == ref.p_node );
		}
		bool		operator!=( const iterator_& ref ) const
		{
			return !( *this == ref );
		}

		iterator_&	operator++()
		{
			this->p_node = p_node->next;
			return *this;
		}
		iterator_&	operator++( int )
		{
			iterator_ temp = *this;
			++( *this );
			return temp;
		}
		iterator_&	operator--()
		{
			this->p_node = p_node->prev;
			return *this;
		}
		iterator_&	operator--( int )
		{
			iterator_ temp = *this;
			--( *this );
			return temp;
		}
		iterator_	operator-( int n ) const
		{
			auto temp = *this;
			for ( int i = n; i > 0; --i ) --temp;

			return temp;
		}
		iterator_	operator+( int n ) const
		{
			auto temp = *this;
			for ( int i = 0; i < n; ++i ) ++temp;

			return temp;
		}
		T&			operator*() 
		{
			return p_node->data;
		}

	private:
		struct Node* p_node;
		
		friend class List<T>;
	};
	template<class T>
	class	reverse_iterator_ : public iterator_<T>
	{
	public:
		reverse_iterator_&	operator--()
		{
			this->p_node = p_node->next;
			return *this;
		}
		reverse_iterator_&	operator--( int )
		{
			iterator_ temp = *this;
			++( *this );
			return temp;
		}
		reverse_iterator_&	operator++()
		{
			this->p_node = p_node->prev;
			return *this;
		}
		reverse_iterator_&	operator++( int )
		{
			iterator_ temp = *this;
			--( *this );
			return temp;
		}
		reverse_iterator_	operator+( int n ) const
		{
			auto temp = *this;
			for ( int i = n; i > 0; --i ) --temp;

			return temp;
		}
		reverse_iterator_	operator-( int n ) const
		{
			auto temp = *this;
			for ( int i = 0; i < n; ++i ) ++temp;

			return temp;
		}
	};

	using	iterator = iterator_<T>;
	using	const_iterator = iterator_<const T>;
	using	reverse_iterator = reverse_iterator_<T>;
	
	/**
	**
	**/
						List();
						List( const List& other );
						~List();
	List<T>&			operator=( const List& other );

	T&					back();
	const T&			back() const;
	T&					front();
	const T&			front() const;

	void				push_back( const T& elem );
	void				push_front( const T& elem );
	void				pop_back();
	void				pop_front();
	iterator			insert( iterator pos, const T & elem );
	iterator			erase( iterator pos );
	void				clear();
	void				splice( iterator pos, List& src );

	int					size() const;
	bool				empty() const;

	iterator			begin();
	const_iterator		cbegin() const;
	reverse_iterator	rbegin();
	iterator			end();
	const_iterator		cend() const;
	reverse_iterator	rend();


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
List<T>::List()
	:
	head	( new Node() ),
	tail	( new Node() ),
	lenght	( 0 )
{
	head->next = tail;
	tail->prev = head;
}

template<typename T>
List<T>::List( const List & other )
{
	*this = other;
}

template<typename T>
List<T>::~List()
{
	clear();
	delete head;
	delete tail;
	tail = head = nullptr;
}

template<typename T>
List<T>& List<T>::operator=( const List & other )
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
T& List<T>::back()
{
	return ( tail->prev ).data;
}

template<typename T>
const T& List<T>::back() const
{
	return ( tail->prev ).data;
}

template<typename T>
T& List<T>::front()
{
	return ( head->next ).data;
}

template<typename T>
const T& List<T>::front() const
{
	return ( head->next ).data;
}

template<typename T>
void List<T>::push_back( const T & elem )
{
	auto temp = new Node( elem, tail->prev, tail );
	tail->prev->next = temp;
	tail->prev = temp;
	++lenght;
}

template<typename T>
void List<T>::push_front( const T & elem )
{
	auto temp = new Node( elem, head, head->next );
	head->next->prev = temp;
	head->next = temp;
	++lenght;
}

template<typename T>
void List<T>::pop_back()
{
	auto temp = tail->prev;
	tail->prev = temp->prev;
	temp->prev->next = tail;

	delete temp;
	--lenght;
}

template<typename T>
void List<T>::pop_front()
{
	auto temp = head->next;
	head->next = temp->next;
	temp->next->prev = head;

	delete temp;
	--lenght;
}

template<typename T>
typename List<T>::iterator List<T>::insert( typename List<T>::iterator pos, const T & elem )
{
	auto temp = new Node( elem, pos.p_node->prev, pos.p_node );

	pos.p_node->prev->next = temp;
	pos.p_node->prev = temp;
	++lenght;

	return iterator { temp };
}

template<typename T>
typename List<T>::iterator List<T>::erase( typename List<T>::iterator pos )
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
void List<T>::clear()
{
	while ( !empty() )
		pop_back();
}

template<typename T>
void List<T>::splice( iterator pos, List & src )
{
	assert( this != &src );

	src.head->next->prev = pos.p_node->prev;
	pos.p_node->prev->next = src.head->next;

	src.tail->prev->next = pos.p_node;
	pos.p_node->prev = src.tail->prev;

	src.head->next = src.tail;
	src.tail->prev = src.head;
}

template<typename T>
int List<T>::size() const
{
	return lenght;
}

template<typename T>
bool List<T>::empty() const
{
	return lenght == 0;
}

template<typename T>
typename List<T>::iterator List<T>::begin()
{
	return iterator { head->next };
}

template<typename T>
typename List<T>::const_iterator List<T>::cbegin() const
{
	return const_iterator { head->next };
}

template<typename T>
typename List<T>::reverse_iterator List<T>::rbegin()
{
	return reverse_iterator { tail->prev };
}

template<typename T>
typename List<T>::iterator List<T>::end()
{
	return iterator { tail };
}

template<typename T>
typename List<T>::const_iterator List<T>::cend() const
{
	return const_iterator { tail };
}

template<typename T>
typename List<T>::reverse_iterator List<T>::rend()
{
	return reverse_iterator { head };
}

