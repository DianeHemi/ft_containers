#include "map.hpp"
#include <map>
#include <iostream>
#include <list>

#include "RBTree.hpp"


#include <chrono>
using namespace std::chrono;

/*
void testInsert()
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
	m1.insert(ft::make_pair(12, 80));*/

	/*m1.insert(ft::make_pair(58, 30));
	m1.insert(ft::pair<int, int>(40, 30));
	m1.insert(ft::pair<int, int>(65, 21));
	m1.insert(ft::pair<int, int>(60, 22));
	m1.insert(ft::pair<int, int>(75, 23));
	m1.insert(ft::pair<int, int>(57, 24));
	m1.insert(ft::pair<int, int>(20, 28));
	m1.insert(ft::pair<int, int>(62, 29));*/
/*	
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
}

void iteratorConstructor( ft::map<int, int>::iterator it, ft::map<int, int>::iterator ite )
{
	std::cout << "\n\nIterator constructor" << std::endl;
	ft::map<int, int> m3(it, ite);
	m3.printTree();
}

void reverseIterator(ft::map<int, int> m1, ft::map<int, int> m2)
{
	std::cout << "\n\nReverse iterator (rbegin / rend-- to avoid segfault)" << std::endl;
	ft::map<int, int>::reverse_iterator rit = m1.rbegin();
	ft::map<int, int>::reverse_iterator rite = m1.rend();
	rite--;
	std::cout << rit->first << " - " << rite->first << std::endl;
}

void testDelete(ft::map<int, int> m2)
{
	std::cout << "\n\nTest delete from one iterator" << std::endl;
	m2.printTree();
	ft::map<int, int>::iterator it2 = m2.begin();
	ft::map<int, int>::iterator ite2 = m2.end();
	it2++;
	std::cout << it2->first << std::endl;
	m2.erase(it2);
	m2.printTree();

	std::cout << "\n\nTest delete from iterator range" << std::endl;
	it2 = m2.begin();
	it2++;
	ite2--;
	std::cout << it2->first << " - " << ite2->first << std::endl;
	std::cout << "Doit rester seulement 5-80 et 98-25" << std::endl;
	m2.erase(it2, ite2);
	m2.printTree();
}
*/


#define T1 int
#define T2 int
typedef ft::pair<const T1, T2> T3;

int main()
{
	/*ft::RBTree<int, int> tree;

	tree._insertSingle(ft::make_pair(13, 25));
	tree._insertSingle(ft::make_pair(17, 15));
	tree._insertSingle(ft::make_pair(60, 15));
	tree._insertSingle(ft::make_pair(15, 80));
	tree._insertSingle(ft::make_pair(10, 80));
	tree._insertSingle(ft::make_pair(1, 80));
	tree._insertSingle(ft::make_pair(5, 80));
	tree._insertSingle(ft::make_pair(3, 80));
	tree._insertSingle(ft::make_pair(12, 80));

	tree.printTree();*/




	std::cout << "\nInsert" << std::endl;
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
	m1.getTree()->printTree();


	//std::cout << m1.count(17) << std::endl;

	/*ft::map<int, int>::iterator it = m1.find(17);
	std::cout << it->first << std::endl;*/

	//std::cout << m1.empty() << " - " << m1.size() << " - " << m1.max_size() << std::endl;
	
	/*std::cout << m1[17] << std::endl;
	std::cout << m1[18] << std::endl;
	m1.getTree()->printTree();*/

	
	std::cout << "\n\nIterator insert" << std::endl;
	m1.getTree()->printTree();
	ft::map<int, int>::iterator it = m1.begin();
	ft::map<int, int>::iterator ite = m1.end();
	it++;
	it++;
	ite--;
	ite--;

	ft::map<int, int> m2;
	m2.insert(ft::make_pair(88, 25));
	m2.insert(ite, ft::make_pair(18, 25));
	m2.insert(ft::make_pair(98, 25));
	std::cout << it->first << " - " << ite->first << std::endl;
	m2.insert(it, ite);
	m2.getTree()->printTree();


/*auto start = high_resolution_clock::now();
for (int i = 0; i < 1000000; i++)
	m2.insert(ft::make_pair(i, i));
auto stop = high_resolution_clock::now();
auto duration = duration_cast<milliseconds>(stop - start);
std::cout << duration.count() << std::endl;*/


	/*std::cout << "\n\nIterator constructor" << std::endl;
	ft::map<int, int> m3(it, ite);
	m3.getTree()->printTree();*/

	/*std::cout << "Lower bound of 15 : " << (m2.lower_bound(15))->first << std::endl;
	std::cout << "Upper bound of 18 : " << (m2.upper_bound(18))->first << std::endl;
	std::cout << "Equal range of 18 : " << (m2.equal_range(18)).first->first << " | " << (m2.equal_range(18)).second->first << std::endl;*/

	/*std::cout << "\n\nSwap" << std::endl;
	m1.getTree()->printTree();
	m1.swap(m2);
	m1.getTree()->printTree();
	m2.getTree()->printTree();*/
	
	/*std::cout << "\n\nDelete" << std::endl;
	ft::map<int, int>::iterator it2 = m2.begin();
	ft::map<int, int>::iterator ite2 = m2.end();
	it2++;
	std::cout << it2->first << std::endl;
	m2.erase(10);
	m2.getTree()->printTree();
	
	std::cout << "\n\nTest delete from iterator range" << std::endl;
	it2 = m2.begin();
	ite2 = m2.end();
	it2++;
	ite2--;
	std::cout << it2->first << " - " << ite2->first << std::endl;
	std::cout << "Doit rester seulement 98-25 et 5-80" << std::endl;
	m2.erase(it2, ite2);
	m2.getTree()->printTree();*/

	


	std::cout << std::endl;
	


    return 0;
}
