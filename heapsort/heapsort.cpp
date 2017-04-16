#include <include/data.h>
#include <util/util.h>

/*
    调整data，大根堆
 */
void heap_adjust(int data[], int size)
{
    // 从一半的位置开始调整
    // 如果size为3，则
    //    0
    //   / \
    //  1  2
    // 从0开始调，为3/2-1，即size/2-1
    // 左孩子是1,即i+1，右孩子是left_c+1
    for (int i = size / 2 - 1; i >= 0; --i) {
        int left_c = i * 2 + 1;
        int right_c = left_c + 1;

        // 保证结点是包括2个子结点中最大的
        if (left_c < size && data[i] < data[left_c]) {
            swap(data[i], data[left_c]);
        }
        if (right_c < size && data[i] < data[right_c]) {
            swap(data[i], data[right_c]);
        }
    }
}

/*
    堆排序
 */

void heap_sort(int data[], int size)
{
    // 每次循环后 data[s-1]是最大元素，对[0, s-1)序列再排序
    for (int s = size; s > 0; --s) {
        heap_adjust(data, s);
        // 堆顶元素交换到末端
        swap(data[0], data[s - 1]);
    }
}

int main()
{
    print_data("Before sort: ", test_data, TEST_DATA_SIZE);

    heap_sort(test_data, TEST_DATA_SIZE);

    print_data("After sort: ", test_data, TEST_DATA_SIZE);

    return 0;
}
