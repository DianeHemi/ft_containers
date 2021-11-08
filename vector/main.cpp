#include "vector.hpp"
#include <vector>
#include <iostream>

void test_iterator()
{
    ft::vector<int> v1;
    v1.push_back(12);
    v1.push_back(13);
    v1.push_back(14);
    v1.push_back(15);
    ft::vector<int>::iterator it = v1.begin();

    std::cout << "\n\n" << *it << std::endl;
    it++;
    std::cout << *it << std::endl;
    it--;
    std::cout << *it << std::endl;
    it += 2;
    std::cout << *it << std::endl;
    it -= 1;
    std::cout << *it << std::endl;

    ft::vector<int>::iterator ite = v1.begin();
    ite = it;
    std::cout << *ite << std::endl;

    if (it == ite)
        std::cout << "Equal" << std::endl;
    ite++;
    if (it <= ite)
        std::cout << "Ite bigger" << std::endl;
    ite -= 2;
    if (it >= ite)
        std::cout << "It bigger" << std::endl;
    if (it != ite)
        std::cout << "It's are differents" << std::endl;
}

void test_erase()
{
    ft::vector<int>     vi1;
    for(int i = 0; i < 10; i++)
        vi1.push_back(i);

    ft::vector<int>::iterator it = vi1.begin();
    std::cout << "\n\nTest d'un erase() sur la 1ere valeur" << std::endl;
    std::cout << "Starting size : " << vi1.size() << " Front/Back : " << vi1.front() << " / " << vi1.back() << std::endl;
    vi1.erase(it);
    std::cout << "New size : " << vi1.size() << " Front/Back : " << vi1.front() << " / " << vi1.back() << std::endl;

    vi1.push_back(5);
    vi1.push_back(6);
    it = vi1.end() -1;
    it--;
    vi1.erase(it);
    std::cout << "Ajout de 5 et 6 a la fin, et erase sur le 5" << std::endl;
    std::cout << "New size : " << vi1.size() << " Front/Back : " << vi1.front() << " / " << vi1.back() << std::endl;

    std::cout << "\nTest d'un erase() avec range (2 - 8)" << std::endl;
    it = vi1.begin() + 1;
    ft::vector<int>::iterator ite = vi1.end() - 3;
    vi1.erase(it, ite);
    std::cout << "New size : " << vi1.size() << " Front/Back : " << vi1.front() << " / " << vi1.back() << std::endl;
}


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
    vi2.clear();
    std::cout << "Test d'un clear sur le 2e vecteur : " << std::endl;
    std::cout << "New size : " << vi2.size() << std::endl;

    vi1.at(0) = 12;
    vi1.at(1) = 13;
    vi1.push_back(14);
    vi1.push_back(15);
    std::cout << "Test changement de valeur via at()" << std::endl;
    std::cout << *vi1.begin() << " " << vi1[1] << std::endl;
    std::cout << "Test de front() et back() apres ajout de 14 et 15 dans le vecteur" << std::endl;
    std::cout << vi1.front() << " " << vi1.back() << std::endl;

    vi1.resize(1, 0);
    std::cout << "Test d'un resize a 1 du vecteur :" << std::endl;
    std::cout << "New size : " << vi1.size() << " Front/Back : " << vi1.front() << " / " << vi1.back() << std::endl;
    vi1.resize(10, 8);
    std::cout << "Test d'un resize a 10 du vecteur avec ajout de 8 :" << std::endl;
    std::cout << "New size : " << vi1.size() << " Front/Back : " << vi1.front() << " / " << vi1.back() << std::endl;
    
    vi1.pop_back();
    std::cout << "Test d'un pop_back()" << std::endl;
    std::cout << "New size : " << vi1.size() << " Front/Back : " << vi1.front() << " / " << vi1.back() << std::endl;

//test_iterator();
//test_erase();

/*
    std::cout << "Test d'assignation du contenu dans un autre vecteur contenant deja des chiffres de 0 a 4" << std::endl;
    ft::vector<int>::iterator it = vi1.begin();
    ft::vector<int>::iterator ite = vi1.end();
    for (size_t i = 0; i < 5; i++)
        vi2.push_back(i);
    vi2.assign(it, ite);
    std::cout << "Old size : " << vi2.size() << " Front/Back : " << vi2.front() << " / " << vi2.back() << std::endl;
    std::cout << "New size : " << vi2.size() << " Front/Back : " << vi2.front() << " / " << vi2.back() << std::endl;
*/

    ft::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    ft::vector<int>::iterator i2 = v.begin();   // + 1 working
    v.insert(i2, 4);
    std::cout << "\nInsertion d'un 4 en deuxieme position d'un vecteur :" << std::endl;
    for(size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;
    v.erase(i2);
    /*std::cout << "\nSuppression du 4 et ajout de trois 6 avant le 2 :" << std::endl;
    i2 = v.begin();
    v.insert(i2, 1, 6);
    for(size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;*/

    return 0;
}