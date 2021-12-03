#include <iostream>
#include "test_stack.cpp"
#include "test_vector.cpp"

int main(void)
{
    std::cout << "STACK" << std::endl;

    std::cout << "\033[1;32m--- Basic --- \033[0m" << std::endl;
    stack_basic_tests();
    std::cout << "\033[1;32m\n--- Relational operators --- \033[0m" << std::endl;
    stack_relational_test();
    std::cout << "\033[1;32m\n--- List compatibility --- \033[0m" << std::endl;
    stack_list_test();


    std::cout << "\n\nVECTOR" << std::endl;

    std::cout << "\033[1;32m--- Modifiers --- \033[0m" << std::endl;
    vector_modifiers();


    return 0;
}