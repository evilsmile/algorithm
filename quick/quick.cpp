#include <include/data.h>
#include <util/util.h>

/*
    快速排序
 */

int _quick(int data[], int left, int right)
{
    if (left == right) 
    {
        return left;
    }

    int l = left;
    int r = right;
    int target = data[left];

    while (l < r) 
    {
        // 不要加>=
        while(r > l && data[r] > target) { r--;}
        // 因为左边是从left开始，l与left开始是重合的，所以要加<=
        while(l < r && data[l] <= target) { l++;}

        // 相遇，则一轮拆分放置已经结束，把target放到重心位置,把原重心位置放到最左边
        if (l == r) 
        {
            data[left] = data[l];
            data[l] = target;
            break;
        } else {
            // 否则交换一大一小
            swap(data[r], data[l]);
        }
    }

    return l;
}

void quick(int data[], int left, int right)
{
    if (left >= right) {
        return;
    }

    int pivot = _quick(data, left, right);

    quick(data, left, pivot - 1);
    quick(data, pivot + 1, right);

}

int main()
{
    print_data("Before sort: ", test_data, TEST_DATA_SIZE);

    quick(test_data, 0, TEST_DATA_SIZE - 1);

    print_data("After sort: ", test_data, TEST_DATA_SIZE);

    return 0;
}
