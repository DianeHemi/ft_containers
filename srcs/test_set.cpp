#include <iostream>
#include <set>
#include "../includes/set/set.hpp"
#include <string>

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

template <class T>
void print( NAMESPACE::set<T> const & set)
{
	std::cout << "Size : " << set.size() << " | Max size : " << set.max_size() << " | Empty : " << set.empty() << std::endl;
	typename NAMESPACE::set<T>::const_iterator it = set.begin(), ite = set.end();
	std::cout << "Content :" << std::endl;
	for (; it != ite; ++it)
	{
		std::cout << " - " << *it;
	}	
}

void set_modifiers()
{
    std::cout << "Empty set : " << std::endl;
    typename NAMESPACE::set<std::string> s1, s2;
    typename NAMESPACE::set<std::string>::iterator it, ite;
    print(s1);

    std::cout << "\nAdding some values to map - insert[single element]" << std::endl;
    s1.insert("To be");
    s1.insert("or not");
    s1.insert("to be");
    print(s1);

    std::cout << "\nAdding some values to map - insert[with hint]" << std::endl;
    s1.insert(s1.begin(), "That is the question");
    s1.insert(s1.end(), "Pony");
    print(s1);

    std::cout << "\nAdding some values to map - insert[range]" << std::endl;
    s2.insert("To be");
    s2.insert("Dog");
    s2.insert("Cat");
    s2.insert("Mouse");
    s1.insert(s2.begin(), s2.end()--);
    print(s1);

    std::cout << "\nDeleting some values from map - erase[iterator]" << std::endl;
    it = s1.begin(); it++;
    ite = s1.end();
    ite--;
    s1.erase(it);
    s1.erase(ite);
    print(s1);

    std::cout << "\nDeleting some values from map - erase[key]" << std::endl;
    s1.erase("To be");
    s1.erase("or not");
    s1.erase("to be");
    print(s1);

    std::cout << "\nDeleting some values from map - erase[range]" << std::endl;
    it = s1.begin(); it++;
    ite = s1.end()--; ite--;
    s1.erase(it, ite);
    print(s1);

    std::cout << "\nSwap map - swap" << std::endl;
    std::cout << "Before : " << std::endl;
    print(s1);
    std::cout << "After : " << std::endl;
    s1.swap(s2);
    print(s1);

    std::cout << "\nClearing whole map - clear" << std::endl;
    s2.clear();
    print(s2);
}

void set_iterators()
{
    std::cout << "Inserting values" << std::endl;
    typename NAMESPACE::set<int> s1;
    typename NAMESPACE::set<int>::iterator it, ite;
    typename NAMESPACE::set<int>::const_iterator cit, cite;

    for(int i = 0; i < 10; i++)
        s1.insert(i * 4);
    print(s1);

    it = s1.begin();
    ite = s1.end();
    cit = s1.begin();
    cite = s1.end();
    std::cout << "\nIterators operations (++) - Non const" << std::endl;
    std::cout << *(++it) << " " << *(it++) << std::endl;
    std::cout << *(it++) << " " << *(++it) << std::endl;
    std::cout << "\nIterators operations (--) - Non const" << std::endl;
    std::cout << *(--ite) << " " << *(ite--) << std::endl;
    std::cout << *(ite--) << " " << *(--ite) << std::endl;
    std::cout << "\nIterators operations (++) - Const" << std::endl;
    std::cout << *(++cit) << " " << *(cit++) << std::endl;
    std::cout << *(cit++) << " " << *(++cit) << std::endl;
    std::cout << "\nIterators operations (--) - Const" << std::endl;
    std::cout << *(--cite) << " " << *(cite--) << std::endl;
    std::cout << *(cite--) << " " << *(--cite) << std::endl;
}

void set_reverse_iterators()
{
    std::cout << "Inserting values" << std::endl;
    typename NAMESPACE::set<int> s1;
    typename NAMESPACE::set<int>::reverse_iterator rit, rite;
    typename NAMESPACE::set<int>::const_reverse_iterator rcit, rcite;

    for(int i = 0; i < 10; i++)
        s1.insert(i * 4);
    print(s1);

    rit = s1.rbegin();
    rite = s1.rend();
    rcit = s1.rbegin();
    rcite = s1.rend();
    std::cout << "\nIterators operations (++) - Non const" << std::endl;
    std::cout << *(++rit) << " " << *(rit++) << std::endl;
    std::cout << *(rit++) << " " << *(++rit) << std::endl;
    std::cout << "\nIterators operations (--) - Non const" << std::endl;
    std::cout << *(--rite) << " " << *(rite--) << std::endl;
    std::cout << *(rite--) << " " << *(--rite) << std::endl;
    std::cout << "\nIterators operations (++) - Const" << std::endl;
    std::cout << *(++rcit) << " " << *(rcit++) << std::endl;
    std::cout << *(rcit++) << " " << *(++rcit) << std::endl;
    std::cout << "\nIterators operations (--) - Const" << std::endl;
    std::cout << *(--rcite) << " " << *(rcite--) << std::endl;
    std::cout << *(rcite--) << " " << *(--rcite) << std::endl;
}

