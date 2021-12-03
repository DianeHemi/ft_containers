#include <iostream>
#include <vector>
#include "../includes/vector/vector.hpp"
#include <string>


#ifndef NAMESPACE
# define NAMESPACE ft
#endif

template<class T>
void print_vector(const NAMESPACE::vector<T>& v)
{
	std::cout << "Size : " << v.size() << " | Capacity : " << v.capacity() << " | Max size : " << v.max_size() << std::endl;

	typename NAMESPACE::vector<T>::const_iterator it = v.begin();
	typename NAMESPACE::vector<T>::const_iterator ite = v.end();
	std::cout << "Content :" << std::endl;
	for (; it != ite; ++it)
		std::cout << " - " << *it;
    std::cout << std::endl;
}


void vector_modifiers()
{
    std::cout << "\nEmpty vector" << std::endl;
    NAMESPACE::vector<int> v1;
    print_vector(v1);

    std::cout << "Inserting values into vector - push_back" << std::endl;
    for(int i = 1; i < 10; i++)
        v1.push_back(i * 2);
    print_vector(v1);

    std::cout << "\nDeleting values from vector - pop_back" << std::endl;
    for(int i = 0; i < 3; i++)
        v1.pop_back();
    print_vector(v1);

    std::cout << "\nInserting values into vector - assign[fill]" << std::endl;
    NAMESPACE::vector<int> v2(v1);
    v1.assign(5, 512);
    print_vector(v1);

    std::cout << "\nInserting values into vector - assign[range]" << std::endl;
    NAMESPACE::vector<int>::iterator it = v2.begin() + 1;
    NAMESPACE::vector<int>::iterator ite = v2.end() - 2;
    v1.assign(it, ite);
    print_vector(v1);

    std::cout << "\nEmptying the vector - clear" << std::endl;
    v1.clear();
    print_vector(v1);

    std::cout << "\nInserting values into vector - insert[single element]" << std::endl;
    v1.insert(v1.begin(), 1024);
    print_vector(v1);
    std::cout << "\nInserting a few others" << std::endl;
    v1.insert(v1.begin(), 256);
    v1.insert(v1.begin() + 1, 512);
    v1.insert(v1.end(), 2048);
    print_vector(v1);

    std::cout << "\nInserting values into vector - insert[fill]" << std::endl;
    v1.insert(v1.begin() + 1, 8, 2);
    print_vector(v1);

    std::cout << "\nInserting values into vector - insert[range]" << std::endl;
    v1.insert(v1.end() - 2, it, ite);
    print_vector(v1);

    std::cout << "\nErasing values from vector - erase[single element]" << std::endl;
    

    std::cout << "\nErasing values from vector - erase[range]" << std::endl;
}