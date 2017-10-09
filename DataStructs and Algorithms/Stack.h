#pragma once

template<typename T> 
class Stack
{
public:
	 Stack();
	 Stack( const Stack& s );
	~Stack();
	Stack& operator=( const Stack& s ) = delete;

	void	push(  T& data );
	void	pop();
	T		top();
	int		size() const;
	bool	empty() const;

private:
	class			Element
	{
	public:
		  Element(  T& data, Element* below = nullptr )
			  :
			  Data		{ data },
			  p_next	{ below }
		  {}
		  Element( const Element& e )
			  :
			  Data   { e.Data }
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

		friend Stack<T>;
	};
	Element*		p_top;

};

template<typename T>
inline Stack<T>::Stack()
	:
	p_top { nullptr }
{}

template<typename T>
inline Stack<T>::Stack( const Stack & s )
{
	if ( !empty() )
	{
		delete p_top;
		p_top = nullptr;
	}

	if ( !s.empty() )
		p_top = new Element( *s.p_top );
}

template<typename T>
inline Stack<T>::~Stack()
{
	delete p_top;
	p_top = nullptr;
}

template<typename T>
inline void Stack<T>::push(  T & data )
{
	p_top = new Element( data, p_top );
}

template<typename T>
inline void Stack<T>::pop()
{
	if ( !empty() )
	{
		auto p = p_top;
		auto p_temp = p_top->p_next;

		p_top->p_next = nullptr; // VERY IMPORTANT ! Otherwise all stack gets cleared !
		p_top = p_temp;

		delete p;
	}
}

template<typename T>
inline T Stack<T>::top()
{
	return p_top->data();
}

template<typename T>
inline int Stack<T>::size() const
{
	if ( !empty() )
		return p_top->count();
	return 0;
}

template<typename T>
inline bool Stack<T>::empty() const
{
	return ( p_top == nullptr );
}

