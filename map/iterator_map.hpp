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
			typedef rbt_node<T>		node;
			typedef rbt_node<T>*	node_ptr;

			iterator_map( ) : _node(NULL) { };
			iterator_map( node_ptr src ) : _node(src) { };
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

			iterator_map&	operator++() //Successor
			{
				if (_node->color != NIL)
					_node = successor(_node);
				return *this;
			};
			iterator_map 	operator++(int)
			{
				iterator_map tmp(*this);
				operator++();
				return tmp;
			};
			iterator_map&	operator--() //Predecessor
			{
				if (_node->color == NIL)
				{
					while (_node->parent)	//Looking for root
						_node = _node->parent;
					_node = max(_node);
				}
				else
					_node = predecessor(_node);
				return *this;
			};
			iterator_map	operator--(int)
			{
				iterator_map tmp(*this);
				operator--();
				return tmp;
			};

			friend bool	operator==( const iterator_map & lhs, const iterator_map & rhs )
			{ return (lhs._node == rhs._node); };
			friend bool	operator!=( const iterator_map & lhs, const iterator_map & rhs )
			{ return (lhs._node != rhs._node); };

			node_ptr	_node;

	};




	template<class T>
	class const_iterator_map : public ft::iterator< ft::bidirectional_iterator_tag, T >
	{
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef	const T&	reference;
			typedef	const T*	pointer;
			typedef rbt_node<T>		node;
			typedef rbt_node<T>*	node_ptr;


			const_iterator_map( ) : _node(NULL) { };
			const_iterator_map( node_ptr src ) : _node(src) { };
			const_iterator_map( const const_iterator_map & src ) { *this = src; };
			const_iterator_map( const iterator_map<T> & src ) : _node(src._node) { };
			~const_iterator_map() { };
			const_iterator_map& operator=( const const_iterator_map & rhs )
			{
				if (this != &rhs)
					this->_node = rhs._node;
				return *this;
			}

			reference	operator*() const { return (_node->data); };
			pointer		operator->() const { return &(_node->data); };

			const_iterator_map&	operator++() 
			{
				if (_node->color != NIL)
					_node = successor(_node);
				return *this;
			};
			const_iterator_map 	operator++(int) 
			{
				const_iterator_map tmp(*this);
				operator++();
				return tmp;
			};
			const_iterator_map&	operator--() 
			{
				if (_node->color == NIL)
				{
					while (_node->parent)	//Looking for root
						_node = _node->parent;
					_node = max(_node);
				}
				else
					_node = predecessor(_node);
				return *this;
			};
			const_iterator_map	operator--(int)
			{
				const_iterator_map tmp(*this);
				operator--();
				return tmp;
			};

			friend bool	operator==( const const_iterator_map & lhs, const const_iterator_map & rhs )
			{ return (lhs._node == rhs._node); };
			friend bool	operator!=( const const_iterator_map & lhs, const const_iterator_map & rhs )
			{ return (lhs._node != rhs._node); };


			node_ptr	_node;

	};


	template <class T>
	T min( T node )
	{
		while (node->left && node->left->color != NIL)
			node = node->left;
		return node;
	}

	template <class T>
	T max( T node )
	{
		while (node->right && node->right->color != NIL)
			node = node->right;
		return node;
	}

	template <class T>
	T successor( T node )
	{
		if (node->right && node->right->color != NIL)
		{
			return (min(node->right));
		}
		T y = node->parent;
		while (y != NULL && node == y->right)
		{
			node = y;
			y = y->parent;
		}
		if (y == NULL)
		{
			while (node->color != NIL)
				node = node->right;
			y = node;
		}						
		return y;
	}

	template <class T>
	T predecessor ( T node )
	{
		if (node->left && node->left->color != NIL)
		{
			return max(node->left);
		}
		T y = node->parent;
		while (y->color != NIL && node == y->left)
		{
			node = y;
			y = y->parent;
		}
		return y;
	}
}

#endif