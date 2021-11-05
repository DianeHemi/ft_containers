#include "vector.hpp"
#include <vector>
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
    std::cout << *vi1.begin() << " " << vi1[1] << std::endl;
    std::cout << vi2.at(0) << " " << vi2.at(1) << "\n" << std::endl;

    vi1.at(0) = 12;
    vi1.at(1) = 13;
    vi1.push_back(14);
    vi1.push_back(15);
    std::cout << "Test changement de valeur via at()" << std::endl;
    std::cout << *vi1.begin() << " " << vi1[1] << std::endl;
    std::cout << "Test de front() et back() apres ajout de 14 et 15 dans le vecteur" << std::endl;
    std::cout << vi1.front() << " " << vi1.back() << std::endl;

    return 0;
}