#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "Choice.h"

extern void do_weight_round_choice(std::vector<Choice>& choices);

void print_choice(const std::vector<Choice>& choices)
{
    std::cout << "Weight config: " << std::endl;
    for (size_t i = 0; i < choices.size(); ++i) {
        std::cout << "[" << choices[i].name << "]:" << choices[i].weight << ", ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<Choice> choices;
    typedef std::map<std::string, int> choices_cnt_t;
    choices_cnt_t choices_cnt;

#define CHOICES_NUM 3
    for (int i = 0; i < CHOICES_NUM; ++i) {
        char c = 'a'+i;
        std::string name(&c, 1);
        choices.push_back(Choice(name, 1<<(CHOICES_NUM-i)));
        choices_cnt[name] = 0;
    }

    print_choice(choices);

    std::cout << "-----------------------------------------------" << std::endl;

#define TEST_CNT 10000
    for (int i = 0; i < TEST_CNT; ++i) {
        do_weight_round_choice(choices);
        print_choice(choices);
        choices_cnt[choices[0].name]++;
    }

    for (choices_cnt_t::iterator iter = choices_cnt.begin(); iter != choices_cnt.end(); ++iter) {
        std::cout << iter->first.c_str() << " : " << iter->second << std::endl;
    }

    return 0;
}
