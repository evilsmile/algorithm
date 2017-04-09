#ifndef __TEST_H__
#define __TEST_H__

#include <iostream>
#include <string>

int test_data[] = {9, 20, 30, 14, 22, 88, 443, 82, 2302, 223, 120};

#define TEST_DATA_SIZE sizeof(test_data)/sizeof(test_data[0])

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

#endif
