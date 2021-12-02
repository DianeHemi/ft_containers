#ifndef BIDIRECTIONNAL_ITERATOR_HPP
# define BIDIRECTIONNAL_ITERATOR_HPP

# include "../iterator_traits.hpp"
# include "RBTree.hpp"

namespace ft
{
/****************************************************************
							Iterator
*****************************************************************/
	template<class T>
	class bidirectionnal_iterator : public ft::iterator< ft::bidirectional_iterator_tag, T >
	{
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef	T&	reference;
			typedef	T*	pointer;
			typedef rbt_node<T>		node;
			typedef rbt_node<T>*	node_ptr;

			bidirectionnal_iterator( ) : _node(NULL) { };
			bidirectionnal_iterator( node_ptr src ) : _node(src) { };
			bidirectionnal_iterator( const bidirectionnal_iterator & src ) { *this = src; };
			~bidirectionnal_iterator() { };
			bidirectionnal_iterator& operator=( const bidirectionnal_iterator & rhs )
			{
				if (this != &rhs)
					this->_node = rhs._node;
				return *this;
			}

			/****************************************************************
										Functions
			*****************************************************************/
			reference	operator*() const { return (_node->data); };
			pointer		operator->() const { return &(_node->data); };

			bidirectionnal_iterator&	operator++() //Successor
			{
				if (_node->color != NIL)
					_node = successor(_node);
				return *this;
			};
			bidirectionnal_iterator 	operator++(int)
			{
				bidirectionnal_iterator tmp(*this);
				operator++();
				return tmp;
			};
			bidirectionnal_iterator&	operator--() //Predecessor
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
			bidirectionnal_iterator	operator--(int)
			{
				bidirectionnal_iterator tmp(*this);
				operator--();
				return tmp;
			};

			friend bool	operator==( const bidirectionnal_iterator & lhs, const bidirectionnal_iterator & rhs )
			{ return (lhs._node == rhs._node); };
			friend bool	operator!=( const bidirectionnal_iterator & lhs, const bidirectionnal_iterator & rhs )
			{ return (lhs._node != rhs._node); };

			node_ptr	_node;
	};


/****************************************************************
						 Const iterator
*****************************************************************/
	template<class T>
	class const_bidirectionnal_iterator : public ft::iterator< ft::bidirectional_iterator_tag, T >
	{
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef	const T&	reference;
			typedef	const T*	pointer;
			typedef rbt_node<T>		node;
			typedef rbt_node<T>*	node_ptr;


			const_bidirectionnal_iterator( ) : _node(NULL) { };
			const_bidirectionnal_iterator( node_ptr src ) : _node(src) { };
			const_bidirectionnal_iterator( const const_bidirectionnal_iterator & src ) { *this = src; };
			const_bidirectionnal_iterator( const bidirectionnal_iterator<T> & src ) : _node(src._node) { };
			~const_bidirectionnal_iterator() { };
			const_bidirectionnal_iterator& operator=( const const_bidirectionnal_iterator & rhs )
			{
				if (this != &rhs)
					this->_node = rhs._node;
				return *this;
			}


			/****************************************************************
										Functions
			*****************************************************************/
			reference	operator*() const { return (_node->data); };
			pointer		operator->() const { return &(_node->data); };

			const_bidirectionnal_iterator&	operator++() 
			{
				if (_node->color != NIL)
					_node = successor(_node);
				return *this;
			};
			const_bidirectionnal_iterator 	operator++(int) 
			{
				const_bidirectionnal_iterator tmp(*this);
				operator++();
				return tmp;
			};
			const_bidirectionnal_iterator&	operator--() 
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
			const_bidirectionnal_iterator	operator--(int)
			{
				const_bidirectionnal_iterator tmp(*this);
				operator--();
				return tmp;
			};

			friend bool	operator==( const const_bidirectionnal_iterator & lhs, const const_bidirectionnal_iterator & rhs )
			{ return (lhs._node == rhs._node); };
			friend bool	operator!=( const const_bidirectionnal_iterator & lhs, const const_bidirectionnal_iterator & rhs )
			{ return (lhs._node != rhs._node); };

			node_ptr	_node;
	};


/****************************************************************
							Helpers
*****************************************************************/
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

} //ft

#endif