#ifndef MAP_HPP
# define MAP_HPP


# include "iterator_map.hpp"
# include "../lexicographical_compare.hpp"
# include <memory>
# include <iostream>


//https://metal-geography-067.notion.site/Binary-Search-Tree-30d6473427324e6fb1cc8c24d0f7938e
//https://gcc.gnu.org/onlinedocs/gcc-7.4.0/libstdc++/api/a15448_source.html

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
			typedef ft::RBTree<key_type, mapped_type, key_compare, allocator_type>	rbt;
			typedef ft::rbt_node<value_type>	rbt_node;
			typedef ft::rbt_node<value_type>*	rbt_node_ptr;


			typedef value_type&         					reference;
			typedef const value_type&   					const_reference;
			typedef typename allocator_type::pointer 		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			

			typedef typename ft::iterator_map<value_type>			    	iterator;        //legacy bidirectionnal iterator to value_type
			//typedef typename ft::const_iterator_map<value_type>	    		const_iterator;  //legacy bidirectionnal iterator to const value_type
			typedef typename ft::reverse_iterator<iterator>		    		reverse_iterator;
			//typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename Alloc::template rebind<rbt>::other    new_alloc;

		/****
			Constructors
		****/
		//Default constructor
		explicit map( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
			: _alloc(alloc), _cmp(comp)
		{
			_rbt = new rbt(_cmp, _alloc);
			//_rbt = newNode(ft::make_pair(key_type(), mapped_type()));
			//_end = _rbt;
		};

		//Range constructor
		/*template <class InputIterator>
		map( InputIterator first, InputIterator last, 
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type() )
		: _alloc(alloc), _cmp(comp), _rbt(0)
		{
			//_rbt = newNode(ft::make_pair(key_type(), mapped_type()));
			//_end = _rbt;
			//insert(first, last);
		};*/

		//Copy constructor
		//map( const map& src ) { *this = src; };

		//Destructor
		~map()
		{
			delete _rbt;
			//clear();
		}

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
		iterator        begin() { return iterator(_rbt->minimum(_rbt->getRoot())); };
		//const_iterator  begin() const { return const_iterator(_rbt->minimum(_rbt)); };
		iterator        end() { return iterator(_rbt->getNil()); };
		//const_iterator  end() const { return const_iterator(_rbt->getNil()); };

		reverse_iterator        rbegin() { return reverse_iterator(_rbt->getNil()); };
		//const_reverse_iterator  rbegin() const { return const_reverse_iterator(_rbt->getNil()); }; //Ou maximum ?
		reverse_iterator        rend() { return reverse_iterator(_rbt->minimum(_rbt->getRoot())); };
		//const_reverse_iterator  rend() const { return const_reverse_iterator(_rbt->minimum(_rbt)); };

		/****
			Capacity
		****/
		bool        empty() const { return _rbt->getSize() == 0; };
		size_type   size() const { return _rbt->getSize(); };
		size_type   max_size() const { return _rbt->getRBtAlloc().max_size(); };
		

//Faire at




		/****
			Element access
		****/
	//Return ref to mapped value
	//OR, if value not found -> insert new value initialized with k
		mapped_type& operator[]( const key_type& key ) 
		{
			rbt_node_ptr node = _rbt->searchTree(key, _rbt->getRoot());
			if (node == NULL || node == _rbt->getNil())
				return insert(ft::make_pair(key, T())).first->second;
			else
				return node->data.second;
		};

		/****
			Modifiers
		****/
		//void 	clear() { };
		//void 	swap( map& x ) { };
		/*void		erase( iterator position ) 
		{
			rbt* node = searchTree(position->first, _rbt);
			if (node)
				_erase(node);
		};
		size_type	erase( const key_type& k ) 
		{ 
			size_type tmp = _size;
			rbt* node = searchTree(k, _rbt);
			erase(node);
			return tmp - _size;
		};
		void		erase( iterator first, iterator last) 
		{*/
			/*if (first == begin() && last == end())
				clear();*/

			//Start from the end
			/*while (first != last)
			{
				erase(first++);
			}
		};*/
		ft::pair<iterator, bool>	insert( const value_type& val ) 
		{
			ft::pair<iterator, bool> ret;

			size_type tmp_size = _rbt->getSize();
			rbt_node_ptr node = _rbt->_insertSingle(val);

			if (_rbt->getSize() != tmp_size)
				ret.second = true;
			else
				ret.second = false;
			ret.first = iterator(node);
			return ret;
		};
		iterator	insert( iterator position, const value_type& val ) 
		{
			iterator it = position;
			//rbt_node_ptr node = _rbt->_insertSingle(val);
	
			return iterator(_rbt->_insertSingle(val));
		};
		template <class InputIterator>
		void	insert( InputIterator first, InputIterator last ) 
		{
			for ( ; first != last; first++)
			{
				_rbt->_insertSingle(*first);
			}
				
		};


		/****
			Observers
		****/
		key_compare 	key_comp() const { return _rbt->getCompare(); };

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
		value_compare	value_comp() const { return (value_compare(_rbt->getCompare())); };

		/****
			Operations
		****/
		iterator		find( const key_type& key ) 
		{ 
			iterator it = _rbt->searchTree(key, _rbt->getRoot());

			if (it->first)
				return it;
			return (_rbt->getNil());
			//return iterator(_rbt->searchTree(key, _rbt->getRoot()));
		};
		/*const_iterator	find( const key_type& k ) const 
		{
			const_iterator it = _rbt->searchTree(key, _rbt->getRoot());

			if (it->first)
				return it;
			return (_rbt->getNil());
		};*/
		size_type		count( const key_type& key ) const 
		{ return (_rbt->count(key)); };
		//iterator		lower_bound( const key_type& k ) { };
		//const_iterator	lower_bound( const key_type& k ) const { };
		//iterator		upper_bound( const key_type& k ) { };
		//const_iterator	upper_bound( const key_type& k ) const { };
		//ft::pair<iterator, iterator>				equal_range( const key_type& k ) { };
		//ft::pair<const_iterator, const_iterator>	equal_range( const key_type& k ) const { };
		
rbt*	getTree() const
{
	return _rbt;
}
/****************************************************************
						 Private members
*****************************************************************/
		private:
			allocator_type  	_alloc;
			Compare				_cmp;
			//new_alloc			_alloc_rbt;
			rbt*				_rbt;

			



/****************************************************************
						Private functions
*****************************************************************/
		/*private:

		

			rbt* searchTree(const key_type& key, rbt* root) 
			{
				if(!root) 
					return NULL; //return root ?

				while (root) 
				{
					if (key == root->data.first)
						return root;
					else if (key < root->data.first)
						root = root->left;
					else 
						root = root->right;
				}
				return NULL;
			}


		void _rbTransplant(rbt* x, rbt* y)
		{
			if (x->parent == NULL || x->parent == _end)
				_rbt = y;
			if (x->parent)
			{
				if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
			}
			if (y && x)
				y->parent = x->parent;
		}
*/
		/*void _erase(rbt* z)
		{
			if (_rbt == NULL || _rbt == _end)
				return ;

			rbt* x = NULL;
			rbt* y = z;
			int y_original_color = y->color;
			if (z->left == NULL)
			{
				x = z->right;
				_rbTransplant(z, z->right);
			}
			else if (z->right == NULL)
			{
				x = z->left;
				_rbTransplant(z, z->left);
			}
			else
			{
				if (z->right)
					y = minimum(z->right);
				y_original_color = y->color;
				
				x = y->right;
				if (y->parent == z && x)
					x->parent = y;
				else
				{
					_rbTransplant(y, y->right);
					y->right = z->right;
					if (y->right != NULL)
						y->right->parent = y;
				}
				_rbTransplant(z, y);
				y->left = z->left;
				if (y->left != NULL)
					y->left->parent = y;
				y->color = z->color;
			}
			if (y_original_color == BLACK)
			{
				if (!x)
					_eraseFix(y);
				else
					_eraseFix(x);
			}
			_deleteNode(z);
		}*/
//https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
		/*void _erase(rbt* z)
		{
			_update_min_max_for_erased_node(z);
			rbt* y = z;
			rbt* x = NULL;
			rbt* new_x_parent = NULL;

			if (y->left == NULL)
				x = y->right;
			else if (y->right == NULL)
				x = y->left;
			else
			{
				y = y->right;
				while (y->left != NULL)
					y = y->left;
				x = y->right;
			}
			if (y == z)
			{
				new_x_parent = y->parent;
				if (x != NULL)
					x->parent = y->parent;
				if (_rbt->parent == z)
					_rbt->parent = x;
				else if (z->parent->left == z)
				{
					y->left = z->parent;
					z->parent->left = x;
				}
				else
				{
					y->left = NULL;
					z->parent->right = x;
				}
			}
			else
			{
				z->left->parent = y;
				y->left = z->left;
				if (y != z->right)
				{
					new_x_parent = y->parent;
					if (x != NULL)
						x->parent = y->parent;
					y->parent->left = x;
					y->right = z->right;
					z->right->parent = y;
				}
				else
					new_x_parent = y;
				y->parent = z->parent;
				bool tmp = y->color;
				y->color = z->color;
				z->color = tmp;
				y = z;
			}
			if (y->color == RED)
			{
				_deleteNode(y);
				return ;
			}
			_deleteNode(y);
			_eraseFix(x, new_x_parent);
		}*/

		/*void _erase(rbt* x)
		{
			if (x->parent != NULL) 
			{
				if (x->right != NULL) 
				{
					if (x->parent->right == x)
						x->parent->right = x->right;
					else
						x->parent->left = x->right;
					x->right->parent = x->parent;

					if (x->left != NULL) 
					{
						rbt *tmp = x->right;
						while (tmp->left)
							tmp = tmp->left;
						tmp->left = x->left;
						x->left->parent = tmp;
					}
				}
				else if (x->left != NULL) 
				{
					if (x->parent->right == x)
						x->parent->right = x->left;
					else
						x->parent->left = x->left;
					x->left->parent = x->parent;
				}
				else {
					if (n == n->parent->right)
						n->parent->right = NULL;
					else
						n->parent->left = NULL;
				}
			}
			else {
				if (x->right != NULL) 
				{
					_rbt = x->right;
					x->right->parent = NULL;

					if (x->left != NULL) 
					{
						rbt *tmp = x->right;
						while (tmp->left)
							tmp = tmp->left;
						tmp->left = x->left;
						x->left->parent = tmp;
					}
				}
				else if (x->left != NULL) 
				{
					_rbt = x->left;
					x->left->parent = NULL;
				}
				else 
					_rbt = _end;
			}
			if (x->color == BLACK)
				_eraseFix(x);
			_deleteNode(x);
		}*/
/*
		void _erase( rbt * z )
		{
			
		}

		void _eraseFix(rbt* x)
		{
			while (x != _rbt && x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					rbt* w = x->parent->right;
					if (w && w->color == RED)
					{
						w->color = BLACK;
						x->parent->color = RED;
						leftRotate(x->parent);
						w = x->parent->right;
					}
					if ( w && w->left && w->right && w->left->color == BLACK && w->right->color == BLACK)
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if (w && w->right && w->right->color == BLACK)
						{
							w->left->color = BLACK;
							w->color = RED;
							rightRotate(w);
							w = x->parent->right;
						}
						if (w)
							w->color = x->parent->color;
						x->parent->color = BLACK;
						if (w && w->right)
							w->right->color = BLACK;
						leftRotate(x->parent);
						x = _rbt;
					}
				}
				else
				{
					rbt* w = x->parent->left;
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
							if (w->right)
								w->right->color = BLACK;
							w->color = RED;
							leftRotate(w);
							w = x->parent->left;
						}
						if (w)
							w->color = x->parent->color;
						x->parent->color = BLACK;
						if (w && w->left)
							w->left->color = BLACK;
						rightRotate(x->parent);
						x = _rbt;
					}
				}
			}
			x->color = BLACK;
		}

		void _update_min_max_for_erased_node( rbt* z )
		{
			if (_size == 1)
			{
				_rbt->left = _rbt;
				_rbt->right = _rbt;
			}
			if (_rbt->left == z)
			{
				iterator it(z);
				++it;
				_rbt->left = it._node;
			}
			else if (_rbt->right == z)
			{
				iterator it(z);
				--it;
				_rbt->right = it._node;
			}
		}

		void _eraseFix(rbt* p_x, rbt* p_new_x_parent)
		{
			while (p_x != _rbt->parent && p_x != _end && p_x && p_x->color == BLACK)
			{
				if (p_x == p_new_x_parent->left)
				{
					rbt* p_w = p_new_x_parent->right;
					if (p_w->color == RED)
					{
						p_w->color = BLACK;
						p_new_x_parent->color = RED;
						leftRotate(p_new_x_parent);
						p_w = p_new_x_parent->right;
					}

					if (p_w && p_w->left->color == BLACK && p_w->right->color == BLACK)
					{
						p_w->color = RED;
						p_x = p_new_x_parent;
						p_new_x_parent = p_new_x_parent->parent;
					}
					else
					{
						if (p_w && p_w->right->color == BLACK)
						{
						if (p_w->left != 0)
						p_w->left->color = BLACK;

						p_w->color = RED;
						rightRotate(p_w);
						p_w = p_new_x_parent->right;
						}

						p_w->color = p_new_x_parent->color;
						p_new_x_parent->color = BLACK;

						if (p_w->right != 0)
						p_w->right->color = BLACK;

						leftRotate(p_new_x_parent);
						break;
					}
				}
				else
				{
					rbt* p_w = p_new_x_parent->left;
					if (p_w->color == RED)
					{
						p_w->color = BLACK;
						p_new_x_parent->color = RED;
						rightRotate(p_new_x_parent);
						p_w = p_new_x_parent->left;
					}

					if (p_w->right->color == BLACK 
						&& p_w->left->color == BLACK)
					{
						p_w->color = RED;
						p_x = p_new_x_parent;
						p_new_x_parent = p_new_x_parent->parent;
					}
					else
					{
						if (p_w->left->color == BLACK)
						{
							if (p_w->right != 0)
								p_w->right->color = BLACK;

							p_w->color = RED;
							leftRotate(p_w);
							p_w = p_new_x_parent->left;
						}

						p_w->color = p_new_x_parent->color;
						p_new_x_parent->color = BLACK;

						if (p_w->left != 0)
							p_w->left->color = BLACK;

						rightRotate(p_new_x_parent);
						//this->update_to_top(p_new_x_parent, (node_update* )this);
						break;
					}
				}
			}
		}

*/

			

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