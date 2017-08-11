#include <include/data.h>
#include <util/util.h>

void sub_quick_sort(int data[], int size, int d)
{
    // d最小为1，此层循环只做一次，相当于插入排序
    for (int i = 0; i < d; ++i) {
        // 从i+d，即序列中的第二个元素开始
        for (int j = i+d; j < size; j+=d) {
            int target = data[j];
            while (j >= i+d && data[j-d] > target) {
                data[j] = data[j-d];
                j -= d;
            }
            data[j] = target;
        }
    }
}

/*
    希尔排序
 */

void shell_sort(int data[], int size)
{
     //   sub_quick_sort(data, size, 1);
      //  return;
    for (int d = size / 2; d > 0; d/=2) {
        sub_quick_sort(data, size, d);
    }
}

int main()
{
    init_data();

    print_data("Before sort: ", test_data, TEST_DATA_SIZE);

    shell_sort(test_data, TEST_DATA_SIZE);

    print_data("After sort: ", test_data, TEST_DATA_SIZE);

    return 0;
}
