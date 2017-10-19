#pragma once

#include <assert.h>
#include <algorithm>
#include <iostream>

/////////////////////////////////////////
////								 ////
////			 AVL Tree			 ////
////								 ////
////  T must have operator< defined	 ////
/////////////////////////////////////////
// Make Node* into Node*&
template<typename T>
class AVLTree
{
	struct Node;
public:
	AVLTree();
	AVLTree( const AVLTree& tree );
	~AVLTree();
	AVLTree&		operator=( const AVLTree& tree );

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
	struct Node
	{
		T		object;
		Node*	left;
		Node*	right;
		int		height;


		Node( const T& obj, Node* lnode = nullptr, Node* rnode = nullptr, int h = 0 )
			:
			object	{ obj },
			left	{ lnode },
			right	{ rnode },
			height	{ h }
		{}
		Node( const Node& ref )
			:
			object { ref.object },
			height { ref.height }
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
	static constexpr int HEIGHT_IMBALANCE_THRESHOLD = 1;

	/* Encapsulating recursion */
	void	Insert( const T& obj, Node*& p_node );
	void	Remove( const T& obj, Node*& p_node );
	Node*	Min_Node( Node* p_node ) const;
	Node*	Max_Node( Node* p_node ) const;
	bool	Contains( const T& obj, Node* p_node ) const;
	/* Balancing Tree */
	void	Balance( Node*& p_node );
	void	Rotation_Left( Node*& p_node );
	void	Rotation_Right( Node*& p_node );
	void	Double_Left( Node*& p_node );
	void	Double_Right( Node*& p_node );
	int		Height( Node* p_node )
	{
		return ( p_node == nullptr ) ? -1 : p_node->height;
	}

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
AVLTree<T>::AVLTree()
	:
	root { nullptr }
{}

template<typename T>
AVLTree<T>::AVLTree( const AVLTree& tree )
{
	*this = tree;
}

template<typename T>
AVLTree<T>::~AVLTree()
{
	delete root;
	root = nullptr;
}

template<typename T>
AVLTree<T>& AVLTree<T>::operator=( const AVLTree& tree )
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
const T& AVLTree<T>::min() const
{
	assert( !empty() );
	return Min_Node( root )->object;
}

/* Encapsulating recursion */
template<typename T> typename
AVLTree<T>::Node* AVLTree<T>::Min_Node( Node* p_node ) const
{
	assert( p_node == nullptr );
	if ( p_node->left == nullptr ) return &( p_node->object );
	return Min_Node( p_node->left );
}

template<typename T>
const T& AVLTree<T>::max() const
{
	assert( !empty() );
	return Max_Node( root )->object;
}

/* Encapsulating recursion */
template<typename T> typename
AVLTree<T>::Node* AVLTree<T>::Max_Node( Node* p_node ) const
{
	assert( p_node == nullptr );
	if ( p_node->right == nullptr ) return &( p_node->object );
	return Max_Node( p_node->right );
}

template<typename T>
bool AVLTree<T>::contains( const T & obj ) const
{
	return Contains( obj, root );
}

/* Encapsulating recursion */
template<typename T>
bool AVLTree<T>::Contains( const T& obj, Node* p_node ) const
{
	if ( p_node->left != nullptr && obj < p_node->object )
	{
		return Contains( obj, p_node->left );
	}
	else if ( p_node->right != nullptr )
	{
		if ( obj > p_node->object )
		{
			return Contains( obj, p_node->right );
		}
		return true; // NOTE : float
	}
	return false;
}

/* Balancing Tree */
template<typename T>
void AVLTree<T>::Balance( Node *& p_node )
{
	assert( p_node != nullptr );

	if ( Height( p_node->left ) - Height( p_node->right ) > HEIGHT_IMBALANCE_THRESHOLD )
	{
		if ( Height( p_node->left->left ) >= Height( p_node->left->right ) )
		{
			Rotation_Left( p_node );
		}
		else Double_Left( p_node );
	}
	else if ( Height( p_node->right ) - Height( p_node->left ) > HEIGHT_IMBALANCE_THRESHOLD )
	{
		if ( Height( p_node->right->right ) >= Height( p_node->right->left ) )
		{
			Rotation_Right( p_node );
		}
		else Double_Right( p_node );
	}

	p_node->height = std::max( Height( p_node->left ), Height( p_node->right ) ) + 1;
}

/* Balancing Tree */
template<typename T>
void AVLTree<T>::Rotation_Left( Node *& p_node )
{
	Node* temp = p_node->left;

	p_node->left = temp->right;
	temp->right = p_node;

	p_node->height = std::max( Height( p_node->left ), Height( p_node->right ) ) + 1;
	temp->height = std::max( Height( temp->left ), p_node->height ) + 1;

	p_node = temp;
}

/* Balancing Tree */
template<typename T>
void AVLTree<T>::Rotation_Right( Node *& p_node )
{
	Node* temp = p_node->right;

	p_node->right = temp->left;
	temp->left = p_node;

	p_node->height = std::max( Height( p_node->right ), Height( p_node->left ) ) + 1;
	temp->height = std::max( Height( temp->right ), p_node->height ) + 1;

	p_node = temp;
}

/* Balancing Tree */
template<typename T>
void AVLTree<T>::Double_Left( Node *& p_node )
{
	Rotation_Right( p_node->left );
	Rotation_Left( p_node );
}

/* Balancing Tree */
template<typename T>
void AVLTree<T>::Double_Right( Node *& p_node )
{
	Rotation_Left( p_node->right );
	Rotation_Right( p_node );
}

template<typename T>
bool AVLTree<T>::empty() const
{
	return root == nullptr;
}

template<typename T>
void AVLTree<T>::insert( const T& obj )
{
	Insert( obj, root );
}

/* Encapsulating recursion */
template<typename T>
void AVLTree<T>::Insert( const T& obj, Node *& p_node )
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

	Balance( p_node );
}

template<typename T>
void AVLTree<T>::remove( const T& obj )
{
	Remove( obj, root );
}

/* Encapsulating recursion */
template<typename T>
void AVLTree<T>::Remove( const T& obj, Node *& p_node )
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

		delete temp;
	}

	Balance( p_node );
}

template<typename T>
void AVLTree<T>::clear( Node*& p_node )
{
	if ( p_node == nullptr ) return;
	else
	{
		delete p_node;
		p_node = nullptr;
	}
}