#pragma once

#include <assert.h>

template <typename T>
class Threaded_BST
{
	struct Node;
public:
					Threaded_BST();
					Threaded_BST( const Threaded_BST& tree );
					~Threaded_BST();
	Threaded_BST&	operator=( const Threaded_BST& tree );

	const T&	min() const;
	const T&	max() const;

	bool		contains( const T& obj ) const;
	bool		empty() const;

	void		insert( const T& obj );
	void		remove( const T& obj );
	void		clear( Node*& p_node );
	//print tree
	void printTree() const
	{
		if ( empty() )
			cout << "Empty tree" << endl;
		else
			printTree( root );
	}
private:
	class Node
	{
	public:
				Node( const T& obj, Node* lnode = nullptr, Node* rnode = nullptr )
			:
			object			{ obj },
			left			{ lnode },
			right			{ rnode },
			right_threaded	{ false }
		{}
				Node( const Node& ref )
			:
			object			{ ref.object },
			right_threaded	{ false }
		{
			if ( ref.left != nullptr ) left = new Node { *ref.left };
			if ( ref.right != nullptr ) right = new Node { *ref.right };
		}
				~Node()
		{
			delete left;
			left = nullptr;
			delete right;
			right = nullptr;
		}
		Node&	operator=( const Node& ) = delete;


		void	Add( const T& obj )
		{
			if ( obj < this->object )
			{
				if ( this->left == nullptr )
				{
					this->left = new Node { obj };
					this->left->right = this;
					this->left->right_threaded = true;
				}
				else return left->Add( obj );
			}
			else if ( obj > this->object )
			{
				if ( this->right == nullptr )
				{
					this->right = new Node { obj };
				}
				else if ( this->right_threaded == true )
				{
					auto temp = this->right;
					this->right = new Node { obj };
					this->right->right = temp;
				}
				else return right->Add( obj );
			}
		}
		void	Del( const T& obj )
		{

		}
		bool	Contains( const T& obj ) const
		{
			if ( obj == this->object ) return true;
			else if ( obj < this->object )
			{
				if ( left == nullptr ) return false;
				else return left->Contains( obj );
			}
			else if ( this->object < obj )
			{
				if ( right == nullptr ) return false;
				else return right->Contains( obj );
			}

			return false;
		}

	private:
		T		object;
		Node*	left;
		Node*	right;
		bool	right_threaded;
	};

	Node* root;

	/* Encapsulating recursion */
	Node*	Min_Node( Node* p_node ) const;
	Node*	Max_Node( Node* p_node ) const;
};

template<typename T>
Threaded_BST<T>::Threaded_BST()
	:
	root { nullptr }
{}

template<typename T>
Threaded_BST<T>::Threaded_BST( const Threaded_BST& tree )
{
	*this = tree;
}

template<typename T>
Threaded_BST<T>::~Threaded_BST()
{
	delete root;
	root = nullptr;
}

template<typename T>
Threaded_BST<T>& Threaded_BST<T>::operator=( const Threaded_BST & tree )
{
	if ( !empty() )
	{
		clear( root );
	}
	if ( !tree.empty() )
	{
		root = new Node { *tree.root };
	}

	return *this;
}

template<typename T>
const T& Threaded_BST<T>::min() const
{
	assert( !empty() );
	return Min_Node( root )->object;
}

template<typename T> typename
Threaded_BST<T>::Node* Threaded_BST<T>::Min_Node( Node * p_node ) const
{
	if ( p_node == nullptr ) return nullptr;
	if ( p_node->left == nullptr ) return p_node;
	return Min_Node( p_node->left );
}

template<typename T>
const T& Threaded_BST<T>::max() const
{
	assert( !empty() );
	return Max_Node( root )->object;
}

template<typename T> typename
Threaded_BST<T>::Node* Threaded_BST<T>::Max_Node( Node * p_node ) const
{
	if ( p_node == nullptr ) return nullptr;
	if ( p_node->right == nullptr ) return p_node;
	return Max_Node( p_node->right );
}

template<typename T>
bool Threaded_BST<T>::contains( const T & obj ) const
{
	if ( empty() ) return false;
	return root->Contains( obj );
}

template<typename T>
bool Threaded_BST<T>::empty() const
{
	return root == nullptr;
}

template<typename T>
void Threaded_BST<T>::insert( const T & obj )
{
	if ( empty() )
	{
		root = new Node { obj };
	}
	else return root->Add( obj );
}

template<typename T>
void Threaded_BST<T>::remove( const T & obj )
{
	assert( !empty() );


}

template<typename T>
void Threaded_BST<T>::clear( Node*& p_node )
{
	if ( p_node == nullptr ) return;
	else
	{
		delete p_node;
		p_node = nullptr;
	}
}
