#include "../data.h"

/*
   bubble 冒泡最大的冒到最右边
 */
void bubble_max(int data[], int size) 
{
    if (check(data, size))
    {
        return;
    }

    for (int i = 0; i < size; ++i)
    {
        // 从左往右冒泡，比较j和j-1，j的上限是size-i
        for (int j = 1; j < size - i; ++j) 
        {
            if (data[j-1] > data[j]) 
            {
                swap(data[j-1], data[j]);
            }
        }
    }
}

/*
   bubble 冒泡最小的冒到最左边
 */
void bubble_min(int data[], int size)
{
    if (check(data, size))
    {
        return;
    }


    for (int i = 0; i < size; ++i) 
    {
        // 从右往左冒泡，比较j和j-1，j的起始位置是size-1，下限是i
        for (int j = size - 1; j > i; --j) 
        {
            if (data[j-1] > data[j]) 
            {
               swap(data[j], data[j-1]); 
            }
        }
    }
}

int main()
{
    print_data("Before sort: ", test_data, TEST_DATA_SIZE);

    bubble_max(test_data, TEST_DATA_SIZE);
//  bubble_min(test_data, TEST_DATA_SIZE);

    print_data("After sort: ", test_data, TEST_DATA_SIZE);

    return 0;
}
