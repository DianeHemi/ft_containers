#ifndef MAP_HPP
# define MAP_HPP

# include "iterator_map.hpp"
# include "../lexicographical_compare.hpp"
# include <memory>

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, 
			class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		/****************************************************************
								 Definitions
		****************************************************************/
		public:
			typedef Key					key_type;
			typedef T					mapped_type;
			typedef std::size_t			size_type;
			typedef std::ptrdiff_t		difference_type;
			typedef Compare				key_compare;
			typedef Allocator			allocator_type;

			typedef typename ft::pair<const Key, T> value_type;
			typedef ft::RBTree<key_type, mapped_type, key_compare, allocator_type>	rbt;

		private:
			typedef ft::rbt_node<value_type>	rbt_node;
			typedef ft::rbt_node<value_type>*	rbt_node_ptr;

		public:
			typedef value_type&         					reference;
			typedef const value_type&   					const_reference;
			typedef typename allocator_type::pointer 		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			

			typedef typename ft::iterator_map<value_type>			iterator;
			typedef typename ft::const_iterator_map<value_type>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			class value_compare
			{
				public:
					typedef	bool		result_type;
					typedef	value_type	first_argument_type;
					typedef	value_type	second_argument_type;

					value_compare( Compare c ) : comp(c) { };
					bool operator()( const value_type& left, const value_type& right ) const 
					{ return (comp(left.first, right.first)); };

				protected:
					Compare comp;
			};

		/****************************************************************
								 Constructors
		****************************************************************/
		//Default constructor
		explicit map( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
			: _alloc(alloc), _cmp(comp)
		{
			_rbt = new rbt(_cmp, _alloc);
		};

		//Range constructor
		template <class InputIt>
		map( InputIt first, InputIt last, 
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type() )
		: _alloc(alloc), _cmp(comp), _rbt(0)
		{
			_rbt = new rbt(_cmp, _alloc);
			insert(first, last);
		};

		//Copy constructor
		map( const map& other ) { *this = other; };

		//Destructor
		~map()
		{
			clear();
			delete _rbt;
		}

		//Overload operator =
		map& operator=( const map& other )
		{
			if (this != &other)
			{
				_alloc = other._alloc;
				_cmp = other._cmp;
				_rbt = new rbt(_cmp, _alloc);
				insert(other.begin(), other.end());
			}
			return *this;
		};

		allocator_type get_allocator() const { return _alloc; };


		/****************************************************************
								 Element access
		*****************************************************************/
		mapped_type& at( const key_type& key )
		{
			rbt_node_ptr node = _rbt->searchTree(key, _rbt->getRoot());
			if (node == NULL || node == _rbt->getNil())
				throw std::out_of_range("map::at");
			else
				return node->data.second;
		};

		const mapped_type& at( const key_type& key ) const
		{
			rbt_node_ptr node = _rbt->searchTree(key, _rbt->getRoot());
			if (node == NULL || node == _rbt->getNil())
				throw std::out_of_range("map::at");
			else
				return node->data.second;
		};

		mapped_type& operator[]( const key_type& key ) 
		{
			rbt_node_ptr node = _rbt->searchTree(key, _rbt->getRoot());
			if (node == NULL || node == _rbt->getNil())
				return insert(ft::make_pair(key, T())).first->second;
			else
				return node->data.second;
		};


		/****************************************************************
									Iterators
		****************************************************************/
		iterator		begin() { return iterator(_rbt->minimum(_rbt->getRoot())); };
		const_iterator	begin() const { return const_iterator(_rbt->minimum(_rbt->getRoot())); };
		iterator		end() { return iterator(_rbt->getNil()); };
		const_iterator	end() const { return const_iterator(_rbt->getNil()); };

		reverse_iterator		rbegin() { return reverse_iterator(_rbt->getNil()); };
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(_rbt->getNil()); }; //Ou maximum ?
		reverse_iterator		rend() { return reverse_iterator(_rbt->minimum(_rbt->getRoot())); };
		const_reverse_iterator	rend() const { return const_reverse_iterator(_rbt->minimum(_rbt)); };


		/****************************************************************
									Capacity
		****************************************************************/
		bool		empty() const { return _rbt->getSize() == 0; };
		size_type	size() const { return _rbt->getSize(); };
		size_type	max_size() const { return _rbt->getRBtAlloc().max_size(); };
		

		/****************************************************************
								 Modifiers
		*****************************************************************/
		ft::pair<iterator, bool>	insert( const value_type& value )
		{
			ft::pair<iterator, bool> ret;
			size_type tmp_size = _rbt->getSize();
			rbt_node_ptr node = _rbt->_insertSingle(value);

			if (_rbt->getSize() != tmp_size)
				ret.second = true;
			else
				ret.second = false;
			ret.first = iterator(node);
			return ret;
		};

		iterator	insert( iterator position, const value_type& value )
		{
			iterator it = position;
			return iterator(_rbt->_insertSingle(value));
		};

		template <class InputIt>
		void	insert( InputIt first, InputIt last )
		{
			for ( ; first != last; first++)
			{
				_rbt->_insertSingle(*first);
			}
		};

		void		erase( iterator position )
		{
			rbt_node* node = _rbt->searchTree(position->first, _rbt->getRoot());
			if (node)
				_rbt->_erase(node);
		};

		void		erase( iterator first, iterator last)
		{
			while (first != last)
			{
				erase(first++);
			}
		};

		size_type	erase( const key_type& key )
		{
			size_type tmp = _rbt->getSize();
			rbt_node* node = _rbt->searchTree(key, _rbt->getRoot());
			if (node)
				_rbt->_erase(node);
			return tmp - _rbt->getSize();
		};

		void 	swap( map& other ) { _rbt->swap(*other._rbt); };
		void 	clear() { erase(begin(), end()); };


		/****************************************************************
								 Observers
		*****************************************************************/
		key_compare 	key_comp() const { return _rbt->getCompare(); };
		value_compare	value_comp() const { return (value_compare(_rbt->getCompare())); };


		/****************************************************************
								 Operations
		*****************************************************************/
		iterator		find( const key_type& key ) 
		{ 
			iterator it = begin();
			iterator ite = end();

			while (it != ite)
			{
				if (!_cmp(it->first, key) && !_cmp(key, it->first))
					return it;
				it++;
			};
			return end();
		};

		const_iterator	find( const key_type& key ) const 
		{
			const_iterator it = _rbt->searchTree(key, _rbt->getRoot());

			if (it->first)
				return it;
			return (_rbt->getNil());
		};

		size_type		count( const key_type& key ) const 
		{ return (_rbt->count(key)); };

		iterator		lower_bound( const key_type& key )  //First element greater or equal
		{ return iterator((_rbt->lower_bound(key))); };

		const_iterator	lower_bound( const key_type& key ) const 
		{ return const_iterator((_rbt->lower_bound(key))); };

		iterator		upper_bound( const key_type& key )	//First element greater than
		{ return iterator((_rbt->upper_bound(key))); };

		const_iterator	upper_bound( const key_type& key ) const 
		{ return const_iterator((_rbt->upper_bound(key))); };

		ft::pair<iterator, iterator>	equal_range( const key_type& key )	//Range : first greater or equal + 
		{
			ft::pair<iterator, iterator> ret;
			
			ret.first = iterator(_rbt->lower_bound(key));
			ret.second = iterator(_rbt->upper_bound(key));
			return ret;
		};

		ft::pair<const_iterator, const_iterator>	equal_range( const key_type& key ) const 
		{
			ft::pair<const_iterator, const_iterator> ret;
			
			ret.first = const_iterator(_rbt->lower_bound(key));
			ret.second = const_iterator(_rbt->upper_bound(key));
			return ret;
		};


		/****************************************************************
								 Private members
		*****************************************************************/
		private:
			allocator_type  	_alloc;
			Compare				_cmp;
			rbt*				_rbt;
	};


