#pragma once

#include <assert.h>

/////////////////////////////////////////
////								 ////
////       Binary Serach Tree		 ////
////								 ////
////  T must have operator< defined	 ////
/////////////////////////////////////////
template<typename T>  
class BSTree
{
	class Node;
public:
				BSTree();
				BSTree( const BSTree& tree );
				~BSTree();
	BSTree&		operator=( const BSTree& tree );

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
		T		object;
		Node*	left;
		Node*	right;

		Node( const T& obj, Node* lnode = nullptr, Node* rnode = nullptr)
			:
			object	{obj},
			left	{lnode},
			right	{rnode}
		{}
		Node( const Node& ref )
			:
			object { ref.object }
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

		Node& operator=( const Node& ) = delete;

		bool Contains( const T& obj ) const
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
	};
	
	Node* root;

	/* Encapsulating recursion */
	void	Insert( const T& obj, Node*& p_node );
	void	Remove( const T& obj, Node*& p_node );
	Node*	Min_Node( Node* p_node ) const;
	Node*	Max_Node( Node* p_node ) const;

	void printTree( Node *t ) const
	{
		if ( t != nullptr )
		{
			printTree( t->left );
			std::cout << t->object << std::endl;
			printTree( t->right );
		}
	}
};

template<typename T>
BSTree<T>::BSTree()
	:
	root { nullptr }
{}

template<typename T>
BSTree<T>::BSTree( const BSTree& tree )
{
	*this = tree;
}

template<typename T>
BSTree<T>::~BSTree()
{
	delete root;
	root = nullptr;
}

template<typename T>
BSTree<T>& BSTree<T>::operator=( const BSTree & tree )
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
const T& BSTree<T>::min() const
{
	assert( !empty() );
	return Min_Node( root )->object;
}

template<typename T> typename
BSTree<T>::Node* BSTree<T>::Min_Node( Node * p_node ) const
{
	if ( p_node == nullptr ) return nullptr;
	if ( p_node->left == nullptr ) return p_node;
	return Min_Node( p_node->left );
}

template<typename T>
const T& BSTree<T>::max() const
{
	assert( !empty() );
	return Max_Node( root )->object;
}

template<typename T> typename
BSTree<T>::Node* BSTree<T>::Max_Node( Node * p_node ) const
{
	if ( p_node == nullptr ) return nullptr;
	if ( p_node->right == nullptr ) return p_node;
	return Max_Node( p_node->right );
}

template<typename T>
bool BSTree<T>::contains( const T & obj ) const
{
	if ( root == nullptr ) return false;
	return root->Contains( obj );
}

template<typename T>
bool BSTree<T>::empty() const
{
	return root == nullptr;
}

template<typename T>
void BSTree<T>::insert( const T & obj )
{
	Insert( obj, root );
}

template<typename T>
void BSTree<T>::Insert( const T & obj, Node *& p_node )
{
	if ( p_node == nullptr )
	{
		p_node = new Node { obj };
	}
	else if ( obj < p_node->object ) 
	{
		Insert( obj, p_node->left );
	}
	else if ( p_node->object < obj )
	{
		Insert( obj, p_node->right );
	}
	else /* Duplicate; Do nothing */;
}

template<typename T>
void BSTree<T>::remove( const T & obj )
{
	Remove( obj, root );
}

template<typename T>
void BSTree<T>::Remove( const T & obj, Node *& p_node )
{
	if ( p_node == nullptr ) return;
	else if ( obj < p_node->object ) 
	{
		Remove( obj, p_node->left );
	}
	else if ( p_node->object < obj ) 
	{
		Remove( obj, p_node->right );
	}
	else if ( p_node->left != nullptr && p_node->right != nullptr )
	{
		p_node->object = Min_Node( p_node->right )->object;
		Remove( p_node->object, p_node->right );
	}
	else
	{
		Node* temp = p_node;

		p_node = ( p_node->left != nullptr ) ? p_node->left : p_node->right;
		temp->left = nullptr;
		temp->right = nullptr;
		delete temp;
	}
}

template<typename T>
void BSTree<T>::clear( Node*& p_node )
{
	if ( p_node == nullptr ) return;
	else
	{
		delete p_node;
		p_node = nullptr;
	}
}

