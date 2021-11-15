#ifndef ITERATOR_MAP_HPP
# define ITERATOR_MAP_HPP

# include "../iterator_traits.hpp"

namespace ft
{
	template<class T>
	class iterator_map : public ft::iterator< ft::bidirectional_iterator_tag, T >
	{
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef	T&	reference;
			typedef	T*	pointer;

			iterator_map( ) : _ptr(NULL) { };
			iterator_map( pointer src ) : _ptr(src) { };
			iterator_map( const iterator_map & src ) { *this = src; };
			~iterator_map() { };
			iterator_map& operator=( const iterator_map & rhs )
			{
				if (this != &rhs)
					this->_ptr = rhs._ptr;
				return *this;
			}

			/*
				* Fonctions
			*/

			//A implementer : | '==' | '!=' | '*' | '->' | '++' | '--' | 

			reference	operator*() const { return *_ptr; };
			pointer		operator->() const { return _ptr; };

			iterator_map&	operator++() { ++_ptr; return *this; };
			iterator_map 	operator++(int) { iterator_map tmp(*this); ++_ptr; return tmp; };
			iterator_map&	operator--() { --_ptr; return *this; };
			iterator_map	operator--(int) { iterator_map tmp(*this); --_ptr; return tmp; };

			friend bool	operator==( const iterator_map & lhs, const iterator_map & rhs )
			{ return (lhs._ptr == rhs._ptr); };
			friend bool	operator!=( const iterator_map & lhs, const iterator_map & rhs )
			{ return (lhs._ptr != rhs._ptr); };


			pointer	_ptr;
	};
}

#endif