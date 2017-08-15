#ifndef __TEST_H__
#define __TEST_H__

#include <vector>
#include <map>

#include "algorithm_review.h"

class Test {
    public:
        void valid_sort_result(int array_size, int max, int repeat_sort_cnt);
        void speed_cmp(int array_size, int max, int repeat_sort_cnt);

    private:
        std::map<std::string, double> _all_time_record;

        void _calc_speed(array_t& data, SortAlgorithm&, int repeat_sort_cnt);
        bool _check_sort(array_t& data);
};


#endif
