#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	/*
		Pair
	*/
	template<class T1, class T2>
	struct pair
	{
		public:
			typedef T1   first_type;
			typedef T2   second_type;

			pair() { };
			pair( const T1& x, const T2& y ) : _first(x), _second(y) { };
			template<class U1, class U2> pair( const pair<U1, U2>& p ) : _first(p._first), _second(p._second)  { };
			pair& operator= ( const pair& rhs )
			{
				if (this != &rhs)
				{
					_first = rhs._first;
					_second = rhs._second;
				}
				return *this;
			};
			~pair() { };

			first_type      _first;
			second_type     _second;
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return lhs.first == rhs.first && lhs.second == rhs.second; }

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !( lhs == rhs ); }

	template <class T1, class T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return (lhs.first < rhs.first || (!( rhs.first < lhs.first ) && lhs.second < rhs.second )); }

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !( rhs < lhs ); }

	template <class T1, class T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return ( rhs < lhs ); }

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !( lhs < rhs ); }



	/*
		Make pair
	*/
	template<class T1, class T2>
    ft::pair<T1, T2> make_pair( T1 x, T2 y )
	{ return (pair<T1,T2>( x, y )); }


	/*
		Less
	*/
	template<class T>
	struct less
	{
		bool operator() (const T& x, const T& y) const { return x < y; };
	};

}

#endif