#pragma once


template<typename T>
class Queue
{
public:
	 Queue();
	 Queue( const Queue& q );
	~Queue();
	Queue& operator=( const Queue& q ) = delete;

	void	push( const T& elem );
	void	pop();
	T&		front();
	T&		back();
	int		size() const;
	bool	empty() const;


private:
	class			Element
	{
	public:
		Element( const T& data, const Element& next = nullptr )
			:
			Data { data },
			p_next { below }
		{}
		Element( const Element& e )
			:
			Data { e.Data }//
		{
			if ( e.p_next != nullptr )
				p_next = new Element( *e.p_next );
		}
		~Element()
		{
			delete p_next;
			p_next = nullptr;
		}
		Element& operator=( const Element& e ) = delete;

		int  count() const
		{
			if ( p_next == nullptr )
				return 1;
			return p_next->count() + 1;
		}
		T	 data() const
		{
			return Data;
		}

	private:
		Element*	p_next;
		T			Data;
	};
	Element*		p_top;
	Element*		p_rear;
};

template<typename T>
inline Queue<T>::Queue()
	:
	p_top	{ nullptr },
	p_rear	{ nullptr }
{}

template<typename T>
inline Queue<T>::Queue( const Queue & q )
{
	if ( !empty() )
	{
		delete p_rear;
		delete p_top;
		p_top = p_rear = nullptr;
	}

	if ( !q.empty() )
	{
		if ( empty() )
		{
			p_rear = new Element( elem, p_rear );
			p_top = p_rear;
		}
		else
			p_rear = new Element( elem, p_rear );
	}
}

template<typename T>
inline Queue<T>::~Queue()
{
	delete p_rear;
	delete p_top;
	p_top = p_rear = nullptr;
}

template<typename T>
inline void Queue<T>::push( const T & elem )
{
	if ( empty() )
	{
		p_rear = new Element( elem, p_rear );
		p_top = p_rear;
	}
	else
		p_rear = new Element( elem, p_rear );
}

template<typename T>
inline void Queue<T>::pop()
{
	if ( !empty() )
	{
		auto p = p_top;
		p_top = p_rear + size() - 2;
		delete p;
	}
}

template<typename T>
inline T & Queue<T>::front()
{
	return *p_top;
}

template<typename T>
inline T & Queue<T>::back()
{
	return *p_rear;
}

template<typename T>
inline int Queue<T>::size() const
{
	return p_top->count();
}

template<typename T>
inline bool Queue<T>::empty() const
{
	return p_top == nullptr;
}
