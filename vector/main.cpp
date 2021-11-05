#include "vector.hpp"
#include <iostream>

int main()
{
    ft::vector<int>     vi1;
    ft::vector<int>     vi2;

    vi1.push_back(1);
    vi1.push_back(2);

    std::cout << vi1[0] << " " << vi1[1] << std::endl;

    vi2.push_back(8);
    vi2.push_back(9);

    std::cout << vi2[0] << " " << vi2[1] << "\n" << std::endl;

    vi1.swap(vi2);
    std::cout << "Swap :" << std::endl;
    std::cout << vi1[0] << " " << vi1[1] << std::endl;
    std::cout << vi2[0] << " " << vi2[1] << std::endl;

    return 0;
}