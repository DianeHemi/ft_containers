#include "stack.hpp"
#include <stack>
#include <iostream>

int main()
{
    ft::vector<int>     v1;
    for (int i = 0; i < 10; i++)
        v1.push_back(i);

    ft::stack<int> st1;
    ft::stack<int, ft::vector<int>> s1(v1);

    std::cout << s1.empty() << std::endl;
    std::cout << s1.size() << std::endl;
    std::cout << s1.top() << std::endl;

    std::cout << "Add 10 :" << std::endl;
    s1.push(10);
    std::cout << s1.top() << std::endl;

    std::cout << "Pop 10 :" << std::endl;
    s1.pop();
    std::cout << s1.top() << std::endl;

    return 0;
}