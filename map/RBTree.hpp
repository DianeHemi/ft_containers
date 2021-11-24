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
				_root->color = BLACK;
				_nil = _root;
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
						 	Nodes
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


/****************************************************************
						 	Position
*****************************************************************/
			node_ptr minimum( node_ptr root ) const //Node at the utter left
			{
				while (root->left)
					root = root->left;
				return root;
			}

			node_ptr maximum( node_ptr root ) const //Node at the utter right
			{
				while (root->right && root->right != _nil)
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
			void leftRotate( node_ptr x )
			{
				if (x->right == NULL || x->right == _nil)
					return ;

				node_ptr y = x->right;
				x->right = y->left;
				if (y->left != NULL)
					y->left->parent = x;
				y->parent = x->parent;

				if (x->parent == NULL)	//Reassign root of the rbt
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;

			}

			void rightRotate( node_ptr x )
			{
				if (x->left == NULL || x->left == _nil)
					return ;

				node_ptr y = x->left;

				x->left = y->right;
				y->parent = x->parent;
				if (y->right != NULL)
					y->right->parent = x;

				if (x->parent == NULL)	//Reassign root of the rbt
					_root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}



/****************************************************************
						 	Insertion
*****************************************************************/
			node_ptr _insertSingle( const value_type& key )
			{
				if(!_root || _root == _nil)
				{
					_root = newNode(key);
					_root->right = _nil;
					_root->color = BLACK;
					_nil->parent = _root;
					_size++;
					return _root;
				}
				node_ptr tmp = searchTree(key.first, _root);
				if (tmp != NULL)
					return tmp;

				node_ptr linker = _root;
				node_ptr node = newNode(key);
				while (linker != NULL)
				{
					if (_cmp(key.first, linker->data.first))
					{
						if (linker->left == NULL)
						{
							linker->left = node;
							node->color = RED;
							node->parent = linker;
							_size++;
							break;
						}
						else 
							linker = linker->left;
					} 
					else if (linker->data.first != key.first)
					{
						if (linker->right == _nil || linker->right == NULL)
						{
							if (linker->right == _nil)
							{
								node->right = _nil;
								_nil->parent = node;
							}
							linker->right = node;
							node->color = RED;
							node->parent = linker;
							_size++;
							break; 
						}
						else
							linker = linker->right;
					}
					else
						return node;
				}
				insertFix(node);
				return node;
			}
			
			void insertFix( node_ptr z )
			{
				while (z != NULL && z != _nil && z->parent != NULL && z->parent->color == RED)
				{
					if (z->parent == z->parent->parent->left) //node->parent is left child
					{
						node_ptr y = z->parent->parent->right; //uncle of node
						if (y && y->color == RED)
						{
							z->parent->color = BLACK;
							y->color = BLACK;
							z->parent->parent->color = RED;
							z = z->parent->parent;
						}
						else
						{
							if (z == z->parent->right)
							{
								z = z->parent;
								leftRotate(z);
							}
							z->parent->color = BLACK;
							z->parent->parent->color = RED;
							rightRotate(z->parent->parent);
						}
					}
					else
					{
						node_ptr y = z->parent->parent->left;
						if (y && y->color == RED)
						{
							z->parent->color = BLACK;
							y->color = BLACK;
							z->parent->parent->color = RED;
							z = z->parent->parent;
						}
						else
						{
							if (z == z->parent->left)
							{
								z = z->parent;
								rightRotate(z);
							}
							z->parent->color = BLACK;
							z->parent->parent->color = RED;
							leftRotate(z->parent->parent);
						}
					}
				}
				_root->color = BLACK;
			}



/****************************************************************
						 	Deletion
*****************************************************************/



/****************************************************************
						 	Affichage
*****************************************************************/
			void printTree()
			{
				if (_root)
					printHelper(_root, "", true);
			}

			void printHelper( node_ptr root, std::string indent, bool last ) 
			{
				if (root) 
				{
					std::cout << indent;
					if (last) 
					{
						std::cout << "R----";
						indent += "   ";
					} 
					else 
					{
						std::cout << "L----";
						indent += "|  ";
					}
					std::string sColor = root->color ? "RED" : "BLACK";
					std::cout << root->data.first << " - " << root->data.second << "(" << sColor << ")" << std::endl;
					printHelper(root->left, indent, false);
					printHelper(root->right, indent, true);
				}
			}

/****************************************************************
						Member functions
*****************************************************************/
			size_type		count( const key_type& key )
			{
				if (searchTree(key, _root) != NULL)
					return 1;
				return 0; 
			};

			node_ptr lower_bound( const key_type& key )
			{
				node_ptr 	tmp = minimum(_root);

				while (tmp != NULL && tmp != _nil)
				{
					if (tmp->data.first >= key)
						return tmp;
					tmp = successor(tmp);
				}
				return _nil;
			}

			node_ptr upper_bound( const key_type& key )
			{
				node_ptr 	tmp = minimum(_root);

				while (tmp != NULL && tmp != _nil)
				{
					if (tmp->data.first > key)
						return tmp;
					tmp = successor(tmp);
				}
				return _nil;
			}

		


	};
}

# endif