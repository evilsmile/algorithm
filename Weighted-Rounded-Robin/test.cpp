#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "Choice.h"
#include "weight_round.h"

extern void do_weight_round_choice(std::vector<Choice>& choices);

std::vector<Choice> choices;
typedef std::map<std::string, int> choices_cnt_t;

choices_cnt_t choices_cnt;

void print_choice(const std::vector<Choice>& choices)
{
    std::cout << "Weight config: " << std::endl;
    for (size_t i = 0; i < choices.size(); ++i) {
        std::cout << "[" << choices[i].name << "]:" << choices[i].weight << ", " << choices[i].cur_weight << " | ";
    }
    std::cout << std::endl;
}

void fill_data()
{
#define CHOICES_NUM 3
    for (int i = 0; i < CHOICES_NUM; ++i) {
        char c = 'a'+i;
        std::string name(&c, 1);
        choices.push_back(Choice(name, 1<<(CHOICES_NUM-i)));
        choices_cnt[name] = 0;
    }
}

#define FILL_DATA_BEGIN(NAME, WEIGHT_CFG, MAXSEL, SIZE) \
    int fill_data_idx = 0;   \
    static std::string NAME[SIZE];  \
    std::string* _p_name_ = NAME;  \
    static int WEIGHT_CFG[SIZE] = {0};   \
    int * _p_weight_cfg_ = WEIGHT_CFG;  \
    static unsigned int MAXSEL[SIZE] = {0} ;  \
    unsigned int * _p_max_sel_ = MAXSEL 

#define FILL_DATA(d_name, d_weight, d_maxsel) \
    _p_name_[fill_data_idx] = d_name; \
    _p_weight_cfg_[fill_data_idx] = d_weight; \
    _p_max_sel_[fill_data_idx] = d_maxsel; \
    fill_data_idx++

void fill_data2()
{
    FILL_DATA_BEGIN(names, cfg_weights, maxselect_cnts, 10);
    FILL_DATA("A", 18, MAX_SELECT_CNT);
    FILL_DATA("B", 18, MAX_SELECT_CNT);
    FILL_DATA("C", 0, MAX_SELECT_CNT);
    FILL_DATA("D", 0, MAX_SELECT_CNT);
    FILL_DATA("E", 0, MAX_SELECT_CNT);
    FILL_DATA("F", 5128, 224);
    FILL_DATA("G", 100, 244);
    FILL_DATA("H", 100, 243);
    FILL_DATA("I", 100, 469);
    FILL_DATA("J", 100, 318);

    for (size_t i = 0; i < sizeof(names)/sizeof(names[0]); ++i) {
        choices.push_back(Choice(names[i], cfg_weights[i], maxselect_cnts[i]));
        choices_cnt[names[i]] = 0;
    }
}

int main()
{
//    fill_data();
    fill_data2();
    print_choice(choices);

    WeightSort ws(choices);

    std::cout << "-----------------------------------------------" << std::endl;

    const int TEST_CNT = 11522 + 224 + 244 + 243 + 469 + 318;
    std::string selectedName;
    for (int i = 0; i < TEST_CNT; ++i) {
         selectedName = ws.do_weight_round_choice();
        //print_choice(choices);
        choices_cnt[selectedName]++;
    }

    for (choices_cnt_t::iterator iter = choices_cnt.begin(); iter != choices_cnt.end(); ++iter) {
        std::cout << iter->first.c_str() << " : " << iter->second << std::endl;
    }

    return 0;
}
