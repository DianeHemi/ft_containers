#include "tests.hpp"
    
int main(void)
{
    /****************************************************************
							    Vector
	****************************************************************/
    std::cout << "#########################################" << std::endl;
    std::cout << "VECTOR" << std::endl;
    std::cout << "#########################################" << std::endl;

    std::cout << "\033[1;32m\n--- Modifiers --- \033[0m" << std::endl;
    vector_modifiers();

    std::cout << "\033[1;32m\n--- Access --- \033[0m" << std::endl;
    vector_access();

    std::cout << "\033[1;32m\n--- Iterators --- \033[0m" << std::endl;
    vector_iterator();

    std::cout << "\033[1;32m\n--- Reverse iterators --- \033[0m" << std::endl;
    vector_reverse_iterator();

    std::cout << "\033[1;32m\n--- Relational operators --- \033[0m" << std::endl;
    vector_relational_ope();

    /*std::cout << "\033[1;32m--- Stress test --- \033[0m" << std::endl;
    vector_stresstest();*/


    /****************************************************************
							    Stack
	****************************************************************/
    std::cout << "\n\n#########################################" << std::endl;
    std::cout << "STACK" << std::endl;
    std::cout << "#########################################" << std::endl;

    std::cout << "\033[1;32m--- Basic --- \033[0m" << std::endl;
    stack_basic_tests();

    std::cout << "\033[1;32m\n--- Relational operators --- \033[0m" << std::endl;
    stack_relational_test();

    std::cout << "\033[1;32m\n--- List compatibility --- \033[0m" << std::endl;
    stack_list_test();


    /****************************************************************
							    Map
	****************************************************************/
    std::cout << "\n\n#########################################" << std::endl;
    std::cout << "MAP" << std::endl;
    std::cout << "#########################################" << std::endl;

    std::cout << "\033[1;32m\n--- Modifiers --- \033[0m" << std::endl;
    map_modifiers();

    std::cout << "\033[1;32m\n--- Iterators --- \033[0m" << std::endl;
    map_iterators();

    std::cout << "\033[1;32m\n--- Iterators --- \033[0m" << std::endl;
    map_reverse_iterators();

    std::cout << "\033[1;32m\n--- Access --- \033[0m" << std::endl;
    map_access();

    std::cout << "\033[1;32m\n--- Operations --- \033[0m" << std::endl;
    map_operations();

    std::cout << "\033[1;32m\n--- Relational operators --- \033[0m" << std::endl;
    map_relational_ope();
    
    /*std::cout << "\033[1;32m\n--- Stress test --- \033[0m" << std::endl;
    map_stresstest();*/



    /****************************************************************
							    Set
	****************************************************************/
    std::cout << "\n\n#########################################" << std::endl;
    std::cout << "SET" << std::endl;
    std::cout << "#########################################" << std::endl;

    std::cout << "\033[1;32m\n--- Modifiers --- \033[0m" << std::endl;
    set_modifiers();

    std::cout << "\033[1;32m\n--- Iterators --- \033[0m" << std::endl;
    set_iterators();

    std::cout << "\033[1;32m\n--- Iterators --- \033[0m" << std::endl;
    set_reverse_iterators();

    std::cout << "\033[1;32m\n--- Operations --- \033[0m" << std::endl;
    set_operations();

    std::cout << "\033[1;32m\n--- Relational operators --- \033[0m" << std::endl;
    set_relational_ope();
    
    /*std::cout << "\033[1;32m\n--- Stress test --- \033[0m" << std::endl;
    set_stresstest();*/



    return 0;
    
}
