#ifndef STACK_HPP
# define STACK_HPP

# include "../vector/vector.hpp"

namespace ft
{
	template< class T, class Container = ft::vector<T> >
	class stack
	{
		/****************************************************************
								 Definitions
		****************************************************************/
		public:
			typedef Container   container_type;
			typedef typename Container::value_type  value_type;
			typedef typename Container::size_type   size_type;
			typedef typename Container::reference   reference;
			typedef typename Container::const_reference const_reference;


		/****************************************************************
								 Constructors
		****************************************************************/
		explicit stack( const container_type& cont = container_type() ) : c(cont) { };
		stack( const stack& other ) { *this = other; };
		stack& operator=( const stack& other )
		{
			if (this != &other)
				c = other.c;
			return *this;
		};
		~stack() { };


		/****************************************************************
								Member functions
		****************************************************************/
		bool        empty() const { return (c.empty()); };
		size_type   size() const { return(c.size()); };

		reference         top() { return (c.back()); };
		const reference   top() const { return (c.back()); };

		void    push( const value_type& value ) { c.push_back(value); };
		void    pop() { c.pop_back(); };

		protected:
			container_type  c;

		public:
			friend  bool operator==( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
			{ return lhs.c == rhs.c; };

			friend bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{ return lhs.c < rhs.c; };

	};

	template <class T, class Container>
	bool operator !=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return !(lhs == rhs); };

	template <class T, class Container>
	bool operator <=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return !(rhs < lhs); };

	template <class T, class Container>
	bool operator >(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return rhs < lhs; };

	template <class T, class Container>
	bool operator >=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{ return !(lhs < rhs); };

} //ft

#endif