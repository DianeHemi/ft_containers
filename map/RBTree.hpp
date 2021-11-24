#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <iostream>
# include "pair.hpp"

namespace ft
{
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
			class Alloc = std::allocator<rbt_node<ft::pair<const Key, T> > > >
	class RBTree
	{
/****************************************************************
						 Definitions
*****************************************************************/
		public:
			typedef Key                 key_type;
			typedef T                   mapped_type;
			typedef std::size_t			size_type;
			typedef std::ptrdiff_t		difference_type;
			typedef Compare             key_compare;
			typedef Alloc				allocator_type;

			typedef typename ft::pair<const Key, T> 	value_type;

			typedef rbt_node<value_type>	node;
			typedef rbt_node<value_type>*	node_ptr;

			typedef typename Alloc::template rebind<node>::other		new_alloc;


/****************************************************************
						 Private members
*****************************************************************/
		private:
			node_ptr		_root;
			node_ptr		_nil;
			Compare			_cmp;

			allocator_type  _alloc;
			new_alloc		_alloc_rbt;

			size_type		_size;


/****************************************************************
						 Construction
*****************************************************************/
		public:
			//Constructor
			RBTree( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() ) 
				: _cmp(comp), _alloc(alloc), _size(0)
			{
				_root = newNode(ft::make_pair(key_type(), mapped_type()));
				//_nil
			};


			//Destructor
			~RBTree()
			{
				//clear();
			};



/****************************************************************
						 	Getters
*****************************************************************/
			node_ptr getRoot() const
			{
				return _root;
			}

			node_ptr getNil() const
			{
				return _nil;
			}

			size_type getSize() const
			{
				return _size;
			}

			new_alloc getRBtAlloc() const
			{
				return _alloc_rbt;
			}

			Compare	getCompare() const
			{
				return _cmp;
			}

/****************************************************************
						 Public functions
*****************************************************************/
			node_ptr newNode( const value_type& key )
			{
				node_ptr node = _alloc_rbt.allocate(1);
				_alloc.construct(&node->data, key);
				node->parent = NULL;
				node->left = NULL;
				node->right = NULL;
				node->color = RED;
				return node;
			};

			void deleteNode( node_ptr node )
			{
				_size--;
				_alloc.destroy(&node->data);
				_alloc_rbt.deallocate(node, 1);
			}

			node_ptr minimum( node_ptr root ) const //Node at the utter left
			{
				while (root->left)
					root = root->left;
				return root;
			}

			node_ptr maximum( node_ptr root ) const //Node at the utter right
			{
				while (root->right && root != _nil)
					root = root->right;
				return root;
			}

			node_ptr successor( node_ptr node )
			{
				if (node->right)
					return minimum(node->right);
				
				node_ptr parent = node->parent;
				while (parent && node == parent->right)
				{
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}

			node_ptr predecessor( node_ptr node )
			{
				if (node->left)
					return maximum(node->left);
				
				node_ptr parent = node->parent;
				while (parent && node == parent->left)
				{
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}

			node_ptr searchTree( const key_type& key, node_ptr node )
			{
				node_ptr tmp = node;

				while (tmp != NULL)
				{
					if (key == tmp->data.first)
						return tmp;
					else if (key < tmp->data.first)
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				return NULL;
			}

/****************************************************************
						 	Helpers
*****************************************************************/
			node_ptr getParent( node_ptr node )
			{
				if (node == NULL)
					return NULL;
				return node->parent;
			}

			node_ptr getGrandParent( node_ptr node )
			{
				return getParent(getParent(node));
			}

			node_ptr getSibling( node_ptr node )
			{
				node_ptr parent = getParent(node);

				if (parent != NULL)
				{
					if (node == parent->left)
						return parent->right;
					else
						return parent->left;
				}
				return NULL;
			}

			node_ptr getUncle( node_ptr node )
			{
				node_ptr parent = getParent(node);

				if (parent != NULL)
					return getSibling(parent);
				return NULL;
			}

/****************************************************************
						 	Rotation
*****************************************************************/		




/****************************************************************
						 	Insertion
*****************************************************************/


/****************************************************************
						 	Deletion
*****************************************************************/



	};
}

# endif