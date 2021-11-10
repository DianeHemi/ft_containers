#ifndef ITERATOR_VECTOR_HPP
# define ITERATOR_VECTOR_HPP

# include <cstddef>
# include "../iterator_traits.hpp"

//https://githubmemory.com/repo/maxime-42/ft_containers
//https://www.fluentcpp.com/2018/05/08/std-iterator-deprecated/
//https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
//https://www.cplusplus.com/reference/iterator/iterator_traits/


namespace ft
{
	/*
		Iterator
	*/
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
			iterator_vector( const iterator_vector & src ) { *this = src; };
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
			
			bool		operator==( const iterator_vector & rhs ) const { return (_ptr == rhs._ptr); };
			bool		operator!=( const iterator_vector & rhs ) const { return (_ptr != rhs._ptr); };
			bool		operator<( const iterator_vector & rhs ) const { return (_ptr < rhs._ptr); };
			bool		operator<=( const iterator_vector & rhs ) const { return (_ptr <= rhs._ptr); };
			bool		operator>( const iterator_vector & rhs ) const { return (_ptr > rhs._ptr); };
			bool		operator>=( const iterator_vector & rhs ) const { return (_ptr >= rhs._ptr ); };

			iterator_vector&	operator++() { ++_ptr; return *this; };
			iterator_vector 	operator++(int) { iterator_vector tmp(*this); ++_ptr; return tmp; };
			iterator_vector&	operator--() { --_ptr; return *this; };
			iterator_vector		operator--(int) { iterator_vector tmp(*this); --_ptr; return tmp; };
			
			iterator_vector&	operator+=( difference_type rhs ) { _ptr += rhs; return *this; };
			iterator_vector&	operator-=( difference_type rhs ) { _ptr -= rhs; return *this; };

			iterator_vector	operator+(difference_type rhs) const { return iterator_vector(_ptr + rhs); };
			iterator_vector	operator-(difference_type rhs) const { return iterator_vector(_ptr - rhs); };
			difference_type	operator+(const iterator_vector& rhs ) const { return (_ptr + rhs._ptr); };
			difference_type	operator-(const iterator_vector& rhs ) const { return (_ptr - rhs._ptr); };
			
		private:
			pointer	_ptr;
	};
	

	/*
		Const iterator
	*/
	template<class T>
	class const_iterator_vector : public ft::iterator< ft::random_access_iterator_tag, T >
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef	T&	reference;
			typedef	T*	pointer;

			const_iterator_vector( ) : _ptr(NULL) { };
			const_iterator_vector( pointer src ) : _ptr(src) { };
			const_iterator_vector( const const_iterator_vector & src ) { *this = src; };
			~const_iterator_vector() { };
			const_iterator_vector& operator=( const const_iterator_vector & rhs )
			{
				if (this != &rhs)
					this->_ptr = rhs._ptr;
				return *this;
			}

			reference	operator*() const { return *_ptr; };
			pointer		operator->() const { return _ptr; };
			reference	operator[]( difference_type rhs ) const { return (*(_ptr + rhs)); };
			
			bool		operator==( const const_iterator_vector & rhs ) const { return (_ptr == rhs._ptr); };
			bool		operator!=( const const_iterator_vector & rhs ) const { return (_ptr != rhs._ptr); };
			bool		operator<( const const_iterator_vector & rhs ) const { return (_ptr < rhs._ptr); };
			bool		operator<=( const const_iterator_vector & rhs ) const { return (_ptr <= rhs._ptr); };
			bool		operator>( const const_iterator_vector & rhs ) const { return (_ptr > rhs._ptr); };
			bool		operator>=( const const_iterator_vector & rhs ) const { return (_ptr >= rhs._ptr ); };

			const_iterator_vector&	operator++() { ++_ptr; return *this; };
			const_iterator_vector 	operator++(int) { const_iterator_vector tmp(*this); ++_ptr; return tmp; };
			const_iterator_vector&	operator--() { --_ptr; return *this; };
			const_iterator_vector		operator--(int) { const_iterator_vector tmp(*this); --_ptr; return tmp; };
			
			const_iterator_vector&	operator+=( difference_type rhs ) { _ptr += rhs; return *this; };
			const_iterator_vector&	operator-=( difference_type rhs ) { _ptr -= rhs; return *this; };

			const_iterator_vector	operator+(difference_type rhs) const { return const_iterator_vector(_ptr + rhs); };
			const_iterator_vector	operator-(difference_type rhs) const { return const_iterator_vector(_ptr - rhs); };
			difference_type	operator+(const const_iterator_vector& rhs ) const { return (_ptr + rhs._ptr); };
			difference_type	operator-(const const_iterator_vector& rhs ) const { return (_ptr - rhs._ptr); };
			
		private:
			pointer	_ptr;
	};


	/*
		Reverse iterator
	*/
	template<class T>
	class reverse_iterator : public ft::iterator< ft::random_access_iterator_tag, T >
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef	T&	reference;
			typedef	T*	pointer;

			reverse_iterator( ) : _ptr(NULL) { };
			reverse_iterator( pointer src ) : _ptr(src) { };
			reverse_iterator( const reverse_iterator & src ) { *this = src; };
			~reverse_iterator() { };
			reverse_iterator& operator=( const reverse_iterator & rhs )
			{
				if (this != &rhs)
					this->_ptr = rhs._ptr;
				return *this;
			}

			reference	operator*() const { return *_ptr; };
			pointer		operator->() const { return _ptr; };
			reference	operator[]( difference_type rhs ) const { return (*(_ptr + rhs)); }; //Faire - a la place ?
			
			bool		operator==( const reverse_iterator & rhs ) const { return (_ptr == rhs._ptr); };
			bool		operator!=( const reverse_iterator & rhs ) const { return (_ptr != rhs._ptr); };
			bool		operator<( const reverse_iterator & rhs ) const { return (_ptr < rhs._ptr); };
			bool		operator<=( const reverse_iterator & rhs ) const { return (_ptr <= rhs._ptr); };
			bool		operator>( const reverse_iterator & rhs ) const { return (_ptr > rhs._ptr); };
			bool		operator>=( const reverse_iterator & rhs ) const { return (_ptr >= rhs._ptr ); };

			reverse_iterator&	operator++() { --_ptr; return *this; };
			reverse_iterator 	operator++(int) { reverse_iterator tmp(*this); --_ptr; return tmp; };
			reverse_iterator&	operator--() { ++_ptr; return *this; };
			reverse_iterator	operator--(int) { reverse_iterator tmp(*this); ++_ptr; return tmp; };
			
			reverse_iterator&	operator+=( difference_type rhs ) { _ptr -= rhs; return *this; };
			reverse_iterator&	operator-=( difference_type rhs ) { _ptr += rhs; return *this; };

			reverse_iterator	operator+(difference_type rhs) const { return reverse_iterator(_ptr - rhs); };
			reverse_iterator	operator-(difference_type rhs) const { return reverse_iterator(_ptr + rhs); };
			difference_type	operator+(const reverse_iterator& rhs ) const { return (_ptr - rhs._ptr); };
			difference_type	operator-(const reverse_iterator& rhs ) const { return (_ptr + rhs._ptr); };
			
		private:
			pointer	_ptr;
	};







	/*
		Const reverse iterator
	*/

} //ft

#endif







//Bidirectional : map & set
	// ++, -- sauf si const. Avec *. ->, ==, !=
//Random-access iterator : vector
	// ++, +=, --, -= sauf si const. Avec * ou []. ->, ==, !=, <, <=, >, >=

//iterateur pesonnalise pour vector + iterateur personnalise pour map. Sont differents
