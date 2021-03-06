#include <stdio.h>

#include "algorithm_review.h"
#include "util.h"

//#define DEBUG 

int SortAlgorithm::ALL_ALGS = BUBBLE | SELECT | INSERT | QUICK | SHELL | HEAP;
/////////////////////////////////////////////////////////////////////
void IAlgorithm::_swap(int& a, int& b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}

/////////////////////////////////////////////////////////////////////
void BubbleSort::sort(array_t& data)
{
    int size = data.size();

    bool _swaped = true;
    for (int i = size - 1; i >= 0; --i) {
        if (!_swaped) {
            break;
        }
        _swaped = false;
        for (int j = 1; j <= i; ++j) {
            if (data[j-1] > data[j]) {
                _swaped = true;
                _swap(data[j-1], data[j]);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////
void SelectSort::sort(array_t& data)
{
    int size = data.size();
#if 1
    // 因为每次循环后首尾两端存放的就是最大和最小值了，然后再对中间部分排序
    // i可以看作是已经排好序的首尾对个数
    for (int i = 0; i < size/2; ++i) {
        // 默认初始将最大值定在尾端，最小值定在头端
        int max_i = size - i - 1;
        int min_i = i;
        for (int j = i; j < size - i; ++j) {
            if (data[j] > data[max_i]) {
                max_i = j;
            }
            if (data[j] < data[min_i]) {
                min_i = j;
            }
        }
        // 如果最大值不在尾端，则交换它到尾端
        if (max_i != size-i-1) {
            _swap(data[size-i-1], data[max_i]);
            // 如果原来的尾端是最小的，经过上面的交换现在被放到了max_i处了，需要重定向
            if (min_i == size-i-1) {
                min_i = max_i;
            }
        }

        // 如果最小值指向的不是头部，
        // 且不是尾部(如果头部和尾部刚好是最大和最小值,则min_i指向尾部，这时上面的交换已经把首尾做过交换了，不需要再交换)，
        // 才交换
        if (min_i != i && min_i != size-i-1) {
            _swap(data[i], data[min_i]);
        }
#else
    for (int i = size - 1; i >= 0; --i) {
        int max_i = i;
        for (int j = 0; j < i; ++j) {
            if (data[j] > data[max_i]) {
                max_i = j;
            }
        }
        // 如果最大值不在尾端，则交换它到尾端
        if (max_i != i) {
            _swap(data[i], data[max_i]);
        }
#endif

#ifdef DEBUG
        Util::pr("", data);
#endif
    }
}

/////////////////////////////////////////////////////////////////////
void InsertSort::sort(array_t& data)
{
    int size = data.size();
    for (int i = 1; i < size; ++i) {
        int target = data[i];
        int j = i;
        while (j > 0 && data[j-1] > target) {
            data[j] = data[j-1];
            j--;
        }
        data[j] = target;
    }
}

/////////////////////////////////////////////////////////////////////
int QuickSort::_parition(array_t& data, int left, int right)
{
    if (left >= right) {
        return left;
    }

    int l = left;
    int r = right;
    int target = data[left];

    while (l < r) {
        while (l < r && data[r] > target) { r--; }
        while (l < r && data[l] <= target) { ++l; }

        if (l == r) {
            data[left] = data[l];
            data[l] = target;
            break;
        }
        _swap(data[r], data[l]);
    }

    return l;
};

void QuickSort::_quick(array_t& data, int left, int right)
{
    if (left >= right) {
        return ;
    }

    int pivot = _parition(data, left, right);

    _quick(data, left, pivot - 1);
    _quick(data, pivot+1, right);
}

/////////////////////////////////////////////////////////////////////
void QuickSort::sort(array_t& data)
{
    _quick(data, 0, data.size()-1);
}

/////////////////////////////////////////////////////////////////////
void ShellSort::sort(array_t& data)
{
    int size = data.size();

    for (int d = size>>1; d > 0; --d) {
        for (int i = d; i < size; i+=d) {
            int j = i;
            int target = data[i];
            while (j >= d && data[j-d] > target) {
                data[j] = data[j-d];
                j -= d;
            }
            data[j] = target;
        }
    }
}

/////////////////////////////////////////////////////////////////////
void HeapSort::_heap_adjust(array_t& data, int start_father, int size)
{
    int tmp  = data[start_father];
    int cur_father = start_father;

	//左孩子结点的位置。(i+1 为当前调整结点的右孩子结点的位置)
    int max_child = 2*cur_father+1; 
    while (true) {
		// 找更大的子结点
        if(max_child+1 < size && data[max_child]<data[max_child+1]) { 
            ++max_child ;
        }

        // 越界，直接退出
        if (max_child >= size) {
            return ;
        }

		// 如果较大的子结点大于父结点
        if(data[cur_father] < data[max_child]) { 
			// 那么把较大的子结点往上移动，替换它的父结点
            data[cur_father] = data[max_child]; 
			// 移动了子节点，可能会影响该子节点的子节点，再往下调整
            cur_father = max_child;       
            max_child = 2*cur_father+1;
        } 	
		// 如果当前待调整结点大于它的左右孩子，则不需要调整，直接退出 
		else {   
             return;
        }
    }
    // 当前待调整的结点放到比其大的孩子结点位置上
    data[cur_father] = tmp;         
}


/**
 * 初始堆进行调整
 * 将data[0..size-1]建成堆
 * 调整完之后第一个元素是序列的最小的元素
 */
void HeapSort::_building_heap(array_t& data, int size)
{
    //最后一个有孩子的节点的位置 i=  (size -1) / 2
    for (int i = (size -1) / 2 ; i >= 0; --i) {
        // 如果父结点调整了以后，会再往子结点调整，大大提高效率
        _heap_adjust(data, i, size);
    }
}

/**
 * 堆排序算法
 */
void HeapSort::sort(array_t& data)
{
	int size = data.size();
    //初始堆
    _building_heap(data, size);
    //从最后一个元素开始对序列进行调整
    for (int i = size - 1; i > 0; --i)
    {
        //交换堆顶元素data[0]和堆中最后一个元素
        _swap(data[0], data[i]);
        //每次交换堆顶元素和堆中最后一个元素之后，都要对堆进行调整
        _heap_adjust(data, 0, i);
  }
}

/////////////////////////////////////////////////////////////////////
SortAlgorithm::SortAlgorithm()
    : _alg_type(QUICK), _alg_impl(new QuickSort)// default 'quick sort'
{

}

SortAlgorithm::SortAlgorithm(SORT_ALG alg_type)
{
    switch(alg_type) {
        case BUBBLE:
            _alg_impl.reset(new BubbleSort);
            break;
        case SELECT:
            _alg_impl.reset(new SelectSort);
            break;
        case INSERT:
            _alg_impl.reset(new InsertSort);
            break;
        case QUICK:
            _alg_impl.reset(new QuickSort);
            break;
        case SHELL:
            _alg_impl.reset(new ShellSort);
            break;
        case HEAP:
            _alg_impl.reset(new HeapSort);
            break;
        default:
            return;
    }
    _alg_type = alg_type;
}

std::string SortAlgorithm::getName() 
{
    if (_alg_impl.get() != NULL) {
        return _alg_impl->get_name();
    }

    return "";
}

void SortAlgorithm::sort(array_t& data)
{
    if (_alg_impl.get() != NULL) {
        _alg_impl->sort(data);    
        return;
    }
}

void SortAlgorithm::set_algrithm(SORT_ALG alg_type)
{
    if (alg_type == _alg_type) {
        return;
    }
    switch(alg_type) {
        case BUBBLE:
            _alg_impl.reset(new BubbleSort);
            break;
        case SELECT:
            _alg_impl.reset(new SelectSort);
            break;
        case INSERT:
            _alg_impl.reset(new InsertSort);
            break;
        case QUICK:
            _alg_impl.reset(new QuickSort);
            break;
        case SHELL:
            _alg_impl.reset(new ShellSort);
            break;
        case HEAP:
            _alg_impl.reset(new HeapSort);
            break;
        default:
            return;
    }
    _alg_type = alg_type;
}
