#ifndef SET_HPP
# define SET_HPP

# include <memory>

namespace ft
{
	template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		/****************************************************************
								 Definitions
		****************************************************************/
		public:
			typedef T			key_type;
			typedef T			value_type;
			typedef Compare		key_compare;
			typedef Compare		value_compare;
			typedef Alloc		allocator_type;

			typedef value_type&			reference;
			typedef const value_type&	const_reference;

			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;

			typedef ft::RBTree<key_type, key_compare, allocator_type>	rbt;

		private:
			typedef ft::rbt_node<value_type>	rbt_node;
			typedef ft::rbt_node<value_type>*	rbt_node_ptr;

		public:
			typedef typename ft::bidirectionnal_iterator<value_type>	iterator;
			typedef typename ft::bidirectionnal_iterator<value_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;

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
								 Private members
		*****************************************************************/
		private:
			key_compare		_cmp;
			allocator_type	_alloc;
			rbt*			_rbt;


		/****************************************************************
								 Constructors
		****************************************************************/
		//Default constructor
		explicit set( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
			: _cmp(comp), _alloc(alloc), _rbt(0)
		{ _rbt = new rbt(_cmp, _alloc); };

		//Range constructor
		template <class InputIt>
		set ( InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
			: _cmp(comp), _alloc(alloc), _rbt(0)
		{
			_rbt = new rbt(_cmp, _alloc);
			insert(first, last);
		};

		//Copy constructor
		set ( const set& other )
		{ *this = other; };

		set& operator=( const set& other )
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

		~set()
		{
			clear();
			delete _rbt;
		};

		allocator_type get_allocator() const { return _alloc; };


		/****************************************************************
								 Iterators
		*****************************************************************/
		


		/****************************************************************
								  Capacity
		*****************************************************************/


		/****************************************************************
								  Modifiers
		*****************************************************************/

		/****************************************************************
								 Observers
		*****************************************************************/


		/****************************************************************
								 Operations
		*****************************************************************/


	};

} //ft

#endif