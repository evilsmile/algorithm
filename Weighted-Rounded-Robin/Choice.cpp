#include <string>

#include "Choice.h"

Choice::Choice(const std::string& name, int weight) 
    : name(name), 
      weight(weight),
      cur_weight(0),
      effective_weight(weight)
{
}

bool Choice::Sort::operator()(const Choice&l, const Choice& r) {
    return l.cur_weight > r.cur_weight;
}
