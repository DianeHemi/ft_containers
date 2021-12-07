#include "tests.hpp"

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
    v1.erase(v1.begin() + 3);
    print_vector(v1);
    v1.erase(v1.end() - 2);
    v1.erase(v1.begin() + 5);
    print_vector(v1);

    std::cout << "\nErasing values from vector - erase[range]" << std::endl;
    v1.erase(v1.begin() + 1, v1.end() - 5);
    print_vector(v1);

    std::cout << "\nSwapping values between vectors - swap" << std::endl;
    std::cout << "Second vector :" << std::endl;
    print_vector(v2);
    v1.swap(v2);
    std::cout << "Second vector after swap :" << std::endl;
    print_vector(v2);

    std::cout << "\nCapacity" << std::endl;
    std::cout << "Current capacity : " << v2.capacity() << std::endl;
    v2.reserve(58);
    std::cout << "Reserve 58 : " << v2.capacity() << std::endl;

    std::cout << "\nSize" << std::endl;
    std::cout << "Current size : " << v2.size() << std::endl;
    v2.resize(2);
    std::cout << "Resize to 2 : " << std::endl;
    print_vector(v2);
}

void vector_stresstest()
{
    std::cout << "Inserting a million elements :" << std::endl;
    NAMESPACE::vector<int> v1;
    v1.insert(v1.begin(), 1000000, 2);
    std::cout << "Erasing a million elements :" << std::endl;
    v1.erase(v1.begin(), v1.end());
}

void vector_access()
{
    NAMESPACE::vector<int> v1;

    std::cout << "\nInserting some values in vector" << std::endl;
    for(int i = 2; i < 4096; i = i * 2)
        v1.push_back(i);
    print_vector(v1);

    std::cout << "Operator []" << std::endl;
    std::cout << "v1[2] - " << v1[2] << std::endl;
    std::cout << "v1[5] - " << v1[5] << std::endl;
    std::cout << "v1[8] - " << v1[8] << std::endl;

    std::cout << "\nOperator front - back" << std::endl;
    std::cout << "Front : " << v1.front() << " | Back : " << v1.back() << std::endl;

    std::cout << "\nOperator at" << std::endl;
    std::cout << "at[1] - " << v1.at(1) << std::endl;
    std::cout << "at[3] - " << v1.at(3) << std::endl;
    std::cout << "at[9] - " << v1.at(9) << std::endl;
}


void print_iter_operator(NAMESPACE::vector<int>::const_iterator a, NAMESPACE::vector<int>::const_iterator b)
{
    static int i = 0;

	std::cout << "\n\t******** " << i++ << " ********" << std::endl;
	std::cout << "Equality : \t" << (a == b) << " | Difference : \t" << (a != b) << std::endl;
	std::cout << "Lower : \t" << (a < b) << " | Lower or equal : \t" << (a <= b) << std::endl;
	std::cout << "Greater : \t" << (a > b) << " | Greater or equal : \t" << (a >= b) << std::endl;
}

void vector_iterator()
{
    NAMESPACE::vector<int> v1;

    std::cout << "\nInserting some values in vector" << std::endl;
    for(int i = 2; i < 4096; i = i * 2)
        v1.push_back(i);
    print_vector(v1);

    NAMESPACE::vector<int>::iterator it = v1.end() - 1;
    NAMESPACE::vector<int>::const_iterator cit = v1.begin();

    std::cout << "\nTesting arrow operator on iterator" << std::endl;
    std::cout << *(--it) << " " << *(it--) << " " << *it-- << " " << *--it << std::endl;

    std::cout << "\nTesting arrow operator on const iterator" << std::endl;
    std::cout << *(++cit) << " " << *(cit++) << " " << *cit++ << " " << *++cit << std::endl;

    std::cout << "\nTesting equality operators on iterator" << std::endl;
    print_iter_operator(it, it);
    print_iter_operator(it, it + 3);
    print_iter_operator(cit, cit);
    print_iter_operator(cit - 2, cit);
    print_iter_operator(cit - 1, cit + 1);
}

void print_rev_iter_operator(NAMESPACE::vector<int>::const_reverse_iterator a, NAMESPACE::vector<int>::const_reverse_iterator b)
{
    static int i = 0;

	std::cout << "\n\t******** " << i++ << " ********" << std::endl;
	std::cout << "Equality : \t" << (a == b) << " | Difference : \t" << (a != b) << std::endl;
	std::cout << "Lower : \t" << (a < b) << " | Lower or equal : \t" << (a <= b) << std::endl;
	std::cout << "Greater : \t" << (a > b) << " | Greater or equal : \t" << (a >= b) << std::endl;
}

void vector_reverse_iterator()
{
    NAMESPACE::vector<int> v1;

    std::cout << "\nInserting some values in vector" << std::endl;
    for(int i = 1; i < 4096; i = i * 3)
        v1.push_back(i);
    print_vector(v1);

    NAMESPACE::vector<int>::reverse_iterator it = v1.rend();
    NAMESPACE::vector<int>::const_reverse_iterator cit = v1.rbegin() + 1;

    std::cout << "\nTesting arrow operator on iterator" << std::endl;
    std::cout << *(--it) << " " << *(it--) << " " << *it-- << " " << *--it << std::endl;

    std::cout << "\nTesting arrow operator on const iterator" << std::endl;
    std::cout << *(++cit) << " " << *(cit++) << " " << *cit++ << " " << *++cit << std::endl;

    std::cout << "\nTesting equality operators on iterator" << std::endl;
    print_rev_iter_operator(it, it);
    print_rev_iter_operator(it, it + 3);
    print_rev_iter_operator(cit, cit);
    print_rev_iter_operator(cit - 2, cit);
    print_rev_iter_operator(cit - 1, cit + 1);
}

void print_operator(NAMESPACE::vector<int> a, NAMESPACE::vector<int> b)
{
    static int i = 0;

	std::cout << "\n\t******** " << i++ << " ********" << std::endl;
	std::cout << "Equality : \t" << (a == b) << " | Difference : \t" << (a != b) << std::endl;
	std::cout << "Lower : \t" << (a < b) << " | Lower or equal : \t" << (a <= b) << std::endl;
	std::cout << "Greater : \t" << (a > b) << " | Greater or equal : \t" << (a >= b) << std::endl;
}

void vector_relational_ope()
{
    NAMESPACE::vector<int> v1;

    std::cout << "\nInserting some values in a vector and copying it into another" << std::endl;
    for(int i = 1; i < 4096; i = i * 3)
        v1.push_back(i);
    NAMESPACE::vector<int> v2(v1); 
    print_vector(v1);

    print_operator(v1, v1);
    print_operator(v1, v2);

    std::cout << "\nAdding a value in the first vector : " << std::endl;
    v1.push_back(2);
    print_operator(v1, v2);
    print_operator(v2, v1);

    std::cout << "\nAdding two values in the second vector : " << std::endl;
    v2.push_back(0);
    v2.push_back(123);
    print_operator(v1, v2);
    print_operator(v2, v1);
}