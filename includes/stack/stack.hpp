#ifndef STACK_HPP
# define STACK_HPP

# include "../vector/vector.hpp"

/*
	https://www.cplusplus.com/reference/stack/stack/?kw=stack
	
	https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf
	P 508 du pdf (481)
*/

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


		/****************************************************************
								 Constructors
		****************************************************************/
		explicit stack( const Container& cont = Container() ) : c(cont) { };


		/****************************************************************
								Member functions
		****************************************************************/
		bool        empty() const { return (c.empty()); };
		size_type   size() const { return(c.size()); };

		value_type&         top() { return (c.back()); };
		const value_type&   top() const { return (c.back()); };

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