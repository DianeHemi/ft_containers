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

			iterator_map&	operator++() 
			{
				/*_node = successor(_node);
				return *this;*/

				if (_node->right != 0)	//Cas ou right == nil a gerer
				{
					_node = _node->right;
					while (_node->left != 0)	//Pareil ?
						_node = _node->left;
				}
				else
				{
					node_ptr y = _node->parent;
					while (_node && _node == y->right)
					{
						_node = y;
						y = y->parent;
					}
					if (_node->right != y)
						_node = y;
				}
				return *this;
			};
			iterator_map 	operator++(int) 
			{
				/*iterator_map tmp(*this);
				_node = successor(_node);
				return tmp;*/

				iterator_map tmp(*this);
				if (_node->right != 0)	//Cas ou right == nil a gerer
				{
					_node = _node->right;
					while (_node->left != 0)	//Pareil ?
						_node = _node->left;
				}
				else
				{
					node_ptr y = _node->parent;
					while (_node && _node == y->right)
					{
						_node = y;
						y = y->parent;
					}
					if (_node->right != y)
						_node = y;
				}
				return tmp;
			};
			iterator_map&	operator--() 
			{
				//Prevoir le cas ou on est sur NIL/end -> Renvoyer max a la place ?
				/*_node = predecessor(_node); 
				return *this;*/

				if (_node->left != 0)	//Cas ou right == nil a gerer
				{
					_node = _node->left;
					while (_node->right != 0)	//Pareil ?
						_node = _node->right;
				}
				else
				{
					node_ptr y = _node->parent;
					while (_node && _node == y->left)
					{
						_node = y;
						y = y->parent;
					}
					if (_node->left != y)
						_node = y;
				}
				return *this;
			};
			iterator_map	operator--(int)
			{
				/*iterator_map tmp(*this); 
				_node = predecessor(_node); 
				return tmp;*/

				iterator_map tmp(*this);
				if (_node->left != 0)	//Cas ou right == nil a gerer
				{
					_node = _node->left;
					while (_node->right != 0)	//Pareil ?
						_node = _node->right;
				}
				else
				{
					node_ptr y = _node->parent;
					while (_node && _node == y->left)
					{
						_node = y;
						y = y->parent;
					}
					if (_node->left != y)
						_node = y;
				}
				return tmp;
			};

			friend bool	operator==( const iterator_map & lhs, const iterator_map & rhs )
			{ return (lhs._node == rhs._node); };
			friend bool	operator!=( const iterator_map & lhs, const iterator_map & rhs )
			{ return (lhs._node != rhs._node); };


			node_ptr	_node;
	};




	/*template<class T>
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
			const_iterator_map( node_ptr src ) : _node(src) { };	//t_list* node -> t_list<T>
			const_iterator_map( const const_iterator_map & src ) { *this = src; };
			~const_iterator_map() { };
			const_iterator_map& operator=( const const_iterator_map & rhs )
			{
				if (this != &rhs)
					this->_node = rhs._node;
				return *this;
			}

			reference	operator*() const { return (_node->data); };
			pointer		operator->() const { return &(_node->data); };

			const_iterator_map&	operator++() { _node = successor(_node); return *this; };
			const_iterator_map 	operator++(int) { const_iterator_map tmp(*this); _node = successor(_node); return tmp; };
			const_iterator_map&	operator--() { _node = predecessor(_node); return *this; };
			const_iterator_map	operator--(int) { const_iterator_map tmp(*this); _node = predecessor(_node);; return tmp; };

			friend bool	operator==( const const_iterator_map & lhs, const const_iterator_map & rhs )
			{ return (lhs._node == rhs._node); };
			friend bool	operator!=( const const_iterator_map & lhs, const const_iterator_map & rhs )
			{ return (lhs._node != rhs._node); };


			node_ptr	_node;
	};*/
}

#endif