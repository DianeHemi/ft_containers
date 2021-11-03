#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

#https://githubmemory.com/repo/maxime-42/ft_containers

namespace ft
{
    template<
        class Category,                     //Category of the iterator
        class T,                            //Type of valuesthat can be obtained by dereferencing the iterator
        class Distance = std::ptrdiff_t,    //A type that can be usd to identify distance between iterators
        class Pointer = T*,                 //Defines a pointer to the type iterated over (T)
        class Reference = T&                //Defines a reference to the type iterated over (T)
    > struct iterator;

    //class randomAccessIterator{

    };

    //typedef Category  iterator_category;
    //typedef T         value_type;
    //typedef Distance  difference_type;
    //typedef Pointer   pointer;
    //typedef Reference reference;




} //ft

#endif
