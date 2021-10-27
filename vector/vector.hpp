#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cstddef>

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

			typedef typename std::allocator_traits<Allocator>::pointer 			pointer;	//Iterators behaves the same way
			typedef typename std::allocator_traits<Allocator>::const_pointer	const_pointer;

			typedef value_type&			reference;
			typedef const value_type&	const_reference;

			typedef size_t				size_type;
			typedef std::ptrdiff_t		difference_type;

			//typedef typename ft::iterator								iterator
			//typedef typename ft::const_iterator						const_iterator
			//typedef typename ft::reverse_iterator<ft::iterator>		reverse_iterator
			//typedef typename ft::reverse_iterator<ft::const_iterator>	const_reverse_iterator


		/*
			Constructors
		*/
		vector() {};
		//vector( const Allocator& alloc );
		//vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator() );
		//template< class InputIt > vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
		//vector& operator=( const vector& src );
		~vector() {};


		//template < class InputIt > 
			//void assign( InputIt first, InputIt last );
		//void assign( size_t count, const T& value );
		//allocator_type get_allocator() const;


		/*
			Iterators
		*/
		//iterator					begin();
		//const_iterator			begin() const;
		//iterator					end();
		//const_iterator			end() cont;
		//reverse_iterator			rbegin();
		//const_reverse_iterator	rbegin() const;
		//reverse_iterator			rend();
		//const_reverse_iterator	rend() const;

		/*
			Element access
		*/
		//reference 		operator[]( size_t pos );
		//const_reference	operator[]( size_t pos ) const;
		//reference			at( size_type pos );
		//const_reference	at( size_type pos ) const;
		//reference			front();
		//const_reference	front() const;
		//reference			back();
		//const_reference	back() const;

		/*
			Capacity
		*/
		//bool		empty() const;
		//size_type	size() const;
		//size_type	max_size() const;
		//size_type	capacity() const;
		//void		resize( size_type count );
		//void		resize( size_type count, T value = T() );
		//void		reserve( size_type n );

		/*
			Modifiers
		*/

		//void		push_back( const T& value )
		/*{
			if (_size == _capacity)
				//Reallocate to allow larger capacity
			if (_size < _capacity)
				//Add element at the end
				//Copy new element at end of array ->insert
				//_size++
		}*/

		//void		pop_back();
		//iterator	insert( iterator pos, const T& value );
		//iterator	insert( iterator pos, size_type count, const T& value );
		//template< class InputIt >
			//void insert( iterator pos, InputIt first, InputIt last );
		//void		clear();
		//iterator	erase( iterator pos );
		//iterator	erase( iterator first, iterator last );
		//void		swap( vector& other );


		/*
			Overload operators
		*/





		private:
			unsigned long	_size;
			unsigned long	_capacity;

	};

	//template<class T, class Allocator>
	//	void swap(vector<T, Allocator>& x, vector<T, Allocator>& y) (x.swap(y));

}	//ft

#endif
