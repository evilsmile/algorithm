#include "../data.h"

/*
    选择排序
    全局地选出最大的，然后与末端位置交换
 */

void select(int data[], int size)
{
    if (check(data, size))
    {
        return;
    }

    for (int i = size - 1; i >= 0; --i) 
    {
        int max_i = i;
        for (int j = 0; j < i; ++j) 
        {
            if (data[j] > data[max_i]) 
            {
                max_i = j;
            }
        }
        if (i != max_i) 
        {
           swap(data[max_i], data[i]);
        }
    }
}

int main()
{
    print_data("Before sort: ", test_data, TEST_DATA_SIZE);

    select(test_data, TEST_DATA_SIZE);

    print_data("After sort: ", test_data, TEST_DATA_SIZE);

    return 0;
}
