#include "map.hpp"
#include <map>
#include <iostream>

int main()
{
	std::cout << "Basic insert" << std::endl;
    ft::map<int, int> m1;
    
	m1.insert(ft::make_pair(13, 25));
	m1.insert(ft::make_pair(17, 15));
	m1.insert(ft::make_pair(60, 15));
	m1.insert(ft::make_pair(15, 80));
	m1.insert(ft::make_pair(10, 80));
	m1.insert(ft::make_pair(1, 80));
	m1.insert(ft::make_pair(5, 80));
	m1.insert(ft::make_pair(3, 80));
	m1.insert(ft::make_pair(12, 80));

	/*m1.insert(ft::make_pair(58, 30));
	m1.insert(ft::pair<int, int>(40, 30));
	m1.insert(ft::pair<int, int>(65, 21));
	m1.insert(ft::pair<int, int>(60, 22));
	m1.insert(ft::pair<int, int>(75, 23));
	m1.insert(ft::pair<int, int>(57, 24));
	m1.insert(ft::pair<int, int>(20, 28));
	m1.insert(ft::pair<int, int>(62, 29));*/
	m1.printTree();


	std::cout << "\n\nIterator insert" << std::endl;
	ft::map<int, int>::iterator it = m1.begin();
	ft::map<int, int>::iterator ite = m1.end();
	it++;
	it++;
	ite--;
	ite--;

	ft::map<int, int> m2;
	m2.insert(ft::make_pair(88, 25));
	m2.insert(ft::make_pair(18, 25));
	m2.insert(ft::make_pair(98, 25));
	m2.insert(it, ite);
	m2.printTree();

	std::cout << "\n\nIterator constructor" << std::endl;
	ft::map<int, int> m3(it, ite);
	m3.printTree();

	std::cout << "\n\nReverse iterator (rbegin / rend-- to avoid segfault)" << std::endl;
	ft::map<int, int>::reverse_iterator rit = m1.rbegin();
	ft::map<int, int>::reverse_iterator rite = m1.rend();
	rite--;
	std::cout << rit->_first << " - " << rite->_first << std::endl;

	std::cout << "\n\nTest delete from iterator" << std::endl;
	m2.printTree();
	ft::map<int, int>::iterator it2 = m2.begin();
	it2++;
	it2++;
	std::cout << it2->_first << std::endl;
	m2.erase(it2);
	m2.printTree();

    return 0;
}