#pragma once

//////////////////////////////////////
////******************************////
////        List CONTAINER        ////
////******************************////
//////////////////////////////////////
////  TODO: add assertions & 
////                  extra polish
//////////////////////////////////////
template<typename T>
class List
{
public:
	 List();
	 List( const List& other );
	~List();
	List& operator=( const List& other );

	T&		 back();
	const T& back() const;
	T&		 front();
	const T& front() const;

	void push_back( const T& elem );
	void push_front( const T& elem );
	void insert( const T& elem, const int pos );
	void pop_back();
	void pop_front();
	void erase( const int pos );

	void clear();

	int	 size() const;
	bool empty() const;

	bool operator==( const List& other ) const;
	bool operator!=( const List& other ) const;

	class const_iterator
	{};
	class iterator : const_iterator
	{};

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
	head(new Node()),
	tail(new Node())
{
	head.next = tail;
	tail.prev = head;
}

template<typename T>
inline List<T>::List( const List & other )
{
}

template<typename T>
inline List<T>::~List()
{
}

template<typename T>
inline List & List<T>::operator=( const List & other )
{
	// TODO: insert return statement here
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
}

template<typename T>
inline void List<T>::push_front( const T & elem )
{
	auto temp = new Node( elem, head, head->next );
	head->next->prev = temp;
	head->next = temp;
}

template<typename T>
inline void List<T>::insert( const T & elem, const int pos )
{
	//Iter
}

template<typename T>
inline void List<T>::pop_back()
{
	auto temp = tail->prev;
	tail->prev = temp->prev;
	temp->prev->next = tail;

	delete temp;
}

template<typename T>
inline void List<T>::pop_front()
{
	auto temp = head->next;
	head->next = temp->next;
	temp->next->prev = head;

	delete temp;
}

template<typename T>
inline void List<T>::erase( const int pos )
{
	//Iter
}

template<typename T>
inline void List<T>::clear()
{
}

template<typename T>
inline int List<T>::size() const
{
	return 0;
}

template<typename T>
inline bool List<T>::empty() const
{
	return lenght == 0;
}

