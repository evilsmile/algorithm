#include "util.h"
#include <iostream>

void print_data(const std::string& headmsg, int data[], int size)
{
    std::cout << headmsg;
    for(int i = 0; i < size; ++i) 
    {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

void swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

int check(int data[], int size)
{
    if (data == NULL) 
    {
        std::cerr << "data can't be NULL!" << std::endl;
        return -1;
    }
    if (size <= 0)
    {
        std::cerr << "size must be greater than 0!" << std::endl;
        return -1;
    }

    return 0;
}


