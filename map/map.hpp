#ifndef MAP_HPP
# define MAP_HPP

# define BLACK 0
# define RED 1

# include "pair.hpp"
# include "iterator_map.hpp"
# include "../lexicographical_compare.hpp"
# include <memory>
# include <iostream>


//# include "tree_test_cleaned.hpp"

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, 
			class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
		/****
			Member type
		****/
			typedef Key                 key_type;
			typedef T                   mapped_type;
			typedef size_t				size_type;
			typedef std::ptrdiff_t		difference_type;
			typedef Compare             key_compare;
			typedef Alloc				allocator_type;

			typedef typename ft::pair<const Key, T> value_type;
			typedef ft::RBTree<value_type>	rbt;

			typedef value_type&         					reference;
			typedef const value_type&   					const_reference;
			typedef typename allocator_type::pointer 		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			

			typedef typename ft::iterator_map<value_type>			    	iterator;        //legacy bidirectionnal iterator to value_type
			//typedef typename ft::const_iterator_map<value_type>	    	const_iterator;  //legacy bidirectionnal iterator to const value_type
			typedef typename ft::reverse_iterator<iterator>		    		reverse_iterator;
			//typedef typename ft::const_reverse_iterator<const_iterator>	const_reverse_iterator
			typedef typename Alloc::template rebind<rbt>::other    new_alloc;

		/****
			Constructors
		****/
		//Default constructor
		explicit map( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
			: _alloc(alloc), _size(0), _cmp(comp), _rbt(0)
		{
			_rbt = newNode(ft::make_pair(key_type(), mapped_type()));
			_end = _rbt;
			//_end->end = true;
		};

		//Range constructor
		template <class InputIterator>
		map( InputIterator first, InputIterator last, 
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type() )
		: _alloc(alloc), _size(0), _cmp(comp), _rbt(0)
		{
			_rbt = newNode(ft::make_pair(key_type(), mapped_type()));
			_end = _rbt;
			//_end->end = true;
			insert(first, last);
		};

		//Copy constructor
		//map( const map& src ) { *this = src; };

		//Destructor
		/*~map()
		{
			clear();
		}*/

		//Overload operator =
		/*map& operator=( const & map rhs )
		{
			if (this != &rhs)
			{
				clear();
				if (rhs._size > 0)
					insert(rhs.begin(), rhs.end());
			}
			return *this;
		};*/

		allocator_type get_allocator() const { return _alloc; };


		/****
			Iterators
		****/
		iterator        begin() { return iterator(minimum(_rbt)); };
		//const_iterator  begin() { };
		iterator        end() { return iterator(_end); };
		//const_iterator  end() { };

		reverse_iterator        rbegin() { return reverse_iterator(maximum(_rbt)); };
		//const_reverse_iterator  rbegin() { };
		reverse_iterator        rend() { return reverse_iterator(minimum(_rbt)); };
		//const_reverse_iterator  rend() { };

		/****
			Capacity
		****/
		bool        empty() const { return _size == 0; };
		size_type   size() const { return _size; };
		size_type   max_size() const { return _alloc.max_size(); };
		
		/****
			Element access
		****/
		//mapped_type& operator[]( const key_type& k ) { };

		/****
			Modifiers
		****/
		//void 	clear() { };
		//void 	swap( map& x ) { };
		//void		erase( iterator position ) { };
		//size_type	erase( const key_type& k ) { };
		//void		erase( iterator first, iterator last) { };
		ft::pair<iterator, bool>	insert( const value_type& val ) 
		{
			ft::pair<iterator, bool> ret;
			size_type tmp_size = _size;
			rbt* node = _insertSingle(val);

			if (_size != tmp_size)
				ret._second = false;
			else
				ret._second = true;
			ret._first = iterator(node);
			return ret;
		};
		iterator	insert( iterator position, const value_type& val ) 
		{
			iterator it = position;
			rbt* node = _insertSingle(val);

			return iterator(node);
		};
		template <class InputIterator>
		void	insert( InputIterator first, InputIterator last ) 
		{
			for ( ; first != last; first++)
				_insertSingle(*first);
		};

		/****
			Observers
		****/
		key_compare 	key_comp() const { return _cmp; };

		class value_compare
		{
			friend class map;
			public:
				typedef	bool		result_type;
				typedef	value_type	first_argument_type;
				typedef	value_type	second_argument_type;

				//constructor
				value_compare( Compare c ) : comp(c) { };
				bool operator()( const value_type& left, const value_type& right ) const 
				{ return (comp(left.first, right.first)); };

			protected:
				Compare comp;
		};
		value_compare	value_comp() const { return (value_compare(_cmp)); };

		/****
			Operations
		****/
		//iterator		find( const key_type& k ) { };
		//const_iterator	find( const key_type& k ) const { };
		//size_type		count( const key_type& k ) const { };
		//iterator		lower_bound( const key_type& k ) { };
		//const_iterator	lower_bound( const key_type& k ) const { };
		//iterator		upper_bound( const key_type& k ) { };
		//const_iterator	upper_bound( const key_type& k ) const { };
		//ft::pair<iterator, iterator>				equal_range( const key_type& k ) { };
		//ft::pair<const_iterator, const_iterator>	equal_range( const key_type& k ) const { };
		


void printTree()
{
	if (_rbt)
		printHelper(_rbt, "", true);
}

/****************************************************************
						 Private members
*****************************************************************/
		private:
			allocator_type  	_alloc;
			size_type       	_size;
			Compare				_cmp;
			new_alloc			_alloc_rbt;
			rbt*				_rbt;
			rbt*				_end;

			



/****************************************************************
						Private functions
*****************************************************************/
		private:
			rbt* newNode( const value_type& key )
			{
				rbt* node = _alloc_rbt.allocate(1);
				_alloc.construct(&node->data, key);
				node->parent = NULL;
				node->left = NULL;
				node->right = NULL;
				node->color = RED;
				return node;
			}


			rbt* _insertSingle( const value_type& key )
			{
				if(!_rbt || _rbt == _end)
				{
					_rbt = newNode(key);
					_rbt->right = _end;
					_rbt->color = BLACK;
					_end->parent = _rbt;
					_size++;
					return _rbt;
				}

				rbt* linker = _rbt;
				rbt *node = newNode(key);
				while (linker != NULL)
				{
					if (_cmp(key._first, linker->data._first))
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
					else if (linker->data._first != key._first)
					{
						if (linker->right == _end || linker->right == NULL)
						{
							if (linker->right == _end)
							{
								node->right = _end;
								_end->parent = node;
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
			
			void leftRotate( rbt* x )
			{
				if (x->right == NULL || x->right == _end)
					return ;

				rbt* y = x->right;
				x->right = y->left;
				if (y->left != NULL)
					y->left->parent = x;
				y->parent = x->parent;

				if (x->parent == NULL)	//Reassign root of the rbt
					_rbt = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void rightRotate( rbt* x )
			{
				if (x->left == NULL || x->left == _end)
					return ;

				rbt* y = x->left;

				x->left = y->right;
				y->parent = x->parent;
				if (y->right != NULL)
					y->right->parent = x;

				if (x->parent == NULL)	//Reassign root of the rbt
					_rbt = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			void insertFix( rbt* z )
			{
				while (z != NULL && z != _end && z->parent != NULL && z->parent->color == RED)
				{
					if (z->parent == z->parent->parent->left) //node->parent is left child
					{
						rbt* y = z->parent->parent->right; //uncle of node
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
						rbt* y = z->parent->parent->left;
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
				_rbt->color = BLACK;
			}

		




void printHelper(rbt* root, std::string indent, bool last) 
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
		std::cout << root->data._first << " - " << root->data._second << "(" << sColor << ")" << std::endl;
		printHelper(root->left, indent, false);
		printHelper(root->right, indent, true);
	}
}
			

	};





	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return rhs < lhs;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}

	/*template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs )
	{

	}*/

}

#endif