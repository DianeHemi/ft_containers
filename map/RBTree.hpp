#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <iostream>

namespace ft
{
    template <class T>
    struct RBTree
	{
		int			color;
		T			data;
		RBTree*   	parent;
		RBTree*   	left;
		RBTree*   	right;
		//bool		end;
	};

    template <class T>
    RBTree<T>* minimum( RBTree<T>* root ) //Node at the utter left
	{
		while (root->left)
			root = root->left;
		return root;
	}

    template <class T>
	RBTree<T>* maximum( RBTree<T>* root ) //Node at the utter right
	{
		while (root->right) //&& root->right->end == false
			root = root->right;
		return root;
	}

    template <class T>
	RBTree<T>* successor( RBTree<T>* node )
	{
		if (node->right)
			return minimum(node->right);
		
		RBTree<T>* parent = node->parent;
		while (parent && node == parent->right)
		{
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}

    template <class T>
	RBTree<T>* predecessor( RBTree<T>* node )
	{
		if (node->left)
			return maximum(node->left);
		
		RBTree<T>* parent = node->parent;
		while (parent && node == parent->left)
		{
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}

}

# endif