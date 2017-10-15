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
	void		clear( struct Node* p_node = root );
	//print tree
private:
	struct Node
	{
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
	};
	
	Node* root;

	/* Encapsulating recursion */
	void	Insert( const T& obj, Node* p_node );
	void	Remove( const T& obj, Node* p_node );
	Node*	Min_Node( Node* p_node ) const;
	Node*	Max_Node( Node* p_node ) const;
	bool	Contains( const T& obj, Node* p_node ) const;
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
		clear();
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
	return Min_Node( root )->element;
}

template<typename T>
BSTree<T>::Node* BSTree<T>::Min_Node( Node * p_node ) const
{
	if ( p_node == nullptr ) return nullptr;
	if ( p_node->left == nullptr ) return p_node->object;
	return Min_Node( p_node->left );
}

template<typename T>
const T& BSTree<T>::max() const
{
	assert( !empty() );
	return Max_Node( root )->element;
}

template<typename T>
BSTree<T>::Node* BSTree<T>::Max_Node( Node * p_node ) const
{
	if ( p_node == nullptr ) return nullptr;
	if ( p_node->right == nullptr ) return p_node->object;
	return Max_Node( p_node->right );
}

template<typename T>
bool BSTree<T>::contains( const T & obj ) const
{
	return Contains( obj, root );
}

template<typename T>
bool BSTree<T>::Contains( const T& obj, Node* p_node ) const
{
	if ( p_node == nullptr ) return false;
	else if ( obj < p_node->object )
	{
		Contains( obj, p_node->left );
	}
	else if ( obj > p_node->object )
	{
		Contains( obj, p_node->right );
	}
	else return true;
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
void BSTree<T>::Insert( const T & obj, Node * p_node )
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
}

template<typename T>
void BSTree<T>::remove( const T & obj )
{
	Remove( obj, root );
}

template<typename T>
void BSTree<T>::Remove( const T & obj, Node * p_node )
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
		p_node->element = Min_Node( p_node->right )->element;
		Remove( p_node->element, p_node->right );
	}
	else
	{
		Node* temp = p_node;

		p_node = ( p_node->left != nullptr ) ? p_node->left : p_node->right;

		delete temp;
	}
}

template<typename T>
void BSTree<T>::clear( Node* p_node )
{
	if ( p_node == nullptr ) return;
	else
	{
		delete p_node;
		p_node = nullptr;
	}
}


