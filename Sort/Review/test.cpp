#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "test.h"
#include "util.h"

#define ERR(msg) \
        std::cerr << msg" [" << strerror(errno) << "]" << std::endl;

Test::Test() : _rand_dev_fd(-1) {}

Test::~Test()
{
    if (_rand_dev_fd > 0) {
        close(_rand_dev_fd);
    }
}

int Test::_get_randint(int range)
{
    bool neg = false;
    if (range < 0) {
        neg = true;
        range = -range;
    }

    if (_rand_dev_fd < 0) {
        _rand_dev_fd = open("/dev/urandom", O_RDONLY);
        if (_rand_dev_fd < 0) {
            ERR("open /dev/random failed.");
            return -1;
        }
    }

    int r = -1;
    if (read(_rand_dev_fd, (char*)&r, sizeof(r)) != sizeof(r)) {
        ERR("read random failed.");
        return r;
    }

    if (r < 0) { 
        r = -r;
    }

    r = r % range;
    return neg?-r:r;
}

void Test::_init_data(array_t& data, int size, int max)
{
    data.clear();
    for (int i = 0; i < size; ++i) {
        data.push_back(_get_randint(max));
    }
}

bool Test::_check_sort(array_t& data)
{
    for (int i = 1; i < data.size(); ++i) {
        if (data[i] < data[i-1]) {
            std::cout << data[i-1] << " " << data[i] << " check failed!!!!!!!!!!!" << std::endl;
            return false;
        }
    }

    return true;
}
void Test::_calc_speed(array_t& data, SortAlgorithm& alg, int repeat_sort_cnt)
{
    clock_t start, end;
    start = clock();
    for (int i = 0 ; i < repeat_sort_cnt; ++i) {
        array_t data_tmp = data;
        alg.sort(data_tmp);
    }
    end = clock();

    _all_time_record[alg.getName()] = (double)(end - start)/CLOCKS_PER_SEC;
}

void Test::speed_cmp(int array_size, int max, int repeat_sort_cnt)
{
    array_t data;

    _init_data(data, array_size, max);

//    Util::pr(data);

    SortAlgorithm alg;
    alg.set_algrithm(SortAlgorithm::BUBBLE);
    _calc_speed(data, alg, repeat_sort_cnt);
    alg.set_algrithm(SortAlgorithm::SELECT);
    _calc_speed(data, alg, repeat_sort_cnt );
    alg.set_algrithm(SortAlgorithm::INSERT);
    _calc_speed(data, alg, repeat_sort_cnt);
    alg.set_algrithm(SortAlgorithm::QUICK);
    _calc_speed(data, alg, repeat_sort_cnt);
    alg.set_algrithm(SortAlgorithm::SHELL);
    _calc_speed(data, alg, repeat_sort_cnt);
    alg.set_algrithm(SortAlgorithm::HEAP);
    _calc_speed(data, alg, repeat_sort_cnt);

    for (std::map<std::string, double>::iterator iter = _all_time_record.begin();
            iter != _all_time_record.end();
            ++iter) {
        printf("%s : %.2f\n", iter->first.c_str(), iter->second);
    }
}

void Test::valid_sort_result(int array_size, int max, int repeat_sort_cnt)
{
    array_t data;

    // 设置需要测试的mask
    int test_mask = 0x0;
    test_mask &= ~(1 << SortAlgorithm::SELECT);
    test_mask |= (1 << SortAlgorithm::SELECT);

    SortAlgorithm alg;
    for (int alg_type = SortAlgorithm::BUBBLE; alg_type <= SortAlgorithm::HEAP; alg_type++) {

        if ((test_mask & (1 << alg_type)) == 0) {
            continue;
        }

        bool test_succ = true;
        alg.set_algrithm(static_cast<SortAlgorithm::SORT_ALG>(alg_type));

        for (int i = 0 ; i < repeat_sort_cnt; ++i) {
            _init_data(data, array_size, max);
            std::cout << "Before: " << std::endl;
            Util::pr(data);

            std::cout << "After: " << std::endl;
            alg.sort(data);
            Util::pr(data);
            if (!_check_sort(data)) {
                test_succ = false;
                break;
            }
        }

        std::cout << "\n====  Test (" << alg.getName() << ") result: [" << (test_succ?"SUCC":"FAILED") << "] ===\n" << std::endl;
    }
}


int main()
{
    Test test;

//    test.valid_sort_result(11, 1000, 10000);

    test.speed_cmp(100000, 100000, 1);

    return 0;
}
