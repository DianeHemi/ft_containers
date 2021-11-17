#ifndef ITERATOR_MAP_HPP
# define ITERATOR_MAP_HPP

# include "../iterator_traits.hpp"

# include "RBTree.hpp"

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
			typedef RBTree<T>	brt;

			iterator_map( ) : _node(NULL) { };
			iterator_map( brt* src ) : _node(src) { };	//t_list* node -> t_list<T>
			iterator_map( const iterator_map & src ) { *this = src; };
			~iterator_map() { };
			iterator_map& operator=( const iterator_map & rhs )
			{
				if (this != &rhs)
					this->_node = rhs._node;
				return *this;
			}

			/*
				* Fonctions
			*/
			reference	operator*() const { return (_node->data); };
			pointer		operator->() const { return &(_node->data); };

			iterator_map&	operator++() { _node = _node->successor(); return *this; };
			iterator_map 	operator++(int) { iterator_map tmp(*this); _node = _node->successor(); return tmp; };
			iterator_map&	operator--() { _node = _node->predecessor(); return *this; };
			iterator_map	operator--(int) { iterator_map tmp(*this); _node = _node->predecessor();; return tmp; };

			friend bool	operator==( const iterator_map & lhs, const iterator_map & rhs )
			{ return (lhs._node == rhs._node); };
			friend bool	operator!=( const iterator_map & lhs, const iterator_map & rhs )
			{ return (lhs._node != rhs._node); };

			brt*	_node;
	};
}

#endif