#include <string>

#include "Choice.h"

Choice::Choice(const std::string& name, int weight, unsigned int maxselect_cnt)
    : name(name), 
      weight(weight),
      cur_weight(0),
      effective_weight(weight),
      maxselect_cnt(maxselect_cnt),
      curselect_cnt(0)
{
}

bool Choice::Sort::operator()(const Choice&l, const Choice& r) {
    return l.cur_weight > r.cur_weight;
}
