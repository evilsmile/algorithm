#include <include/data.h>
#include <util/util.h>

/*
   插入排序
   保证前面有序
 */
void insert(int data[], int size)
{
    if (check(data, size))
    {
        return;
    }

    for (int i = 1; i < size; ++i) 
    {
        int j = i;
        int tmp = data[i];
        while (j > 0 && data[j - 1] > tmp) 
        {
            // 比data[i]位置的数据大则后移
            data[j] = data[j-1];
            --j;
        }
        data[j] = tmp;
    }
}


int main()
{
    init_data();

    print_data("Before sort: ", test_data, TEST_DATA_SIZE);

    insert(test_data, TEST_DATA_SIZE);

    print_data("After sort: ", test_data, TEST_DATA_SIZE);

    return 0;
}
