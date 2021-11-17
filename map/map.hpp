#ifndef MAP_HPP
# define MAP_HPP

# include "pair.hpp"
# include "iterator_map.hpp"
# include <memory>
# include <iostream>


# include "tree_test_cleaned.cpp"

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
			typedef ft::RedBlackTree<value_type>	rbt; //typedef pour rbt ?

			typedef value_type&         					reference;
			typedef const value_type&   					const_reference;
			typedef typename allocator_type::pointer 		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			

			typedef typename ft::iterator_map<value_type>			    iterator;        //legacy bidirectionnal iterator to value_type
			//typedef typename ft::const_iterator_map<value_type>	    const_iterator;  //legacy bidirectionnal iterator to const value_type
			//typedef typename ft::reverse_iterator<value_type>		    reverse_iterator;
			//typedef typename ft::const_reverse_iterator<value_type>	const_reverse_iterator
			//typedef typename alloc::template rebind<Node>::other    new_alloc;

		/****
			Constructors
		****/
		//Default constructor
		explicit map( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
			: _alloc(alloc), _size(0), _cmp(comp)
		{

		};

		//Range constructor
		/*template <class InputIterator>
		map( InputIterator first, InputIterator last, 
			const key_compare& cmp = key_compare,
			const allocator_type& alloc = allocator_type() )
		: 
		{

		};*/

		//Copy constructor
		//map( const map& src ) { *this = src; };

		//Destructor
		/*~map()
		{

		}*/

		//Overload operator =
		/*map& operator=( const & map rhs )
		{
			if (this != &rhs)
			{
				//clear();
				insert(begin(), rhs.begin(), rhs.end());
				_size = rhs._size;
			}
			return *this;
		};*/

		allocator_type get_allocator() const { return _alloc; };


		/****
			Iterators
		****/
		iterator        begin() { return iterator(_rbt->minimum()->data); };
		//const_iterator  begin() { };
		iterator        end() { return iterator(_rbt->maximum()->data); };
		//const_iterator  end() { };

		//reverse_iterator        rbegin() { };
		//const_reverse_iterator  rbegin() { };
		//reverse_iterator        rend() { };
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
		//ft::pair<iterator, bool>	insert( const value_type& val ) { };
		//iterator	insert( iterator position, const value_type& val ) { };
		/*template <class InputIterator>
		void	insert( InputIterator first, InputIterator last ) 
		{

		};*/

		/****
			Observers
		****/
		//key_compare 	key_comp() const { return _cmp; };

		class value_compare
		{
			//friend class map;
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
		


		private:
			allocator_type  	_alloc;
			size_type       	_size;
			Compare				_cmp;
		public:
			rbt*				_rbt;
			//Node*				_root;


		//Elements relatifs a l'arbre binaire
		//creation des nodes, free des nodes, suppression node,  
		//insertion node, recherche d'une node, clear arbre, copy tree ?

	};





	/*template< class Key, class T, class Compare, class Alloc >
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

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs )
	{

	}*/

}

#endif