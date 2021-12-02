#include <set>
#include "set.hpp"
#include "../map/RBTree.hpp"

int main()
{
    ft::set<int> s;

    s.insert(12);
    s.insert(8);
    s.insert(1);
    s.insert(32);
    s.insert(24);
    s.insert(16);

    ft::set<int>::iterator it = s.begin();
    ft::set<int>::iterator ite = s.end();
    ite--;
    it++;
    std::cout << "Insert" << std::endl;
    std::cout << "Iterators : " << *it << " " << *ite << std::endl;
    std::cout << "Size : " << s.size() << std::endl;


    ft::set<int> s2(s);
    it = s2.begin();
    ite = s2.end();
    std::cout << "Copy construct - Iterators : " << *it << " " << *ite << std::endl;
    std::cout << "Size : " << s2.size() << std::endl;

    ft::set<int> s3;
    s3.insert(64);
    s3.insert(8);
    s3.insert(128);
    s3.insert(it, 256);
    s3.insert(it, ite);

    ft::set<int>::iterator it2 = s3.begin();
    ft::set<int>::iterator ite2 = s3.end();
    ite2--;
    std::cout << "Iterator insert - Iterators : " << *it2 << " " << *ite2 << std::endl;
    std::cout << "Size : " << s3.size() << std::endl;

    s3.erase(8);
    it2 = s3.begin();
    std::cout << "\nErase" << std::endl;
    std::cout << "Iterators : " << *it2 << " " << *ite2 << std::endl;
    std::cout << "Size : " << s3.size() << std::endl;
    s3.erase(it2);
    it2 = s3.begin();
    std::cout << "Iterators : " << *it2 << " " << *ite2 << std::endl;
    std::cout << "Size : " << s3.size() << std::endl;
    it2++;
    ite2--;
    s3.erase(it2, ite2);
    it2 = s3.begin();
    ite2 = s3.end();
    ite2--;
    std::cout << "Iterators : " << *it2 << " " << *ite2 << std::endl;
    std::cout << "Size : " << s3.size() << std::endl;



    return 0;
}