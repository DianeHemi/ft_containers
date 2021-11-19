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
	/*m1.insert(ft::make_pair(12, 80));
	m1.insert(it, ft::make_pair(21, 80));*/


	/*m1.insert(ft::make_pair(58, 30));*/
	/*bst._rbt->insert(ft::pair<int, int>(40, 30));
	
	bst._rbt->insert(ft::pair<int, int>(65, 21));
	bst._rbt->insert(ft::pair<int, int>(60, 22));
	bst._rbt->insert(ft::pair<int, int>(75, 23));
	bst._rbt->insert(ft::pair<int, int>(57, 24));
	bst._rbt->insert(ft::pair<int, int>(20, 28));
	bst._rbt->insert(ft::pair<int, int>(62, 29));*/
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


    return 0;
}