#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cstddef>
# include <stdexcept>
# include <iostream>
# include "iterator_vector.hpp"
# include "../lexicographical_compare.hpp"
# include "../enable_if.hpp"

/*
	https://www.cplusplus.com/reference/vector/vector/?kw=vector

	https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf
	P 508 du pdf (482)
*/

namespace ft
{
	template <class T, class Allocator=std::allocator<T> >
	class vector {
		public:
		/****************************************************************
								 Definitions
		****************************************************************/
			typedef T 					value_type;
			typedef Allocator			allocator_type;
			typedef std::size_t			size_type;
			typedef std::ptrdiff_t		difference_type;

			typedef typename allocator_type::pointer 			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::reference			reference;
      		typedef typename allocator_type::const_reference	const_reference;

			typedef typename ft::iterator_vector<T>					iterator;
			typedef typename ft::const_iterator_vector<T>			const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;


		/****************************************************************
								 Constructors
		****************************************************************/
		explicit vector( const allocator_type& alloc = allocator_type() )
			: _size(0), _capacity(0), _alloc(alloc), _data(NULL) { };

		//Copy constructor
		vector( const vector & other ) : 
			_size(0), _capacity(0), _alloc(Allocator()), _data(NULL)
		{
			*this = other;
		}	

		// Fill constructor with count copies of T
		explicit vector( size_type count, const T& value = T(), const allocator_type& alloc = allocator_type() ) 
			: _size(0), _capacity(count), _alloc(alloc), _data(NULL)
		{
			_data = _alloc.allocate(count);
			for (size_type i = 0; i < count; i++)
				_alloc.construct(_data + i, value);
			_size = count;
		}

		//Range constructor 
		//enable_if = V??rifie si on a un it??rateur. Si ce n'est pas le cas on appelle pas ce constructeur
		template< class InputIt > 
		vector( InputIt first, 
			typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last, 
			const allocator_type& alloc = allocator_type() )
			: _size(0), _capacity(0), _alloc(alloc), _data(NULL)
		{
			/*difference_type dist = ft::it_distance(first, last);
    		this->_data = this->_alloc.allocate(dist);
			this->_capacity = dist;

			for (size_type i = 0; first != last; first++, i++) 
			{
				this->_alloc.construct(_data + i, *first);
				this->_size++;
			}*/
			assign(first, last);
		}

		//Overload operateur =
		vector& operator=( const vector& other )
		{
			if (this != &other)
			{
				assign(other.begin(), other.end());
				_size = other._size;
			}
			return (*this);
		};

		~vector()
		{
			clear();
			_alloc.deallocate(_data, _capacity);
			_capacity = 0;
		}

		template < class InputIt > 
		  void assign( InputIt first, 
		  typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type last )
		{
			erase(begin(), end());
			insert(begin(), first, last);
		};

		void assign( size_type n, const value_type& val )
		{
			erase(begin(), end());
			insert(begin(), n, val);
		};

		allocator_type	get_allocator() const { return _alloc; };


		/****************************************************************
								 Iterators
		****************************************************************/
		iterator				begin() { return iterator(_data); };
		const_iterator			begin() const { return const_iterator(_data); };
		iterator				end() { return iterator(_data + _size); };
		const_iterator			end() const { return const_iterator(_data + _size); };
		
		reverse_iterator		rbegin() { return reverse_iterator(_data + _size); };
		const_reverse_iterator	rbegin() const { return reverse_iterator(_data + _size); };
		reverse_iterator		rend() { return reverse_iterator(_data); };
		const_reverse_iterator	rend() const { return reverse_iterator(_data); };


		/****************************************************************
								 Element access
		****************************************************************/
		reference 		operator[]( size_type pos ) { return _data[pos]; };
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


		/****************************************************************
								 Capacity
		****************************************************************/
		bool			empty() const { return (_size == 0); };
		size_type		size() const { return _size; };
		size_type		max_size() const { return _alloc.max_size(); };
		size_type		capacity() const { return _capacity; };

		void		resize( size_type n, value_type val = value_type() )
		{
			if (n > _size)
				insert(end(), n - _size, val);
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
				throw std::length_error("vector::reserve");

			ft::vector<T> tmp;
			tmp._data = tmp._alloc.allocate(n);
			tmp._capacity = n;

			for(size_type i = 0; i < _size; i++)
				tmp._alloc.construct(tmp._data + i, _data[i]);
			tmp._size = _size;
			tmp.swap(*this);
		};

		/****************************************************************
								 Modifiers
		****************************************************************/
		void	push_back( const value_type& val )
		{
			if (_size == _capacity)
				reserve(_size == 0 ? 1 : _size * 2);
			_alloc.construct(_data + _size, val);
			_size++;
		};

		void	pop_back()
		{
			_alloc.destroy(_data + _size - 1);
			_size--;
		};

		iterator	insert( iterator pos, const value_type& val )
		{
			size_type	offset = pos - _data;

			if (_size == _capacity)
				reserve(_size == 0 ? 1 : _size * 2);

			for (size_type i = _size ; i > offset; i--)
			{
				_alloc.construct(_data + i, _data[i - 1]);
				_alloc.destroy(_data + i - 1);
			}
			_alloc.construct(_data + offset, val);
			_size++;
			return (begin() + offset);
		};

		void	insert( iterator pos, size_type n, const value_type& val )
		{
			size_type offset = pos - _data;

			for (size_type z = 0; (_size + n) > _capacity; z++)
			{
				if (_size <= 1)
					reserve(_size + n);
				else
					reserve((_size + z) * 2);
			}

			if (n > 0) 
			{
				for (size_type i = _size + n - 1; i >= offset + n; i--) 
				{
					_alloc.construct(_data + i, _data[i - n]);
					_alloc.destroy(_data + (i - n));
				}
			}
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_data + offset + i, val);
			_size += n;
		};

		template< class InputIt >
		 void insert( iterator pos, InputIt first, 
		 typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type last )
		{
			size_type n = 0;
			for (InputIt it = first; it != last; it++)
				n++;

			size_type offset = pos - _data;
			if ((_size + n) > _capacity)
				reserve(_size + n);

			if (n > 0) 
			{
				for (size_type i = _size + n - 1; i >= offset + n; i--) 
				{
					_alloc.construct(_data + i, _data[i - n]);
					_alloc.destroy(_data + (i - n));
				}
			}
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_data + offset + i, *first++);
			_size += n;
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

			return (erase(pos, pos + 1));
		};

		iterator	erase( iterator first, iterator last )
		{
			size_type offset = last - first;
			size_type i = (first - begin()) + offset;
			iterator tmp = first;

			for( ; tmp != last; tmp++)
				_alloc.destroy(&(*tmp));

			for( ; i < _size; i++)
			{
				_alloc.construct(_data + (i - offset), _data[i]);
				_alloc.destroy(_data + i);
			}
			_size -= offset;
			return first;
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


		/****************************************************************
								Private members
		****************************************************************/
		private:
			size_type	_size;		//size filled
			size_type	_capacity;	//size allocated
			Allocator	_alloc;		//allocator
			pointer		_data;		//content
	};


/****************************************************************
					 Non-member functions
****************************************************************/
	
	template <class T, class Allocator>
	bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Allocator>
  	bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
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

} //ft

#endif
