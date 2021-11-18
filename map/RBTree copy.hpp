#ifndef RBTREE_HPP
# define RBTREE_HPP

# define	BLACK	0
# define	RED		1

namespace ft
{
    struct Node_base
	{
		int			color;
		Node_base*   	parent;
		Node_base*   	left;
		Node_base*   	right;

		Node_base* minimum( Node_base* root ) //Node at the utter left
		{
			while (root->left)
				root = root->left;
			return root;
		}

		Node_base* maximum( Node_base* root ) //Node at the utter right
		{
			while (root->right)
				root = root->right;
			return root;
		}

		Node_base* successor( Node_base* node )	//Next node
		{
			if (node->right)
				return minimum(node->right);
			
			Node_base* parent = node->parent;
			while(parent && node == parent->right)
			{
				node = parent;
				parent = parent->parent;
			}
			return parent;
		}

		Node_base* predecessor( Node_base* node )	//Previous node
		{
			if (node->left)
				return minimum(node->left);
			
			Node_base* parent = node->parent;
			while(parent && node == parent->left)
			{
				node = parent;
				parent = parent->parent;
			}
			return parent;
		}

		/*RBTree<T>* searchTree(T key, RBTree<T>* root) 
		{
			if(!root) 
				return NULL;

			while (root) 
			{
				if (key == root->data)
					return root;
				else if (key < root->data)
					root = root->left;
				else 
					root = root->right;
			}
			return NULL;
		}*/
	};

	template <class T>
	struct Node : public Node_base
	{
		T	data;

		Node( const & key ) : data(key) { };
	};

	template <class T>
	struct RBTree_iterator : public ft::iterator< ft::bidirectional_iterator_tag, T >
	{
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef	T&	reference;
			typedef	T*	pointer;
			typedef RBTree_iterator<T>	iterator;
			typedef node<T>*			type;

			RBTree_iterator() { };
			RBTree_iterator( node_base* src ) : _node(src) { };


			node_base*					_node;
	};
	


}

# endif