void set_operations()
{
    std::cout << "\nFilling set : " << std::endl;
    typename NAMESPACE::set<int> s1;
    s1.insert(2);
    s1.insert(4);
    s1.insert(8);
    s1.insert(16);
    print(s1);

    std::cout << "\nFind - Existing element 4 : " << *(s1.find(4)) << std::endl;
    std::cout << "\nFind - Non-existing element 5 : " << *(s1.find(5)) << std::endl;

    std::cout << "\nCount - Existing element 16 : " << s1.count(16) << std::endl;
    std::cout << "Count - Non-existing element 5 : " << s1.count(5) << std::endl;

    std::cout << "\nLower bound 8 : " << *(s1.lower_bound(8)) << std::endl;
    std::cout << "Lower bound 12 : " << *(s1.lower_bound(12)) << std::endl;

    std::cout << "\nUpper bound 2 : " << *(s1.upper_bound(2)) << std::endl;
    std::cout << "Upper bound 6 : " << *(s1.upper_bound(6)) << std::endl;

    std::cout << "\nEqual range 2 : " << *(s1.equal_range(2).first) << " | " << *(s1.equal_range(2).second) << std::endl;
    std::cout << "\nEqual range 8 : " << *(s1.equal_range(8).first) << " | " << *(s1.equal_range(8).second) << std::endl;
}

void set_stresstest()
{
    typename NAMESPACE::set<int> s1;
    for(int i = 0; i < 1000000; i++)
        s1.insert(i);
    typename NAMESPACE::set<int>::iterator it, ite;
    it = s1.begin();
    ite = s1.end();
    std::cout << s1.size() << std::endl;
    s1.erase(it, ite);
    std::cout << s1.size() << std::endl;
}

template<class T>
void print_operator(NAMESPACE::set<T> a, NAMESPACE::set<T> b)
{
    static int i = 0;

	std::cout << "\n\t******** " << i++ << " ********" << std::endl;
	std::cout << "Equality : \t" << (a == b) << " | Difference : \t" << (a != b) << std::endl;
	std::cout << "Lower : \t" << (a < b) << " | Lower or equal : \t" << (a <= b) << std::endl;
	std::cout << "Greater : \t" << (a > b) << " | Greater or equal : \t" << (a >= b) << std::endl;
}

void set_relational_ope()
{
    typename NAMESPACE::set<int> s1;
    std::cout << "\nInserting some values in a map and copying it into another" << std::endl;
    for(int i = 1; i < 4096; i = i * 3)
        s1.insert(i * 2);
    NAMESPACE::set<int> s2(s1); 
    print(s1);

    print_operator(s1, s1);
    print_operator(s1, s2);

    std::cout << "\nAdding a value in the first map : " << std::endl;
    s1.insert(19);
    print_operator(s1, s2);
    print_operator(s2, s1);

    std::cout << "\nAdding two values in the second map : " << std::endl;
    s2.insert(5);
    s2.insert(1035);
    print_operator(s1, s2);
    print_operator(s2, s1);
}

int main(void)
{
    /****************************************************************
							    Map
	****************************************************************/
    std::cout << "\n\nMAP" << std::endl;

    std::cout << "\033[1;32m\n--- Modifiers --- \033[0m" << std::endl;
    set_modifiers();

    std::cout << "\033[1;32m\n--- Iterators --- \033[0m" << std::endl;
    set_iterators();

    std::cout << "\033[1;32m\n--- Iterators --- \033[0m" << std::endl;
    set_reverse_iterators();

    std::cout << "\033[1;32m\n--- Operations --- \033[0m" << std::endl;
    set_operations();

    std::cout << "\033[1;32m\n--- Relational operators --- \033[0m" << std::endl;
    set_relational_ope();
    
    /*std::cout << "\033[1;32m\n--- Stress test --- \033[0m" << std::endl;
    set_stresstest();*/

    return 0;
}