#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <cstddef>

//https://githubmemory.com/repo/maxime-42/ft_containers
//https://www.fluentcpp.com/2018/05/08/std-iterator-deprecated/
//https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
//https://www.cplusplus.com/reference/iterator/iterator_traits/


namespace ft
{
	/*
		Iterator tags
	*/
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };


	/*
		Iterator traits
	*/
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

	/*
		Iterator base class
	*/
	template<
		class Category,                     //Category of the iterator
		class T,                            //Type of valuesthat can be obtained by dereferencing the iterator
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



	/*
		Reverse iterator
	*/
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


			/****
			 * Constructors
			****/
			reverse_iterator( ) : _current(NULL) { };
			explicit reverse_iterator( iterator_type x ) : _current(x) { };
			template< class U >
				reverse_iterator( const reverse_iterator<U>& other ) : _current(other.base()) { };
			template< class U >
				reverse_iterator& operator=( const reverse_iterator<U>& other )
			{
				_current = other.base();
				return *this;
			};
			~reverse_iterator() { };

			/****
			 * Member functions
			****/
			iterator_type	base() const { return _current; };
			reference	operator*() const { Iter tmp = _current; return *--tmp; };
			pointer		operator->() const { return &(operator*()); };
			reference	operator[]( difference_type n ) const { return (base()[-n-1]); };

			reverse_iterator&	operator++() { --_current; return *this; };
			reverse_iterator 	operator++(int) { reverse_iterator tmp(_current); --_current; return tmp; };
			reverse_iterator&	operator--() { ++_current; return *this; };
			reverse_iterator	operator--(int) { reverse_iterator tmp(_current); ++_current; return tmp; };
			

			reverse_iterator&	operator+=( difference_type n ) { _current -= n; return *this; };
			reverse_iterator&	operator-=( difference_type n ) { _current += n; return *this; };

			reverse_iterator	operator+(difference_type n) const { return reverse_iterator(base() - n); };
			reverse_iterator	operator-(difference_type n) const { return reverse_iterator(base() + n); };
			
		protected:
			Iter	_current;
	};



	template< class Iterator >
	bool	operator==( const reverse_iterator<Iterator> & rhs,
						const reverse_iterator<Iterator> & lhs ) 
	{ 
		return (lhs.base() == rhs.base()); 
	};

	template< class Iterator >
	bool	operator!=( const reverse_iterator<Iterator> & rhs,
						const reverse_iterator<Iterator> & lhs )
	{ 
		return (lhs.base() != rhs.base()); 
	};

	template< class Iterator >
	bool	operator<( const reverse_iterator<Iterator> & rhs,
						const reverse_iterator<Iterator> & lhs )
	{ 
		return (lhs.base() > rhs.base()); 
	};

	template< class Iterator >
	bool	operator<=( const reverse_iterator<Iterator> & rhs,
						const reverse_iterator<Iterator> & lhs ) 
	{ 
		return (lhs.base() >= rhs.base());
	};

	template< class Iterator >
	bool	operator>( const reverse_iterator<Iterator> & rhs,
						const reverse_iterator<Iterator> & lhs ) 
	{ 
		return (lhs.base() < rhs.base());
	};

	template< class Iterator >
	bool	operator>=( const reverse_iterator<Iterator> & rhs,
						const reverse_iterator<Iterator> & lhs ) 
	{ 
		return (lhs.base() <= rhs.base());
	};

	template <class Iterator>
  	reverse_iterator<Iterator> operator+ (
           typename reverse_iterator<Iterator>::difference_type n,
           const reverse_iterator<Iterator>& rev_it)
	{
		return (reverse_iterator<Iterator>(rev_it.base() - n));
	};

	template <class Iterator>
  	typename reverse_iterator<Iterator>::difference_type operator- (
    	const reverse_iterator<Iterator>& lhs,
    	const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	};




	

} //ft

#endif







//Bidirectional : map & set
	// ++, -- sauf si const. Avec *. ->, ==, !=
//Random-access iterator : vector
	// ++, +=, --, -= sauf si const. Avec * ou []. ->, ==, !=, <, <=, >, >=

//iterateur pesonnalise pour vector + iterateur personnalise pour map. Sont differents