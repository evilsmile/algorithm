#ifndef __CHOICE_H__
#define __CHOICE_H__

#include <string>

const static unsigned int MAX_SELECT_CNT = ~0;

class Choice {
    public:
        Choice(const std::string& name, int weight, unsigned int maxselect_cnt = MAX_SELECT_CNT);

        std::string name;
        int weight;
        int cur_weight;
        int effective_weight;
        unsigned int maxselect_cnt;
        unsigned int curselect_cnt;

        class Sort {
        public:
            bool operator()(const Choice&l, const Choice& r);
        };
};

#endif
