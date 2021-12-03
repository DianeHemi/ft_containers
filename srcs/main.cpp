#include <iostream>
#include <ctime>
#include "test_stack.cpp"
#include "test_vector.cpp"

int main(void)
{
    clock_t start, end;

    /****************************************************************
							    Stack
	****************************************************************/
    std::cout << "STACK" << std::endl;

    start = clock();
    std::cout << "\033[1;32m--- Basic --- \033[0m" << std::endl;
    stack_basic_tests();
    end = clock();

    std::cout << "Execution time : " << (double)(end - start)/CLOCKS_PER_SEC << std::endl;
    std::cout << "\033[1;32m\n--- Relational operators --- \033[0m" << std::endl;
    start = clock();
    stack_relational_test();
    end = clock();

    std::cout << "Execution time : " << (double)(end - start)/CLOCKS_PER_SEC << std::endl;
    std::cout << "\033[1;32m\n--- List compatibility --- \033[0m" << std::endl;
    stack_list_test();


    /****************************************************************
							    Vector
	****************************************************************/
    std::cout << "\n\nVECTOR" << std::endl;

    std::cout << "\033[1;32m--- Modifiers --- \033[0m" << std::endl;
    start = clock();
    vector_modifiers();
    end = clock();
    std::cout << "Execution time : " << (double)(end - start)/CLOCKS_PER_SEC << std::endl;

    /*std::cout << "\033[1;32m--- Stress test --- \033[0m" << std::endl;
    start = clock();
    vector_stresstest();
    end = clock();
    std::cout << "Execution time : " << (double)(end - start)/CLOCKS_PER_SEC << std::endl;*/






    /****************************************************************
							    Map
	****************************************************************/


    /****************************************************************
							    Set
	****************************************************************/

    return 0;
}