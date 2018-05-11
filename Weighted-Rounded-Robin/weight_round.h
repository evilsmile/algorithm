#ifndef __WEIGHT_ROUND_H__
#define __WEIGHT_ROUND_H__

#include <string>
#include <vector>
#include "Choice.h"

class WeightSort {
public:
    WeightSort(std::vector<Choice>& choices)
        : _choices(choices)
    {
    }

    std::string do_weight_round_choice();

private:
    std::vector<Choice>& _choices;
};


#endif
