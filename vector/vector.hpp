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
			typedef size_t				size_type;
			typedef std::ptrdiff_t		difference_type;

			typedef typename Allocator::pointer 			pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef typename Allocator::reference          reference;
      		typedef typename Allocator::const_reference    const_reference;

			typedef typename ft::iterator_vector						iterator
			typedef typename ft::const_iterator_vector					const_iterator
			//typedef typename ft::reverse_iterator<ft::iterator>		reverse_iterator
			//typedef typename ft::reverse_iterator<ft::const_iterator>	const_reverse_iterator


		/*
			Constructors
		*/
		vector( )
			: _size(0), _capacity(0), _alloc(Allocator()), _data(0) { };
		vector( const Allocator& alloc = Allocator() )
			: _size(0), _capacity(0), _alloc(alloc), _data(0) { };

		/* Copy constructor //explicit ?
		vector( vector & src ) : 
			_size(0), _capacity(0), _alloc(Allocator()), _data(0)
		{ *this = src; }
		*/

		/* Fill constructor with count copies of T
		vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator() ) 
			: _size(0), _capacity(count), _alloc(alloc), _data(0)
		{
			//Ou reserve memoire ?
			 _vector = _alloc.allocate(count);  //Allouer avec .allocate(nb)
        	for(size_type size = 0; size < count; size++){ //Construire pour chaque élément
          		_alloc.construct(_vector + size, value) //_size++ au lieu de _size = count ?
			_size = count;
        }*/

		/* Range constructor - enable_if = Vérifie si on a un itérateur. Si ce n'est pas le cas on appelle pas ce constructeur
		template< class InputIt > 
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator()
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = NULL ) //type* ?
			: _size(0), _capacity(0), _alloc(alloc), _data(0)
		{
			for (iterator iter = first; iter != last; iter++)
			{
				_data.push_back(*iter);
			}
			//Ou juste while first != last ?
			//ou refaire allocate + construct ?
		}
		*/

		//vector& operator=( const vector& src ) { A faire };

		virtual ~vector()
		{
			/*
			_alloc.destroy() ou clear ?
			_alloc.deallocate() si != 0
			*/
		}


		//template < class InputIt > 
			//void assign( InputIt first, InputIt last );
		//void assign( size_t count, const T& value );
		//Allocator get_allocator() const;


		/*
			Iterators
		*/
		iterator					begin() { return iterator(_data); };
		const_iterator				begin() const { return const_iterator(_data); };
		iterator					end() { return iterator(_data + _size); };
		const_iterator				end() const { return const_iterator(_ptr + _size); };
		
		//reverse_iterator			rbegin();
		//const_reverse_iterator	rbegin() const;
		//reverse_iterator			rend();
		//const_reverse_iterator	rend() const;

		/*
			Element access
		*/
		//reference 		operator[]( size_t pos );
			//return this->start() + pos;
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
			size_type	_size;		//size filled
			size_type	_capacity;	//size allocated
			Allocator	_alloc;
			T*			_data;

	};



	/*	template <class T, class Alloc>
		bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{

		}

		Faire tous les operateurs
	*/


	template<class T, class Allocator>
	void swap(vector<T, Allocator>& x, vector<T, Allocator>& y)
	{ x.swap(y); }

}

#endif
