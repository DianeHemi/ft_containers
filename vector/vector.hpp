#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cstddef>
# include <stdexcept>
# include <limits>
# include <iostream>
# include "iterator_vector.hpp"
# include "../lexicographical_compare.hpp"
# include "../enable_if.hpp"

namespace ft
{
	template <class T, class Allocator=std::allocator<T>>
	class vector {
		public:
		/*
			Member type
		*/
			typedef T 					value_type;
			typedef Allocator			allocator_type;
			typedef size_t				size_type;
			typedef std::ptrdiff_t		difference_type;

			typedef typename allocator_type::pointer 			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::reference			reference;
      		typedef typename allocator_type::const_reference	const_reference;

			typedef typename ft::iterator_vector<T>			iterator;
			typedef typename ft::const_iterator_vector<T>	const_iterator;
			typedef typename ft::reverse_iterator<T>		reverse_iterator;
			//typedef typename ft::reverse_iterator<ft::const_iterator>	const_reverse_iterator

		/****
			Constructors
		****/
		explicit vector( const Allocator& alloc = Allocator() )
			: _size(0), _capacity(0), _alloc(alloc), _data(0) { };

		//Copy constructor
		vector( const vector & src ) : 
			_size(0), _capacity(0), _alloc(Allocator()), _data(0)
		{
			*this = src;
		}	

		// Fill constructor with count copies of T
		explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator() ) 
			: _size(0), _capacity(0), _alloc(alloc), _data(0)
		{
			reserve(count);
			for (size_type i = 0; i < count; i++)
				_alloc.construct(_data + i, value);
			_size = count;
		}

