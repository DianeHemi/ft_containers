#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

//https://githubmemory.com/repo/maxime-42/ft_containers
//https://www.fluentcpp.com/2018/05/08/std-iterator-deprecated/
//https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
//https://www.cplusplus.com/reference/iterator/iterator_traits/


namespace ft
{
	/*
		Iterator tags
	*/
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };


	/*
		Iterator traits
	*/
	template<class Iter>
	struct iterator_traits
	{
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};
	
	template<class T>
	struct iterator_traits<T*>
	{
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag 	iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*>
	{
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef random_access_iterator_tag 	iterator_category;
	};
	
	





	/*
		Iterator
	*/
	template<
		class Category,                     //Category of the iterator
		class T,                            //Type of valuesthat can be obtained by dereferencing the iterator
		class Distance = std::ptrdiff_t,    //A type that can be used to identify distance between iterators
		class Pointer = T*,                 //Defines a pointer to the type iterated over (T)
		class Reference = T&                //Defines a reference to the type iterated over (T)
	> struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};






//class randomAccessIterator

} //ft

#endif







//Bidirectional : map & set
	// ++, -- sauf si const. Avec *. ->, ==, !=
//Random-access iterator : vector
	// ++, +=, --, -= saif si const. Avec * ou []. ->, ==, !=, <, <=, >, >=
