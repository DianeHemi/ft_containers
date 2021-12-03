#include <iostream>
#include <map>
#include "../includes/map/map.hpp"
#include <string>

#ifndef NAMESPACE
# define NAMESPACE ft
#endif


template <class T>
void printPair(const T &iterator)
{
    std::cout << "Key : " << iterator->first << " | Value : " << iterator->second << std::endl;
}

template <class T, class U>
void print( NAMESPACE::map<T, U> const & mp)
{
	std::cout << "Size : " << mp.size() << " | Max size : " << mp.max_size() << std::endl;
	typename NAMESPACE::map<T, U>::const_iterator it = mp.begin(), ite = mp.end();
	std::cout << "Content :" << std::endl;
	for (; it != ite; ++it)
	{
		std::cout << "- ";
        printPair(it);
	}	
}

void map_modifiers()
{
    std::cout << "Empty map : " << std::endl;
    typename NAMESPACE::map<int, std::string> m1, m2;
    typename NAMESPACE::map<int, std::string>::iterator it, ite;
    print(m1);

    std::cout << "\nAdding some values to map - insert[single element]" << std::endl;
    m1.insert(NAMESPACE::make_pair(2, "To be"));
    m1.insert(NAMESPACE::make_pair(4, "or not"));
    m1.insert(NAMESPACE::make_pair(8, "to be"));
    print(m1);

    std::cout << "\nAdding some values to map - insert[with hint]" << std::endl;
    m1.insert(m1.begin(), NAMESPACE::make_pair(6, "That is the question"));
    m1.insert(m1.end(), NAMESPACE::make_pair(3, "Pony"));
    print(m1);

    std::cout << "\nAdding some values to map - insert[range]" << std::endl;
    m2.insert(NAMESPACE::make_pair(2, "To be"));
    m2.insert(NAMESPACE::make_pair(5, "Dog"));
    m2.insert(NAMESPACE::make_pair(7, "Cat"));
    m2.insert(NAMESPACE::make_pair(12, "Mouse"));
    m1.insert(m2.begin(), m2.end()--);
    print(m1);

    std::cout << "\nDeleting some values from map - erase[iterator]" << std::endl;
    it = m1.begin(); it++;
    ite = m1.end();
    ite--;
    m1.erase(it);
    m1.erase(ite);
    print(m1);

    std::cout << "\nDeleting some values from map - erase[key]" << std::endl;
    m1.erase(22);
    m1.erase(7);
    m1.erase(5);
    print(m1);

    std::cout << "\nDeleting some values from map - erase[range]" << std::endl;
    it = m1.begin(); it++;
    ite = m1.end()--; ite--;
    m1.erase(it, ite);
    print(m1);

    std::cout << "\nSwap map - swap" << std::endl;
    std::cout << "Before : " << std::endl;
    print(m1);
    std::cout << "After : " << std::endl;
    m1.swap(m2);
    print(m1);

    std::cout << "\nClearing whole map - clear" << std::endl;
    m2.clear();
    print(m2);
}

void map_iterators()
{
    



}