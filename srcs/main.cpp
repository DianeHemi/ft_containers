#include <iostream>
#include <ctime>
#include "test_stack.cpp"
#include "test_vector.cpp"
#include "test_map.cpp"

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

    std::cout << "\033[1;32m\n--- Modifiers --- \033[0m" << std::endl;
    start = clock();
    vector_modifiers();
    end = clock();
    std::cout << "Execution time : " << (double)(end - start)/CLOCKS_PER_SEC << std::endl;

    std::cout << "\033[1;32m\n--- Access --- \033[0m" << std::endl;
    start = clock();
    vector_access();
    end = clock();
    std::cout << "Execution time : " << (double)(end - start)/CLOCKS_PER_SEC << std::endl;

    std::cout << "\033[1;32m\n--- Iterators --- \033[0m" << std::endl;
    start = clock();
    vector_iterator();
    end = clock();
    std::cout << "Execution time : " << (double)(end - start)/CLOCKS_PER_SEC << std::endl;

    std::cout << "\033[1;32m\n--- Reverse iterators --- \033[0m" << std::endl;
    start = clock();
    vector_reverse_iterator();
    end = clock();
    std::cout << "Execution time : " << (double)(end - start)/CLOCKS_PER_SEC << std::endl;

    std::cout << "\033[1;32m\n--- Relational operators --- \033[0m" << std::endl;
    start = clock();
    vector_relational_ope();
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
    std::cout << "\n\nMAP" << std::endl;

    std::cout << "\033[1;32m\n--- Modifiers --- \033[0m" << std::endl;
    start = clock();
    map_modifiers();
    end = clock();
    std::cout << "Execution time : " << (double)(end - start)/CLOCKS_PER_SEC << std::endl;

    std::cout << "\033[1;32m\n--- Iterators --- \033[0m" << std::endl;
    start = clock();
    map_iterators();
    end = clock();
    std::cout << "Execution time : " << (double)(end - start)/CLOCKS_PER_SEC << std::endl;

    /*std::cout << "\033[1;32m\n--- Reverse iterators --- \033[0m" << std::endl;
    start = clock();
    map_reverse_iterators();
    end = clock();
    std::cout << "Execution time : " << (double)(end - start)/CLOCKS_PER_SEC << std::endl;

    std::cout << "\033[1;32m\n--- Relational operators --- \033[0m" << std::endl;
    start = clock();
    map_relational_ope();
    end = clock();
    std::cout << "Execution time : " << (double)(end - start)/CLOCKS_PER_SEC << std::endl;
    
    std::cout << "\033[1;32m\n--- Stress test --- \033[0m" << std::endl;
    start = clock();
    map_stresstest();
    end = clock();
    std::cout << "Execution time : " << (double)(end - start)/CLOCKS_PER_SEC << std::endl;*/

    /****************************************************************
							    Set
	****************************************************************/

    return 0;
}