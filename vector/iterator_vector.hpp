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
	template<typename T>
	class iterator_vector : public ft::iterator< ft::random_access_iterator_tag, T, std::ptrdiff_t, T*, T& >
	{
		public:
			iterator_vector( ) : _ptr(NULL) { };
			iterator_vector( pointer src ) : _ptr(src) { };
			iterator_vector( const iterator_vector & src ) { *this = src; };
			~iterator_vector() { };
			iterator_vector & operator=( const iterator_vector & rhs )
			{
				//A faire 
				//if !=, this->_ptr = rhs._ptr
				//return *this
			}
			
			bool		operator==( const iterator_vector & rhs ) const { return (_ptr == rhs._ptr); };
			bool		operator!=( const iterator_vector & rhs ) const { return (_ptr != rhs._ptr); };
			bool		operator<( const iterator_vector & rhs ) const { return (_ptr < rhs._ptr); };
			bool		operator<=( const iterator_vector & rhs ) const { return (_ptr <= rhs._ptr); };
			bool		operator>( const iterator_vector & rhs ) const { return (_ptr > rhs._ptr); };
			bool		operator>=( const iterator_vector & rhs ) const { return (_ptr >= rhs._ptr ); };

			iterator_vector&	operator++() { ++_ptr; return *this: };
			iterator_vector 	operator++(int) { iterator_vector tmp(*this); ++_ptr; return tmp; }; //_ptr++; return (iterator_vector(_ptr - 1);)
			iterator_vector&	operator--() { --_ptr; return *this; };
			iterator_vector		operator--(int) { iterator_vector tmp(*this); --_ptr; return tmp; }; //_ptr++; return (iterator_vector(_ptr + 1);)
			
			//iterator_vector&	operator+=( difference_type rhs ) { _ptr += rhs; return *this; };	//int ?
			//iterator_vector&	operator-=( difference_type rhs ) { _ptr -= rhs; return *this; };

			iterator_vector	operator+(difference_type rhs) const { return iterator_vector(_ptr + rhs); }; //rhs.getPtr()
			iterator_vector	operator-(difference_type rhs) const { return iterator_vector(_ptr - rhs); };
			difference_type	operator+(const iterator_vector& rhs ) const { return iterator_vector(_ptr + rhs._ptr); };
			difference_type	operator-(const iterator_vector& rhs ) const { return iterator_vector(_ptr - rhs._ptr); };
			
			reference	operator*() const { return *_ptr; };
			pointer		operator->() const { return _ptr; };
			reference	operator[]( difference_type rhs ) const { return _ptr[rhs]; };

			pointer		getPtr() const { return (this->_ptr); };
			
		private:
			pointer	_ptr;
	};

//+ meme chose avec const !

} //ft

#endif







//Bidirectional : map & set
	// ++, -- sauf si const. Avec *. ->, ==, !=
//Random-access iterator : vector
	// ++, +=, --, -= sauf si const. Avec * ou []. ->, ==, !=, <, <=, >, >=

//iterateur pesonnalise pour vector + iterateur personnalise pour map. Sont differents
