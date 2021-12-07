#ifndef NAMESPACE
    # define NAMESPACE ft
#endif



    #include <iostream>
    #include "../includes/vector/vector.hpp"
    #include "../includes/set/set.hpp"
    #include "../includes/map/map.hpp"
    #include <list>
    #include <vector>
    #include "../includes/stack/stack.hpp"

        #include <iostream>
    #include <stack>
    #include <string>
    #include <set>
    #include <map>

//VECTOR
template<class T>
void print_vector(const NAMESPACE::vector<T>& v);
void vector_modifiers();
void vector_stresstest();
void vector_access();
void print_iter_operator(NAMESPACE::vector<int>::const_iterator a, NAMESPACE::vector<int>::const_iterator b);
void vector_iterator();
void print_rev_iter_operator(NAMESPACE::vector<int>::const_reverse_iterator a, NAMESPACE::vector<int>::const_reverse_iterator b);
void vector_reverse_iterator();
void print_operator(NAMESPACE::vector<int> a, NAMESPACE::vector<int> b);
void vector_relational_ope();

//STACK
void stack_basic_tests();
void print_cmp( const NAMESPACE::stack<unsigned int>& a, const NAMESPACE::stack<unsigned int>& b );
void print_cmp_list( const NAMESPACE::stack<char, std::list<char> >& a, const NAMESPACE::stack<char, std::list<char> >& b );
void stack_relational_test();
void stack_list_test();


//MAP
template <class T>
void map_printPair(const T &iterator);
template <class T, class U>
void map_print( NAMESPACE::map<T, U> const & mp);
void map_modifiers();
void map_iterators();
void map_reverse_iterators();
void map_access();
void map_operations();
void map_stresstest();
template<class T, class U>
void map_print_operator(NAMESPACE::map<T, U> a, NAMESPACE::map<T, U> b);
void map_relational_ope();

//SET
template <class T>
void set_print( NAMESPACE::set<T> const & set);
void set_modifiers();
void set_iterators();
void set_reverse_iterators();
void set_operations();
void set_stresstest();
template<class T>
void set_print_operator(NAMESPACE::set<T> a, NAMESPACE::set<T> b);
void set_relational_ope();

