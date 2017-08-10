#include <iostream>

#include "smart_ptr.hpp"

int main() 
{
    // constructor
    smart_ptr<int> pi1(new int(42));
    std::cout << "ref1: " << pi1.count_ref() << std::endl;
    // copy
    smart_ptr<int> pi2(pi1);
    std::cout << "ref1: " << pi2.count_ref() << std::endl;

    // 

    smart_ptr<int> pi3(new int(33));
    // operator=
    pi2 = pi3;
    std::cout << "ref1: " << pi1.count_ref() << std::endl;
    std::cout << "ref2: " << pi2.count_ref() << std::endl;


    std::cout << "REF1 NUM: " << *pi1.get() << std::endl;
    std::cout << "REF2 NUM: " << *pi2.get() << std::endl;
    std::cout << "REF3 NUM: " << *pi3.get() << std::endl;
    return 0;
}
