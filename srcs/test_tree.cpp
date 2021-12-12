#include "../includes/set/RBTree_set.hpp"

int main(void)
{
    std::cout << "Inserting values : " << std::endl;
    ft::RBTree<int> s1;

    for(int i = 0; i < 4; i++)
    {
        std::cout << (i * 4) << " ";
        s1._insertSingle(i * 4);
    }
    for(int i = 8; i > 4; i--)
    {
        std::cout << (i / 2) << " ";
        s1._insertSingle(i / 2);
    }
    for(int i = 8; i < 12; i++)
    {
        std::cout << (i * 3) << " ";
        s1._insertSingle(i * 3);
    }

    std::cout << std::endl; 
    s1.printTree();
}