/****************************************************************
						 Non-member functions
****************************************************************/
	template< class Key, class T, class Compare, class Allocator >
	bool operator==( const ft::map<Key,T,Compare,Allocator>& lhs, const ft::map<Key,T,Compare,Allocator>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class Key, class T, class Compare, class Allocator >
	bool operator!=( const ft::map<Key,T,Compare,Allocator>& lhs, const ft::map<Key,T,Compare,Allocator>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Allocator >
	bool operator<( const ft::map<Key,T,Compare,Allocator>& lhs, const ft::map<Key,T,Compare,Allocator>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class Key, class T, class Compare, class Allocator >
	bool operator<=( const ft::map<Key,T,Compare,Allocator>& lhs, const ft::map<Key,T,Compare,Allocator>& rhs )
	{
		return !(rhs < lhs);
	}

	template< class Key, class T, class Compare, class Allocator >
	bool operator>( const ft::map<Key,T,Compare,Allocator>& lhs, const ft::map<Key,T,Compare,Allocator>& rhs )
	{
		return rhs < lhs;
	}

	template< class Key, class T, class Compare, class Allocator >
	bool operator>=( const ft::map<Key,T,Compare,Allocator>& lhs, const ft::map<Key,T,Compare,Allocator>& rhs )
	{
		return !(lhs < rhs);
	}

	template< class Key, class T, class Compare, class Allocator >
	void swap( ft::map<Key,T,Compare,Allocator>& lhs, ft::map<Key,T,Compare,Allocator>& rhs )
	{
		lhs.swap(rhs);
	}

} //ft

#endif