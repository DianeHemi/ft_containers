#ifndef STACK_HPP
# define STACK_HPP

# include "../vector/vector.hpp"

namespace ft
{
	template< class T, class Container = ft::vector<T> >
	class stack
	{
		/*
			Member type
		*/
		public:
			//typedef T           value_type;
			typedef Container   container_type;
			typedef typename Container::value_type  value_type;
			typedef typename Container::size_type   size_type;
			typedef typename Container::reference   reference;
			typedef typename Container::const_reference const_reference;


		/****
			Constructors
		****/
		explicit stack( const container_type& cont = container_type() ) : _cont(cont) { };
		stack( const stack& src ) { *this = src; };
		stack& operator=( const stack& rhs )
		{
			if (this != &rhs)
				_cont = rhs._cont;
			return *this;
		};
		~stack() { };


		/****
			Member functions
		****/
		bool        empty() const { return (_cont.empty()); };
		size_type   size() const { return(_cont.size()); };

		reference         top() { return (_cont.back()); };
		const reference   top() const { return (_cont.back()); };

		void    push( const value_type& val ) { _cont.push_back(val); };
		void    pop() { _cont.pop_back(); };

		protected:
			container_type  _cont;

		public:
			friend  bool operator==( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
			{ return lhs._cont == rhs._cont; };

			friend bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{ return lhs._cont != rhs._cont; };

			friend bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{ return lhs._cont < rhs._cont; };

			friend bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{ return lhs._cont <= rhs._cont; };

			friend bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{ return lhs._cont > rhs._cont; };

			friend bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{ return lhs._cont >= rhs._cont; };
	};

}

#endif