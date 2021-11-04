#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

//https://githubmemory.com/repo/maxime-42/ft_containers
//https://www.fluentcpp.com/2018/05/08/std-iterator-deprecated/
//https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
//https://www.cplusplus.com/reference/iterator/iterator_traits/


namespace ft
{

	/*
		Iterator
	*/
	template<	//typename instead of class ?
		class Category,                     //Category of the iterator
		class T,                            //Type of valuesthat can be obtained by dereferencing the iterator
		class Distance = std::ptrdiff_t,    //A type that can be used to identify distance between iterators
		class Pointer = T*,                 //Defines a pointer to the type iterated over (T)
		class Reference = T&                //Defines a reference to the type iterated over (T)
	> struct iterator_vector
	{
		public:
			typedef Category	iterator_category;	//random_access_iterator_tag ?
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
		
		public:
			iterator() : _ptr(NULL) { };
			iterator( pointer rhs ) : _ptr(rhs) { };
			iterator( const iterator & rhs ) : _ptr(rhs._ptr) { };
			~iterator();
			
			bool		operator==( const iterator & rhs ) const { return (_ptr == rhs._ptr); };
			bool		operator!=( const iterator & rhs ) const { return (_ptr != rhs._ptr); };
			bool		operator<( const iterator & rhs ) const { return (_ptr < rhs._ptr); };
			bool		operator<=( const iterator & rhs ) const { return (_ptr <= rhs._ptr); };
			bool		operator>( const iterator & rhs ) const { return (_ptr > rhs._ptr); };
			bool		operator>=( const iterator & rhs ) const { return (_ptr >= rhs._ptr ); };

			iterator&	operator++() { ++_ptr; return *this: };
			iterator 	operator++(int) const { iterator tmp(*this); ++_ptr; return tmp; }; //Enlever le const ?
			iterator&	operator--() { --_ptr; return *this; };
			iterator	operator--(int) const { iterator tmp(*this); --_ptr; return tmp; };
			
			iterator&	operator+=( difference_type rhs ) { _ptr += rhs; return *this; };
			iterator&	operator-=( difference_type rhs ) { _ptr -= rhs; return *this; };

			iterator	operator+(difference_type rhs) const { return iterator(_ptr + rhs); };
			iterator	operator-(difference_type rhs) const { return iterator(_ptr - rhs); };
			difference_type	operator-(const iterator& rhs ) const { return iterator(_ptr - rhs._ptr); };
			
			//friend iterator operator+( difference_type lhs, const iterator & rhs ) { return iterator(lhs + rhs._ptr); };
			//friend iterator operator-( difference_type lhs, const iterator & rhs ) { return iterator(lhs - rhs._ptr); };

			reference	operator*() const { return *_ptr; };
			pointer		operator->() const { return _ptr; };
			reference	operator[]( difference_type rhs ) const { return _ptr[rhs]; };
			
			private:
				pointer	_ptr;
			
	};


} //ft

#endif







//Bidirectional : map & set
	// ++, -- sauf si const. Avec *. ->, ==, !=
//Random-access iterator : vector
	// ++, +=, --, -= sauf si const. Avec * ou []. ->, ==, !=, <, <=, >, >=

//iterateur pesonnalise pour vector + iterateur personnalise pour map. Sont differents
