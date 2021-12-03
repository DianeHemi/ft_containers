#ifndef ITERATOR_SET_HPP
# define ITERATOR_SET_HPP

# include "../iterator_traits.hpp"
# include "RBTree.hpp"

namespace ft
{
/****************************************************************
							Iterator
*****************************************************************/
	template<class T>
	class iterator_set : public ft::iterator< ft::bidirectional_iterator_tag, T >
	{
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef	T&	reference;
			typedef	T*	pointer;
			typedef rbt_node<T>		node;
			typedef rbt_node<T>*	node_ptr;

			iterator_set( ) : _node(NULL) { };
			iterator_set( node_ptr src ) : _node(src) { };
			iterator_set( const iterator_set & src ) { *this = src; };
			~iterator_set() { };
			iterator_set& operator=( const iterator_set & rhs )
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

			iterator_set&	operator++() //Successor
			{
				if (_node->color != NIL)
					_node = successor(_node);
				return *this;
			};
			iterator_set 	operator++(int)
			{
				iterator_set tmp(*this);
				operator++();
				return tmp;
			};
			iterator_set&	operator--() //Predecessor
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
			iterator_set	operator--(int)
			{
				iterator_set tmp(*this);
				operator--();
				return tmp;
			};

			friend bool	operator==( const iterator_set & lhs, const iterator_set & rhs )
			{ return (lhs._node == rhs._node); };
			friend bool	operator!=( const iterator_set & lhs, const iterator_set & rhs )
			{ return (lhs._node != rhs._node); };

			node_ptr	_node;
	};


/****************************************************************
						 Const iterator
*****************************************************************/
	template<class T>
	class const_iterator_set : public ft::iterator< ft::bidirectional_iterator_tag, T >
	{
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef	const T&	reference;
			typedef	const T*	pointer;
			typedef rbt_node<T>		node;
			typedef rbt_node<T>*	node_ptr;


			const_iterator_set( ) : _node(NULL) { };
			const_iterator_set( node_ptr src ) : _node(src) { };
			const_iterator_set( const const_iterator_set & src ) { *this = src; };
			const_iterator_set( const iterator_set<T> & src ) : _node(src._node) { };
			~const_iterator_set() { };
			const_iterator_set& operator=( const const_iterator_set & rhs )
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

			const_iterator_set&	operator++() 
			{
				if (_node->color != NIL)
					_node = successor(_node);
				return *this;
			};
			const_iterator_set 	operator++(int) 
			{
				const_iterator_set tmp(*this);
				operator++();
				return tmp;
			};
			const_iterator_set&	operator--() 
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
			const_iterator_set	operator--(int)
			{
				const_iterator_set tmp(*this);
				operator--();
				return tmp;
			};

			friend bool	operator==( const const_iterator_set & lhs, const const_iterator_set & rhs )
			{ return (lhs._node == rhs._node); };
			friend bool	operator!=( const const_iterator_set & lhs, const const_iterator_set & rhs )
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