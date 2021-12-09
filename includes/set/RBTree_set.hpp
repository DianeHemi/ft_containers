#ifndef RBTREE_SET_HPP
# define RBTREE_SET_HPP

# include <iostream>
# include "../pair.hpp"

# define BLACK 0
# define RED 1
# define NIL 2

namespace ft
{
	template <class T>
	struct rbt_node
	{
		size_t		color;
		T			data;
		rbt_node*	parent;
		rbt_node*	left;
		rbt_node*	right;

		rbt_node() : color(RED), data(T()), parent(NULL), left(NULL), right(NULL) { };
		rbt_node(T data) : color(RED), data(data), parent(NULL), left(NULL), right(NULL) { };
	};


	template <class Key, class Compare = ft::less<Key>, 
			class Alloc = std::allocator<Key> >
	class RBTree
	{
		/****************************************************************
								 Definitions
		*****************************************************************/
		public:
			typedef Key					key_type;
			typedef Key					value_type;
			typedef std::size_t			size_type;
			typedef std::ptrdiff_t		difference_type;
			typedef Compare				key_compare;
			typedef Alloc				allocator_type;

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
								 Constructors
		*****************************************************************/
		public:
			//Constructor
			RBTree( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() ) 
				: _cmp(comp), _alloc(alloc), _size(0)
			{
				_root = newNode(value_type());
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
			~RBTree() { };


		/****************************************************************
									Getters
		*****************************************************************/
		node_ptr	getRoot() const { return _root; }

		node_ptr	getNil() const { return _nil; }

		size_type	getSize() const { return _size; }

		new_alloc	getRBtAlloc() const { return _alloc_rbt; }

		Compare		getCompare() const { return _cmp; }


		/****************************************************************
									Nodes
		*****************************************************************/
		node_ptr newNode( const value_type& key )
		{		
			node_ptr node = _alloc_rbt.allocate(1);
			_alloc_rbt.construct(node, key);
			node->parent = NULL;
			node->left = _nil;
			node->right = _nil;
			node->color = RED;
			return node;
		};

		void deleteNode( node_ptr node )
		{
			_size--;
			_alloc_rbt.destroy(node);
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
				if (key == tmp->data)
					return tmp;
				else if (key < tmp->data)
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
			if (node == NULL)
				return NULL;
			return node->parent->parent;
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
				if (_cmp(x->data, node->data))
					x = x->right;
				else if (_cmp(node->data, x->data))
					x = x->left;
				else
				{
					deleteNode(node);
					_size++;
					return x;
				}
			}
			node->parent = y;
			_size++;
			if (_cmp(node->data, y->data))
				y->left = node;	
			else
				y->right = node;
			if (getGrandParent(node) == NULL)	//New node is red -> no need to fix insert
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
				{
					x = z->parent->parent->left;
					if (x && x->color == RED)
					{
						x->color = BLACK;
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						z = getGrandParent(z);
					}
					else 
					{
						if (z == z->parent->left)
						{
							z = getParent(z);
							rightRotate(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						leftRotate(z->parent->parent);
					}
				}
				else
				{
					x = z->parent->parent->right;
					if (x && x->color == RED)
					{
						x->color = BLACK;
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						z = getGrandParent(z);
					}
					else
					{
						if (z == z->parent->right)
						{
							z = getParent(z);
							leftRotate(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						rightRotate(z->parent->parent);
					}
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
			if (getParent(x) == NULL)
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
			y->parent = getParent(x);
		}


		void _erase( node_ptr z )
		{
			node_ptr x;
			node_ptr y = z;
			size_t y_original_color = y->color;

			if (!z->left || z->left == _nil) //1 child
			{
				x = z->right;	//We copy the child
				_rbTransplant(z, z->right);	//We move the child to were z was
			}
			else if (!z->right || z->right == _nil) //1 child
			{	
				x = z->left;
				_rbTransplant(z, z->left);	//Remplacer z->left/z->right par x ?
			}
			else //2 childs
			{
				y = minimum(z->right);	//Search for smaller element in right tree branch
				x = y->right; 
				y_original_color = y->color;
				
				if (y->parent == z)
					x->parent = y;
				else
				{
					_rbTransplant(y, y->right);	//Copy z right side to y
					y->right = z->right;
					y->right->parent = y;
				}
				_rbTransplant(z, y);	//Copy z left side to y
				y->left = z->left;		// = We move y to were z was and keep the children
				y->left->parent = y;
				y->color = z->color;
			}
			deleteNode(z);	//No child -> We end up here and juste delete the node
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
						x = getParent(x);
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
						x = getParent(x);
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
					}
				}
			}
			x->color = BLACK;
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
				if (tmp->data >= key)
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
				if (tmp->data > key)
					return tmp;
				tmp = successor(tmp);
			}
			return _nil;
		}

		void swap( RBTree& other )
		{
			size_type	sz = this->_size;
			node_ptr	rt = this->_root;
			node_ptr	nil = this->_nil;
			Compare		cmp = this->_cmp;
			allocator_type	alloc = this->_alloc;
			new_alloc		alloc_rbt = this->_alloc_rbt;

			this->_size = other._size;
			this->_root = other._root;
			this->_nil = other._nil;
			this->_cmp = other._cmp;
			this->_alloc = other._alloc;
			this->_alloc_rbt = other._alloc_rbt;

			other._size = sz;
			other._root = rt;
			other._nil = nil;
			other._cmp = cmp;
			other._alloc = alloc;
			other._alloc_rbt = alloc_rbt;
		}


		/****************************************************************
								Cleaning
		*****************************************************************/
		void clearTree()
		{
			if (_size > 0)
			{
				node_ptr node = maximum(_root);
				node_ptr parent;
				while (node && node != _root && node != _nil)
				{
					if (node->right && node->right != _nil)
						node = maximum(node);
					if (node->left && node->left != _nil)
						node = minimum(node);
					parent = node->parent;
					if (parent->left == node)
						parent->left = _nil;
					else
						parent->right = _nil;
					deleteNode(node);
					if (parent != _root && parent->left && parent->left != _nil)
						node = minimum(parent->left);
					else if (parent->right && parent->right != _nil)
						node = maximum(parent->right);
					else
						node = parent;
				}
				node = minimum(_root);
				while (node && node != _root && node != _nil)
				{
					if (node->right && node->right != _nil)
						node = maximum(node);
					if (node->left && node->left != _nil)
						node = minimum(node);
					parent = node->parent;
					if (parent->left == node)
						parent->left = _nil;
					else
						parent->right = _nil;
					deleteNode(node);
					if (parent->left && parent->left != _nil)
						node = minimum(parent->left);
					else if (parent != _root && parent->right && parent->right != _nil)
						node = maximum(parent->right);
					else
						node = parent;
				}
				if (_root)
					deleteNode(_root);
			}
			deleteNode(_nil);
		}
	};

} //ft

# endif