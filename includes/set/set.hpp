#ifndef SET_HPP
# define SET_HPP

# include <memory>
# include "../lexicographical_compare.hpp"
# include "iterator_set.hpp"

/*
	https://www.cplusplus.com/reference/set/set/?kw=set

	https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf
	P 515/523 du pdf (489/497)
*/

namespace ft
{
	template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		/****************************************************************
								 Definitions
		****************************************************************/
		public:
			typedef T				key_type;
			typedef T				value_type;
			typedef Compare			key_compare;
			typedef Compare			value_compare;
			typedef Alloc			allocator_type;
			typedef std::size_t		size_type;
			typedef std::ptrdiff_t	difference_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;

			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;

		private:
			typedef ft::RBTree<value_type, key_compare, allocator_type>	rbt;
			typedef ft::rbt_node<value_type>	rbt_node;
			typedef ft::rbt_node<value_type>*	rbt_node_ptr;

		public:
			typedef typename ft::const_iterator_set<value_type>		iterator;
			typedef typename ft::const_iterator_set<value_type>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			
		/****************************************************************
								 Private members
		*****************************************************************/
		private:
			std::allocator<rbt>	_talloc;
			key_compare			_cmp;
			allocator_type		_alloc;
			rbt*				_rbt;


		/****************************************************************
								 Constructors
		****************************************************************/
		public:
		//Default constructor
		explicit set( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
			: _cmp(comp), _alloc(alloc), _rbt(0)
		{
			_rbt = _talloc.allocate(1);
			_talloc.construct(_rbt, rbt(_cmp, _alloc));
		};

		//Range constructor
		template <class InputIt>
		set ( InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
			: _cmp(comp), _alloc(alloc), _rbt(0)
		{
			_rbt = _talloc.allocate(1);
			_talloc.construct(_rbt, rbt(_cmp, _alloc));
			insert(first, last);
		};

		//Copy constructor
		set ( const set& other )
		{
			_alloc = other._alloc;
			_cmp = other._cmp;
			_rbt = _talloc.allocate(1);
			_talloc.construct(_rbt, rbt(_cmp, _alloc));
			insert(other.begin(), other.end());
		};

		set& operator=( const set& other )
		{
			if (this != &other)
			{
				if (_rbt)
				{
					_rbt->clearTree();
					_talloc.destroy(_rbt);
					_talloc.deallocate(_rbt, 1);
				}
				_alloc = other._alloc;
				_cmp = other._cmp;
				_rbt = _talloc.allocate(1);
				_talloc.construct(_rbt, rbt(_cmp, _alloc));
				insert(other.begin(), other.end());
			}
			return *this;
		};

		~set()
		{
			_rbt->clearTree();
			_talloc.destroy(_rbt);
			_talloc.deallocate(_rbt, 1);
		};

		allocator_type get_allocator() const { return _alloc; };


		/****************************************************************
								 Iterators
		*****************************************************************/
		iterator begin() { return iterator(_rbt->minimum(_rbt->getRoot())); };
		const_iterator begin() const { return const_iterator(_rbt->minimum(_rbt->getRoot())); };
		iterator end() { return iterator(_rbt->getNil()); };
		const_iterator end() const { return const_iterator(_rbt->getNil()); };

		reverse_iterator rbegin() { return reverse_iterator(_rbt->getNil()); };
		const_reverse_iterator rbegin() const { return const_reverse_iterator(_rbt->getNil()); };
		reverse_iterator rend() { return reverse_iterator(_rbt->minimum(_rbt->getRoot())); };
		const_reverse_iterator rend() const { return const_reverse_iterator(_rbt->minimum(_rbt->getRoot())); };


		/****************************************************************
								  Capacity
		*****************************************************************/
		bool		empty() const { return _rbt->getSize() == 0; };
		size_type	size() const { return _rbt->getSize(); };
		size_type	max_size() const { return _rbt->getRBtAlloc().max_size(); };


		/****************************************************************
								  Modifiers
		*****************************************************************/
		ft::pair<iterator, bool> insert( const value_type& val )
		{
			ft::pair<iterator, bool> ret;
			size_type		tmp_size = _rbt->getSize();
			rbt_node_ptr	node = _rbt->_insertSingle(val);

			if (_rbt->getSize() != tmp_size)
				ret.second = true;
			else
				ret.second = false;
			ret.first = iterator(node);
			return ret;
		};

		iterator insert ( iterator pos, const value_type& val )
		{
			iterator it = pos;
			return iterator(_rbt->_insertSingle(val));
		};

		template <class InputIt>
		void insert( InputIt first, InputIt last )
		{
			for ( ; first != last; first++)
			{
				_rbt->_insertSingle(*first);
			}
		};

		void erase( iterator pos )
		{
			rbt_node* node = _rbt->searchTree(*pos, _rbt->getRoot());

			if (node)
				_rbt->_erase(node);
		};

		size_type erase( const value_type& val )
		{
			size_type	tmp = _rbt->getSize();
			rbt_node*	node = _rbt->searchTree(val, _rbt->getRoot());

			if (node)
				_rbt->_erase(node);
			return tmp - _rbt->getSize();
		};

		void erase( iterator first, iterator last )
		{
			while (first != last)
			{
				erase(first++);
			}
		};

		void	swap( set& other ) { _rbt->swap(*other._rbt); };
		void	clear() { erase(begin(), end()); };


		/****************************************************************
								 Observers
		*****************************************************************/
		key_compare		key_comp() const { return _rbt->getCompare(); };
		value_compare	value_comp() const { return (value_compare(_rbt->getCompare())); };


		/****************************************************************
								 Operations
		*****************************************************************/
		iterator find( const value_type& val ) const
		{
			iterator it = begin();
			iterator ite = end();

			while (it != ite)
			{
				if (!_cmp(*it, val) && !_cmp(val, *it))
					return it;
				it++;
			};
			return end();
		};

		size_type count( const value_type& val ) const
		{ return (_rbt->count(val)); };

		iterator lower_bound( const value_type& val ) const
		{ return iterator((_rbt->lower_bound(val))); };

		iterator upper_bound( const value_type& val ) const
		{ return iterator((_rbt->upper_bound(val))); };

		ft::pair<iterator, iterator> equal_range( const value_type& val ) const
		{
			ft::pair<iterator, iterator> ret;
			
			ret.first = iterator(_rbt->lower_bound(val));
			ret.second = iterator(_rbt->upper_bound(val));
			return ret;
		};

	};

/****************************************************************
						Non-member functions
****************************************************************/
	template< class Key, class Compare, class Alloc >
	bool operator==( const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class Key, class Compare, class Alloc >
	bool operator!=( const ft::set<Key ,Compare, Alloc>& lhs, const ft::set<Key ,Compare, Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class Key, class Compare, class Alloc >
	bool operator<( const ft::set<Key ,Compare, Alloc>& lhs, const ft::set<Key ,Compare, Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class Key, class Compare, class Alloc >
	bool operator<=( const ft::set<Key ,Compare, Alloc>& lhs, const ft::set<Key ,Compare, Alloc>& rhs )
	{
		return !(rhs < lhs);
	}

	template< class Key, class Compare, class Alloc >
	bool operator>( const ft::set<Key ,Compare, Alloc>& lhs, const ft::set<Key ,Compare, Alloc>& rhs )
	{
		return rhs < lhs;
	}

	template< class Key, class Compare, class Alloc >
	bool operator>=( const ft::set<Key ,Compare, Alloc>& lhs, const ft::set<Key ,Compare, Alloc>& rhs )
	{
		return !(lhs < rhs);
	}

	template< class Key, class Compare, class Alloc >
	void swap( ft::set<Key, Compare, Alloc>& lhs, ft::set<Key ,Compare, Alloc>& rhs )
	{
		lhs.swap(rhs);
	}

} //ft

#endif