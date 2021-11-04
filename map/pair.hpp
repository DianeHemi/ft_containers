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

		public:
			pair() { };
			pair( const T1& x, const T2& y ) : _fist(x), _second(y) { };
			template<class U1, class U2> pair( const pair<U1, U2>& p ) : _first(p._first), _second(p._second)  { };
			~pair() { };

			//pair& operator=( const pair& pr ) { };  //return *this

			/*
			template <class T1, class T2>
			bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return lhs.first==rhs.first && lhs.second==rhs.second; }

			template <class T1, class T2>
			bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return !(lhs==rhs); }

			template <class T1, class T2>
			bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

			template <class T1, class T2>
			bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return !(rhs<lhs); }

			template <class T1, class T2>
			bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return rhs<lhs; }

			template <class T1, class T2>
			bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return !(lhs<rhs); }
			*/

		protected:
			first_type      _first;
			second_type     _second;
	};



	/*
		Make pair
	*/
	template<class T1, class T2>
    ft::pair<T1, T2> make_pair( T1 x, T2 y );
	//{ return (pair<T1,T2>(x,y)); }
	
}

#endif