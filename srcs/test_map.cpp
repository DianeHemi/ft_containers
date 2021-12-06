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
	std::cout << "Size : " << mp.size() << " | Max size : " << mp.max_size() << " | Empty : " << mp.empty() << std::endl;
	typename NAMESPACE::map<T, U>::const_iterator it = mp.begin(), ite = mp.end();
	std::cout << "Content :" << std::endl;
	for (; it != ite; ++it)
	{
		std::cout << " - ";
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
    std::cout << "Inserting values" << std::endl;
    typename NAMESPACE::map<int, std::string> m1;
    typename NAMESPACE::map<int, std::string>::iterator it, ite;
    typename NAMESPACE::map<int, std::string>::const_iterator cit, cite;

    for(int i = 0; i < 10; i++)
        m1.insert(NAMESPACE::make_pair(i * 4, "Mapped"));
    print(m1);

    it = m1.begin();
    ite = m1.end();
    cit = m1.begin();
    cite = m1.end();
    std::cout << "\nIterators operations (++) - Non const" << std::endl;
    printPair(++it);
    printPair(it++);
    printPair(it++);
    printPair(++it);
    std::cout << "\nIterators operations (--) - Non const" << std::endl;
    printPair(--ite);
    printPair(ite--);
    printPair(ite--);
    printPair(--ite);
    std::cout << "\nIterators operations (++) - Const" << std::endl;
    printPair(++cit);
    printPair(cit++);
    printPair(cit++);
    printPair(++cit);
    std::cout << "\nIterators operations (--) - Const" << std::endl;
    printPair(--cite);
    printPair(cite--);
    printPair(cite--);
    printPair(--cite);
}

void map_reverse_iterators()
{
    std::cout << "Inserting values" << std::endl;
    typename NAMESPACE::map<int, std::string> m1;
    typename NAMESPACE::map<int, std::string>::reverse_iterator rit, rite;
    typename NAMESPACE::map<int, std::string>::const_reverse_iterator rcit, rcite;

    for(int i = 0; i < 10; i++)
        m1.insert(NAMESPACE::make_pair(i * 4, "Mapped"));
    print(m1);

    rit = m1.rbegin();
    rite = m1.rend();
    rcit = m1.rbegin();
    rcite = m1.rend();
    std::cout << "\nIterators operations (++) - Non const" << std::endl;
    printPair(++rit);
    printPair(rit++);
    printPair(rit++);
    printPair(++rit);
    std::cout << "\nIterators operations (--) - Non const" << std::endl;
    printPair(--rite);
    printPair(rite--);
    printPair(rite--);
    printPair(--rite);
    std::cout << "\nIterators operations (++) - Const" << std::endl;
    printPair(++rcit);
    printPair(rcit++);
    printPair(rcit++);
    printPair(++rcit);
    std::cout << "\nIterators operations (--) - Const" << std::endl;
    printPair(--rcite);
    printPair(rcite--);
    printPair(rcite--);
    printPair(--rcite);
}

void map_access()
{
    std::cout << "Empty map : " << std::endl;
    typename NAMESPACE::map<int, std::string> m1;
    print(m1);

    std::cout << "[] - Non existing value 12 : " << m1[12] << std::endl;

    std::cout << "\nFilling map : " << std::endl;
    for(int i = 0; i < 5; i++)
        m1.insert(NAMESPACE::make_pair(i * 9, "Mapped"));
    print(m1);

    std::cout << "\n[] - Existing value 18 : " << m1[18] << std::endl;
    std::cout << "at - Existing value 27 : " << m1[27] << std::endl;
}

