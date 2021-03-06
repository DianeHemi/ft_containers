#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <cstddef>

namespace ft
{
/****************************************************************
						 Iterator tags
*****************************************************************/
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };


/****************************************************************
						Iterator traits
*****************************************************************/
	template<class Iter>
	struct iterator_traits
	{
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};
	
	template<class T>
	struct iterator_traits<T*>
	{
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag 	iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*>
	{
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ft::random_access_iterator_tag 	iterator_category;
	};


/****************************************************************
				  Iterator category base class
*****************************************************************/
	template<
		class Category,                     //Category of the iterator
		class T,                            //Type of values that can be obtained by dereferencing the iterator
		class Distance = std::ptrdiff_t,    //A type that can be used to identify distance between iterators
		class Pointer = T*,                 //Defines a pointer to the type iterated over (T)
		class Reference = T&                //Defines a reference to the type iterated over (T)
	> struct iterator
	{
		public:
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
	};


/****************************************************************
				  Distance between two operators
*****************************************************************/
	template < class InputIt >
	typename ft::iterator_traits<InputIt>::difference_type it_distance ( InputIt start, InputIt end )
	{
		typename ft::iterator_traits< InputIt >::difference_type distance = 0;
		for ( ; start != end; start++)
			distance++;
		return distance;
	};


/****************************************************************
						Reverse iterator
*****************************************************************/
	template<class Iter>
	class reverse_iterator
	{
		public:
			typedef	Iter	iterator_type;
			typedef typename	iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename	iterator_traits<Iter>::value_type			value_type;
			typedef typename	iterator_traits<Iter>::difference_type		difference_type;
			typedef typename	iterator_traits<Iter>::pointer				pointer;
			typedef typename	iterator_traits<Iter>::reference			reference;


			/****************************************************************
									Constructeurs
			****************************************************************/
			reverse_iterator( ) : _current(NULL) { };
			explicit reverse_iterator( iterator_type x ) : _current(x) { };
			template< class U >
				reverse_iterator( const reverse_iterator<U>& rhs ) : _current(rhs.base()) { };
			template< class U >
				reverse_iterator& operator=( const reverse_iterator<U>& rhs )
			{
				_current = rhs.base();
				return *this;
			};
			~reverse_iterator() { };


			/****************************************************************
									Member functions
			****************************************************************/
			iterator_type	base() const { return _current; };
			reference	operator*() const { Iter tmp = _current; return *--tmp; };
			pointer		operator->() const { return &(operator*()); };
			reference	operator[]( difference_type n ) const { return (base()[-n-1]); };

			reverse_iterator&	operator++() { --_current; return *this; };
			reverse_iterator 	operator++(int) { reverse_iterator tmp(*this); _current--; return tmp; };
			reverse_iterator&	operator--() { ++_current; return *this; };
			reverse_iterator	operator--(int) { reverse_iterator tmp(*this); _current++; return tmp; };
			

			reverse_iterator&	operator+=( difference_type n ) { _current -= n; return *this; };
			reverse_iterator&	operator-=( difference_type n ) { _current += n; return *this; };

			reverse_iterator	operator+(difference_type n) const { return reverse_iterator(base() - n); };
			reverse_iterator	operator-(difference_type n) const { return reverse_iterator(base() + n); };
			
		protected:
			Iter	_current;
	};


/****************************************************************
					 Non-member functions
****************************************************************/
	template< class Iter1, class Iter2 >
	bool	operator==( const reverse_iterator<Iter1> & lhs,
						const reverse_iterator<Iter2> & rhs ) 
	{ 
		return (lhs.base() == rhs.base()); 
	};

	template< class Iter1, class Iter2 >
	bool	operator!=( const reverse_iterator<Iter1> & lhs,
						const reverse_iterator<Iter2> & rhs )
	{ 
		return (lhs.base() != rhs.base()); 
	};

	template< class Iter1, class Iter2 >
	bool	operator<( const reverse_iterator<Iter1> & lhs,
						const reverse_iterator<Iter2> & rhs )
	{ 
		return (lhs.base() > rhs.base()); 
	};

	template< class Iter1, class Iter2 >
	bool	operator<=( const reverse_iterator<Iter1> & lhs,
						const reverse_iterator<Iter2> & rhs ) 
	{ 
		return (lhs.base() >= rhs.base());
	};

	template< class Iter1, class Iter2 >
	bool	operator>( const reverse_iterator<Iter1> & lhs,
						const reverse_iterator<Iter2> & rhs ) 
	{ 
		return (lhs.base() < rhs.base());
	};

	template< class Iter1, class Iter2 >
	bool	operator>=( const reverse_iterator<Iter1> & lhs,
						const reverse_iterator<Iter2> & rhs ) 
	{ 
		return (lhs.base() <= rhs.base());
	};

	template <class Iterator>
  	reverse_iterator<Iterator> operator+ (
           typename reverse_iterator<Iterator>::difference_type n,
           const reverse_iterator<Iterator>& x)
	{
		return (reverse_iterator<Iterator>(x.base() - n));
	};

	template <class Iter1, class Iter2>
  	typename reverse_iterator<Iter1>::difference_type operator- (
    	const reverse_iterator<Iter1>& lhs,
    	const reverse_iterator<Iter2>& rhs)
	{
		return (rhs.base() - lhs.base());
	};

} //ft

#endif