		//Range constructor - enable_if = Vérifie si on a un itérateur. Si ce n'est pas le cas on appelle pas ce constructeur
		template< class InputIt > 
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(),
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = NULL ) //type* ?
			: _size(0), _capacity(0), _alloc(alloc), _data(0)
		{
			for (iterator iter = first; iter != last; iter++)
				push_back(*iter);
		}

		//Overload de l'operateur =
		vector& operator=( const vector& src )
		{
			clear();
			if (this != &src)
			{
				insert(begin(), src.begin(), src.end());
				_size = src._size;
				_capacity = src._capacity;
			}
			return (*this);
		};

		virtual ~vector()
		{
			_alloc.destroy(_data); //ou clear ?
			_alloc.deallocate(_data, _capacity);
		}


		template < class InputIt > 
		  void assign( InputIt first, InputIt last, 
		  typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type = NULL)
		{
			erase(begin(), end());
			insert(begin(), first, last);
		};
		void assign( size_t count, const T& value )
		{
			erase(begin(), end());
			insert(begin(), count, value);
		};
		allocator_type get_allocator() const { return _alloc; };


		/****
			Iterators
		****/
		iterator					begin() { return iterator(_data); };
		const_iterator				begin() const { return const_iterator(_data); };
		iterator					end() { return iterator(_data + _size); };
		const_iterator				end() const { return const_iterator(_data + _size); };
		
		reverse_iterator			rbegin() { return reverse_iterator(_data + _size); };
		//const_reverse_iterator	rbegin() const;
		reverse_iterator			rend() { return reverse_iterator(_data - 1); };
		//const_reverse_iterator	rend() const;


		/*********************
			Element access
		*********************/
		reference 		operator[]( size_type pos ) { return _data[pos]; }; // ++ check invalid index ?
		const_reference	operator[]( size_type pos ) const { return _data[pos]; };
		reference		front() { return _data[0]; };
		const_reference	front() const { return _data[0]; };
		reference		back() { return _data[_size - 1]; };
		const_reference	back() const { return _data[_size - 1]; };
		reference		at( size_type pos ) 
		{
			if (!(pos < size()))
				throw std::out_of_range("vector::_M_range_check");
			return _data[pos];
		};
		const_reference	at( size_type pos ) const
		{
			if (!(pos < size()))
				throw std::out_of_range("vector::_M_range_check");
			return _data[pos];
		};


		/***************
			Capacity
		***************/
		bool		empty() const { return (_size == 0); };
		size_type	size() const { return _size; };
		size_type	max_size() const { return (std::numeric_limits<difference_type>::max()); };
		size_type	capacity() const { return _capacity; };
		void		resize( size_type n, value_type val = value_type() )
		{
			if (n > _size)
				insert(end(), n - size(), val);
			else if (n < _size)
				erase(begin() + n, end());
			else
				return ;
		};
		void		reserve( size_type n )
		{
			if (_capacity >= n)
				return ;
			if (n > max_size()) 
				throw std::length_error("vector::_M_fill_insert");

			ft::vector<T> tmp;
			tmp._data = tmp._alloc.allocate(n);
			tmp._capacity = n;

			for(size_type i = 0; i < _size; i++)
				tmp._alloc.construct(tmp._data + i, _data[i]);
			tmp._size = _size;
			tmp.swap(*this); //No need to destroy. tmp destructor called on return
		};

		/****
			Modifiers
		****/
		void		push_back( const value_type& val )
		{
			if (_size == _capacity)
				reserve(_size == 0 ? 1 : _capacity * 2);
			_data[_size] = val;
			_size++;
		}
		void		pop_back()
		{
			iterator ite = end();
			_alloc.destroy(&ite);
			_size--;
		};
		iterator	insert( iterator pos, const T& value )
		{
			size_type	offset = pos - _data;

			if (_size == _capacity)
				reserve(_size == 0 ? 1 : _capacity * 2);

			for (size_type i = _size ; i > offset; i--)
			{
				_alloc.construct(_data + i, _data[i - 1]);
				_alloc.destroy(_data + i - 1);
			}
			_data[offset] = value;
			_size++;
			return (begin() + offset);
		};
		void	insert( iterator pos, size_type count, const T& value )
		{
			/*size_type offset = (pos - _data);

			if (_size == 0)
				reserve(1);
			while ((_size + count) >= _capacity)
				reserve(_capacity * 2);

			size_type src = _size;
			size_type dest = src + count;

			for( ; src > offset; dest--, src--) 
			{
				_alloc.construct(_data + dest, _data[src]);
				_alloc.destroy(_data + src);
			}
			_alloc.construct(_data + dest, _data[src]);
			for(size_type i = 0; i < count; i++, src++)
				_data[src] = value;
			_size += count;*/

			ft::vector<T> tmp;
			tmp._data = tmp._alloc.allocate(_capacity);
			tmp._capacity = _capacity;

			iterator it = begin();
			for ( ; it != pos; it++)
				tmp.push_back(*it);
			for( ; count > 0; count--)
				tmp.push_back(value);
			for ( ; it != end(); it++)
				tmp.push_back(*it);
			tmp.swap(*this);
			
		};
		template< class InputIt >
		 void insert( iterator pos, InputIt first, InputIt last, 
		 typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type = NULL )
		{
			ft::vector<T> tmp;
			tmp._data = tmp._alloc.allocate(_capacity);
			tmp._capacity = _capacity;

			iterator it = begin();
			for( ; it != pos; it++)
				tmp.push_back(*it);
			for(size_type i = 0 ; first != last; first++, i++)
				tmp.push_back(*first);
			for (; it != end(); it++)
				tmp.push_back(*it);
			tmp.swap(*this);
		};
		void		clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_data[i]);
			_size = 0;
		};
		iterator	erase( iterator pos )
		{
			if (pos == end())
				return end();

			for (++pos; pos != end(); ++pos)
			{
				pos[-1] = *pos;
				_alloc.destroy(&pos);
			}	
			_size--;
			return pos;
		};
		iterator	erase( iterator first, iterator last )
		{
			iterator storage_it = first;
			iterator return_it = last;
			iterator diff_it = last;

			for ( ; last != end(); ++last, ++storage_it)
				*storage_it = *last;

			while (first != diff_it)
			{
				_alloc.destroy(&first);
				*first++;
				_size--;
			}
			return return_it;
		};
		void		swap( vector& other )
		{
			pointer tmp_data = _data;
			size_type tmp_size = _size;
			size_type tmp_capacity = _capacity;
			Allocator tmp_alloc = _alloc;

			_data = other._data;
			_capacity = other._capacity;
			_size = other._size;
			_alloc = other._alloc;

			other._data = tmp_data;
			other._size = tmp_size;
			other._capacity = tmp_capacity;
			other._alloc = tmp_alloc;
		};

		private:
			size_type	_size;		//size filled
			size_type	_capacity;	//size allocated
			Allocator	_alloc;		//allocator
			pointer		_data;		//content
	};
	
	template <class T, class Allocator>
	bool operator==(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Allocator>
  	bool operator!=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		if (lhs.size() != rhs.size())
			return true;
		return !(ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Allocator>
	bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Allocator>
	bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Allocator>
	bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Allocator>
	bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return !(lhs < rhs);
	}

	template<class T, class Allocator>
	void swap(vector<T, Allocator>& x, vector<T, Allocator>& y) { x.swap(y); }

}

#endif
