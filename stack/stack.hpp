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
            typedef T           value_type;
            typedef Container   container_type;
            //typename typedef Container::value_type  value_type;
            typedef typename Container::size_type   size_type;
            typedef typename Container::reference   reference;
            typedef typename Container::const_reference const_reference;


		/****
			Constructors
		****/
        explicit stack( const container_type& cont = container_type() ) : _cont(cont) { };
        //stack( const stack& src ) :  { };
        ~stack() { };


        /****
			Member functions
		****/
        bool        empty() const { return (_cont.empty()); };
        size_type   size() const { return(_cont.size()); };

        value_type&         top() { return (_cont.back()); };
        const value_type&   top() const { return (_cont.back()); };

        void    push( const value_type& val ) { _cont.push_back(val); };
        void    pop() { _cont.pop_back(); };

        private:
            container_type  _cont;

    };

    template <class T, class Container>
    bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs == rhs;
    }

    template <class T, class Container>
    bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs != rhs;
    }

    template <class T, class Container>
    bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs < rhs;
    }

    template <class T, class Container>
    bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs <= rhs;
    }

    template <class T, class Container>
    bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs > rhs;
    }

    template <class T, class Container>
    bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs >= rhs;
    }

}

#endif