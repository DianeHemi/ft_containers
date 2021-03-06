#ifndef ITERATOR_VECTOR_HPP
# define ITERATOR_VECTOR_HPP

# include <cstddef>
# include "../iterator_traits.hpp"

namespace ft
{
/****************************************************************
							Iterator
*****************************************************************/
	template<class T>
	class iterator_vector : public ft::iterator< ft::random_access_iterator_tag, T >
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef	T&	reference;
			typedef	T*	pointer;

			iterator_vector( ) : _ptr(NULL) { };
			iterator_vector( pointer src ) : _ptr(src) { };
			iterator_vector( const iterator_vector<T> & src ) { *this = src; };
			~iterator_vector() { };
			iterator_vector& operator=( const iterator_vector & rhs )
			{
				if (this != &rhs)
					this->_ptr = rhs._ptr;
				return *this;
			}

			reference	operator*() const { return *_ptr; };
			pointer		operator->() const { return _ptr; };
			reference	operator[]( difference_type rhs ) const { return (*(_ptr + rhs)); };


			friend bool	operator==( const iterator_vector & lhs, const iterator_vector & rhs )
			{ return (lhs._ptr == rhs._ptr); };
			friend bool	operator!=( const iterator_vector & lhs, const iterator_vector & rhs )
			{ return (lhs._ptr != rhs._ptr); };
			friend bool	operator<( const iterator_vector & lhs, const iterator_vector & rhs )
			{ return (lhs._ptr < rhs._ptr); };
			friend bool	operator<=( const iterator_vector & lhs, const iterator_vector & rhs )
			{ return (lhs._ptr <= rhs._ptr); };
			friend bool	operator>( const iterator_vector & lhs, const iterator_vector & rhs )
			{ return (lhs._ptr > rhs._ptr); };
			friend bool	operator>=( const iterator_vector & lhs, const iterator_vector & rhs )
			{ return (lhs._ptr >= rhs._ptr ); };

			iterator_vector&	operator++() { ++_ptr; return *this; };
			iterator_vector 	operator++(int) { iterator_vector tmp(*this); ++_ptr; return tmp; };
			iterator_vector&	operator--() { --_ptr; return *this; };
			iterator_vector		operator--(int) { iterator_vector tmp(*this); --_ptr; return tmp; };
			
			iterator_vector&	operator+=( difference_type rhs ) { _ptr += rhs; return *this; };
			iterator_vector&	operator-=( difference_type rhs ) { _ptr -= rhs; return *this; };

			iterator_vector	operator+(difference_type rhs) const { return iterator_vector(_ptr + rhs); };
			iterator_vector	operator-(difference_type rhs) const { return iterator_vector(_ptr - rhs); };
			friend iterator_vector operator+( difference_type diff, const iterator_vector& rhs ) 
			{ return rhs._ptr + diff; };
			friend difference_type operator-( const iterator_vector& lhs, const iterator_vector& rhs ) 
			{ return lhs._ptr - rhs._ptr; };

			pointer	_ptr;
	};


/****************************************************************
						 Const iterator
*****************************************************************/
	template<class T>
	class const_iterator_vector : public ft::iterator< ft::random_access_iterator_tag, T >
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef	const T&	reference;
			typedef	const T*	pointer;

			const_iterator_vector( ) : _ptr(NULL) { };
			const_iterator_vector( pointer src ) : _ptr(src) { };
			const_iterator_vector( const const_iterator_vector & src ) { *this = src; };
			const_iterator_vector( const iterator_vector<T> & src ) : _ptr(src._ptr) { };
			~const_iterator_vector() { };
			const_iterator_vector& operator=( const const_iterator_vector & rhs )
			{
				if (this != &rhs)
					_ptr = rhs._ptr;
				return *this;
			}

			reference	operator*() const { return *_ptr; };
			pointer		operator->() const { return _ptr; };
			reference	operator[]( difference_type rhs ) const { return (*(_ptr + rhs)); };

			friend bool	operator==( const const_iterator_vector & lhs, const const_iterator_vector & rhs )
			{ return (lhs._ptr == rhs._ptr); };
			friend bool	operator!=( const const_iterator_vector & lhs, const const_iterator_vector & rhs )
			{ return (lhs._ptr != rhs._ptr); };
			friend bool	operator<( const const_iterator_vector & lhs, const const_iterator_vector & rhs )
			{ return (lhs._ptr < rhs._ptr); };
			friend bool	operator<=( const const_iterator_vector & lhs, const const_iterator_vector & rhs )
			{ return (lhs._ptr <= rhs._ptr); };
			friend bool	operator>( const const_iterator_vector & lhs, const const_iterator_vector & rhs )
			{ return (lhs._ptr > rhs._ptr); };
			friend bool	operator>=( const const_iterator_vector & lhs, const const_iterator_vector & rhs )
			{ return (lhs._ptr >= rhs._ptr ); };

			const_iterator_vector&	operator++() { ++_ptr; return *this; };
			const_iterator_vector 	operator++(int) { const_iterator_vector tmp(*this); ++_ptr; return tmp; };
			const_iterator_vector&	operator--() { --_ptr; return *this; };
			const_iterator_vector	operator--(int) { const_iterator_vector tmp(*this); --_ptr; return tmp; };
			
			const_iterator_vector&	operator+=( difference_type rhs ) { _ptr += rhs; return *this; };
			const_iterator_vector&	operator-=( difference_type rhs ) { _ptr -= rhs; return *this; };

			const_iterator_vector	operator+(difference_type rhs) const { return const_iterator_vector(_ptr + rhs); };
			const_iterator_vector	operator-(difference_type rhs) const { return const_iterator_vector(_ptr - rhs); };
			friend const_iterator_vector operator+( difference_type diff, const const_iterator_vector& rhs ) 
			{ return rhs._ptr + diff; };
			friend difference_type operator-( const const_iterator_vector& lhs, const const_iterator_vector& rhs )
			{ return lhs._ptr - rhs._ptr; };

			pointer	_ptr;
	};

} //ft

#endif