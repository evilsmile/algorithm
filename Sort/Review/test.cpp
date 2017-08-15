#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "test.h"

#define ERR(msg) \
        std::cerr << msg" [" << strerror(errno) << "]" << std::endl;

namespace Util {

void pr(std::vector<int>& v)
{
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}


int get_randint(int range)
{
    bool neg = false;
    if (range < 0) {
        neg = true;
        range = -range;
    }

    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        ERR("open /dev/random failed.");
        return -1;
    }

    int r = -1;
    if (read(fd, (char*)&r, sizeof(r)) != sizeof(r)) {
        ERR("read random failed.");
        close(fd);
        return r;
    }

    if (r < 0) { 
        r = -r;
    }

    close(fd);

    r = r % range;
    return neg?-r:r;
}

void init_data(array_t& data, int size, int max)
{
    data.clear();
    for (int i = 0; i < size; ++i) {
        data.push_back(get_randint(max));
    }
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

    Util::init_data(data, array_size, max);

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

    bool test_succ = true;
    SortAlgorithm alg;
    for (int alg_type = SortAlgorithm::BUBBLE; alg_type <= SortAlgorithm::HEAP; alg_type++) {

        alg.set_algrithm(static_cast<SortAlgorithm::SORT_ALG>(alg_type));

        for (int i = 0 ; i < repeat_sort_cnt; ++i) {
            Util::init_data(data, array_size, max);
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

//    test.valid_sort_result(10000, 1000, 1);

    test.speed_cmp(100000, 100000, 1);

    return 0;
}
