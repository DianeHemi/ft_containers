#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <iostream>
# include "pair.hpp"

namespace ft
{
	enum eColor
	{
		BLACK, RED, NIL
	};

	template <class T>
	struct rbt_node
	{
		eColor		color;
		T			data;
		rbt_node*	parent;
		rbt_node*	left;
		rbt_node*	right;


		rbt_node() : color(RED), data(T()), parent(NULL), left(NULL), right(NULL) { };
		rbt_node(T data) : color(RED), data(data), parent(NULL), left(NULL), right(NULL) { };
		//virtual ~rbt_node() {};
	};



	template <class Key, class Mapped, class Compare = ft::less<Key>, 
			class Alloc = std::allocator<Key> >
	class RBTree
	{
/****************************************************************
						 Definitions
*****************************************************************/
		public:
			typedef Key					key_type;
			typedef Mapped				mapped_type;
			typedef std::size_t			size_type;
			typedef std::ptrdiff_t		difference_type;
			typedef Compare				key_compare;
			typedef Alloc				allocator_type;

			typedef typename ft::pair<const Key, Mapped> 	value_type;

			typedef rbt_node<value_type>	node_t;
			typedef rbt_node<value_type>*	node_ptr;

			typedef typename Alloc::template rebind<node_t>::other	new_alloc;

			


/****************************************************************
						 Private members
*****************************************************************/
		private:
			node_ptr		_root;
			node_ptr		_nil;
			Compare			_cmp;

			allocator_type	_alloc;
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
				_root->color = NIL;
				_nil = _root;
			};

			//Copy constructor
			RBTree( const RBTree& src )
			{ *this = src; };

			//Overload operator=
			RBTree & operator=( const RBTree& rhs )
			{
				if (this != &rhs)
				{
					_root = rhs._root;
					_nil = rhs._nil;
					_cmp = rhs._cmp;
					_alloc = rhs._alloc;
					_alloc_rbt = rhs._alloc_rbt;
					_size = rhs._size;
				}
				return *this;
			}