void map_operations()
{
    std::cout << "\nFilling map : " << std::endl;
    typename NAMESPACE::map<int, std::string> m1;
    m1.insert(NAMESPACE::make_pair(2, "Two"));
    m1.insert(NAMESPACE::make_pair(4, "Four"));
    m1.insert(NAMESPACE::make_pair(8, "Eight"));
    m1.insert(NAMESPACE::make_pair(16, "Six"));
    print(m1);

    std::cout << "\nFind - Existing element" << std::endl;
    printPair(m1.find(4));

    std::cout << "\nCount - Existing element 16 : " << m1.count(16) << std::endl;

    std::cout << "\nLower bound 8" << std::endl;
    printPair(m1.lower_bound(8));
    std::cout << "Lower bound 12" << std::endl;
    printPair(m1.lower_bound(12));

    std::cout << "\nUpper bound 2" << std::endl;
    printPair(m1.upper_bound(2));
    std::cout << "Upper bound 6" << std::endl;
    printPair(m1.upper_bound(6));

    std::cout << "\nEqual range 2" << std::endl;
    printPair(m1.equal_range(2).first);
    printPair(m1.equal_range(2).second);

    std::cout << "\nEqual range 8" << std::endl;
    printPair(m1.equal_range(8).first);
    printPair(m1.equal_range(8).second);
}

void map_stresstest()
{
    typename NAMESPACE::map<int, std::string> m1;
    for(int i = 0; i < 1000000; i++)
        m1[i];
    typename NAMESPACE::map<int, std::string>::iterator it, ite;
    it = m1.begin();
    ite = m1.end();
    std::cout << m1.size() << std::endl;
    m1.erase(it, ite);
    std::cout << m1.size() << std::endl;
}

template<class T, class U>
void print_operator(NAMESPACE::map<T, U> a, NAMESPACE::map<T, U> b)
{
    static int i = 0;

	std::cout << "\n\t******** " << i++ << " ********" << std::endl;
	std::cout << "Equality : \t" << (a == b) << " | Difference : \t" << (a != b) << std::endl;
	std::cout << "Lower : \t" << (a < b) << " | Lower or equal : \t" << (a <= b) << std::endl;
	std::cout << "Greater : \t" << (a > b) << " | Greater or equal : \t" << (a >= b) << std::endl;
}

void map_relational_ope()
{
    typename NAMESPACE::map<int, int> m1;
    std::cout << "\nInserting some values in a map and copying it into another" << std::endl;
    for(int i = 1; i < 4096; i = i * 3)
        m1.insert(NAMESPACE::make_pair(i, i * 2));
    NAMESPACE::map<int, int> m2(m1); 
    print(m1);

    print_operator(m1, m1);
    print_operator(m1, m2);

    std::cout << "\nAdding a value in the first map : " << std::endl;
    m1.insert(NAMESPACE::make_pair(19, 13));
    print_operator(m1, m2);
    print_operator(m2, m1);

    std::cout << "\nAdding two values in the second map : " << std::endl;
    m2.insert(NAMESPACE::make_pair(5, 0));
    m2.insert(NAMESPACE::make_pair(1025, 0));
    print_operator(m1, m2);
    print_operator(m2, m1);
}

int main(void)
{
    /****************************************************************
							    Map
	****************************************************************/
    std::cout << "\n\nMAP" << std::endl;

    std::cout << "\033[1;32m\n--- Modifiers --- \033[0m" << std::endl;
    map_modifiers();

    std::cout << "\033[1;32m\n--- Iterators --- \033[0m" << std::endl;
    map_iterators();

    std::cout << "\033[1;32m\n--- Iterators --- \033[0m" << std::endl;
    map_reverse_iterators();

    std::cout << "\033[1;32m\n--- Access --- \033[0m" << std::endl;
    map_access();

    std::cout << "\033[1;32m\n--- Operations --- \033[0m" << std::endl;
    map_operations();

    std::cout << "\033[1;32m\n--- Relational operators --- \033[0m" << std::endl;
    map_relational_ope();
    
    /*std::cout << "\033[1;32m\n--- Stress test --- \033[0m" << std::endl;
    map_stresstest();*/

    return 0;
}