#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <iostream>

namespace ft
{
    /*template <class T>
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
	}*/


	enum color
	{
		BLACK, RED
	};

	template <class T>
	struct rbt_node
	{
		color				color;
		T					data;
		struct rbt_node*	parent;
		struct rbt_node*	left;
		struct rbt_node*	right;

		rbt_node(T data) : color(RED), data(data), parent(NULL), left(NULL), right(NULL) { };
	};

	template <class Key, class T, class Compare = ft::less<Key>, 
			class Alloc = std::allocator<rbt_node<T> > >
	class RBTree
	{
		public:
			typedef Key                 key_type;
			typedef T                   mapped_type;
			typedef std::size_t			size_type;
			typedef std::ptrdiff_t		difference_type;
			typedef Compare             key_compare;
			typedef Alloc				allocator_type;

			typedef rbt_node<mapped_type>	node;
			typedef rbt_node<mapped_type>*	node_ptr;

			typedef typename Alloc::template rebind<rbt>::other    new_alloc;

		private:
			node_ptr		_root;
			node_ptr		_nil;
			difference_type	_cmp;

			allocator_type  _alloc;
			new_alloc		_alloc_rbt;

			size_type		_size;


		public:
			//Constructor
			

			//Destructor

			//Functions
			
	};

}

# endif