			//Destructor
			~RBTree()
			{
				deleteNode(_nil);
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
				node->left = _nil;
				node->right = _nil;
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
			node_ptr minimum( node_ptr node ) const //Node at the utter left
			{
				if (node == _nil)
					return _root;

				while (node->left && node->left != _nil)
					node = node->left;
				return node;
			}

			node_ptr maximum( node_ptr node ) const //Node at the utter right
			{
				if (node == _nil)
					return _root;

				while (node->right && node->right != _nil)
					node = node->right;
				return node;
			}

			node_ptr successor( node_ptr node ) const
			{
				if (node->right && node->right != _nil)
					return minimum(node->right);

				node_ptr parent = node->parent;
				while (parent && parent != _nil && node == parent->right)
				{
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}

			node_ptr predecessor( node_ptr node ) const
			{
				if (node->left && node->left != _nil)
					return maximum(node->left);
				
				node_ptr parent = node->parent;
				while (parent && parent != _nil && node == parent->left)
				{
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}

			node_ptr searchTree( const key_type& key, node_ptr node ) const
			{
				node_ptr tmp = node;

				while (tmp != NULL && tmp != _nil)
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


/****************************************************************
						 	Rotation
*****************************************************************/		
			void leftRotate( node_ptr x )
			{
				node_ptr y = x->right;
				
				x->right = y->left;
				if (y->left && y->left != _nil)
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
				node_ptr y = x->left;

				x->left = y->right;
				if (y->right && y->right != _nil)
					y->right->parent = x;
				y->parent = x->parent;
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
					_root->color = BLACK;
					_nil->parent = _root;
					_size++;
					return _root;
				}

				node_ptr y = NULL;
				node_ptr x = _root;
				node_ptr node = newNode(key);
				while (x && x != _nil)
				{
					y = x;
					if (_cmp(node->data.first, x->data.first))
						x = x->left;
					else if (_cmp(x->data.first, node->data.first))
						x = x->right;
					else
					{
						deleteNode(node);
						_size++;
						return x;
					}
				}
				
				node->parent = y;
				_size++;
				if (_cmp(node->data.first, y->data.first))
					y->left = node;	
				else
					y->right = node;
				if (node->parent == NULL)
				{
					node->color = BLACK;
					return node;
				}
				if (node->parent->parent == NULL)
					return node;

				insertFix(node);

				_nil->parent = _root;
				_nil->color = NIL;

				return node;
			}

			void insertFix( node_ptr z )
			{
				node_ptr x = NULL;
				while (z->parent->color == RED)
				{
					if (z->parent == z->parent->parent->right)
						x = z->parent->parent->left;
					else
						x = z->parent->parent->right;
					if (x && x->color == RED)
					{
						x->color = BLACK;
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else if (z->parent == z->parent->parent->right)
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
					else if (z->parent == z->parent->parent->left)
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
					if (z == _root)
						break;
				}
				_root->color = BLACK;
			}



/****************************************************************
						 	Deletion
*****************************************************************/
			void _rbTransplant(node_ptr x, node_ptr y)
			{
				if (x->parent == NULL)
					_root = y;

				if (x->parent)
				{
					if (x == x->parent->left)
					{
						x->parent->left = y;
					}
					else
					{
						if (y == NULL)
							x->parent->right = _nil;
						else
							x->parent->right = y;
					}	
				}
				y->parent = x->parent;
			}


			void _erase( node_ptr z )
			{
				node_ptr x;
				node_ptr y = z;
				eColor y_original_color = y->color;

				if (!z->left || z->left == _nil) //1 child
				{
					x = z->right;
					_rbTransplant(z, z->right);
				}
				else if (!z->right || z->right == _nil) //1 child
				{	
					x = z->left;
					_rbTransplant(z, z->left);
				}
				else //2 childs
				{
					y = minimum(z->right);
					x = y->right;
					y_original_color = y->color;
					
					if (y->parent == z)
						x->parent = y;
					else
					{
						_rbTransplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					_rbTransplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				deleteNode(z);
				if (y_original_color == BLACK)
					_eraseFix(x);
				_nil->parent = _root;
				_nil->color = NIL;
			}

			void _eraseFix(node_ptr x)
			{
				node_ptr w;

				while (x != _root && x->color == BLACK)
				{
					if (x->parent && x == x->parent->left)
					{
						w = x->parent->right;
						if (w && w->color == RED)
						{
							w->color = BLACK;
							x->parent->color = RED;
							leftRotate(x->parent);
							w = x->parent->right;
						}
						if (w && w->left && w->right && w->left->color == BLACK && w->right->color == BLACK)
						{
							w->color = RED;
							x = x->parent;
						}
						else
						{
							if (w && w->right && w->right->color == BLACK)
							{
								if (w->left)
									w->left->color = BLACK;
								w->color = RED;
								rightRotate(w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							if (w->right)
								w->right->color = BLACK;
							leftRotate(x->parent);
							x = _root;
							if (x->left == NULL)
								x->left = _nil;
							if (x->right == NULL)
								x->right = _nil;
						}
					}
					else
					{
						w = x->parent->left;
						if (w && w->color == RED)
						{
							w->color = BLACK;
							x->parent->color = RED;
							rightRotate(x->parent);
							w = x->parent->left;
						}
						if (w && w->right && w->left && w->right->color == BLACK && w->left->color == BLACK)
						{
							w->color = RED;
							x = x->parent;
						}
						else
						{
							if (w && w->left && w->left->color == BLACK)
							{
								w->right->color = BLACK;
								w->color = RED;
								leftRotate(w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							if (w ->left)
								w->left->color = BLACK;
							rightRotate(x->parent);
							x = _root;
							if (x->left == NULL)
								x->left = _nil;
							if (x->right == NULL)
								x->right = _nil;
						}
					}
				}
				x->color = BLACK;
			}
	



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
				if (root != _nil)
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
					std::string sColor;
					if (root->color == RED)
						sColor = "RED";
					else if (root->color == BLACK)
						sColor = "BLACK";
					else
						sColor = "NIL";
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
					if (tmp->data.first >= key) //value_compare()
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

			void swap( RBTree& other )
			{
				RBTree tmp = *this;
				*this = other;
				other = tmp;
			}


	};
}

# endif