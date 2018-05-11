#include <algorithm>
#include <string>
#include <vector>
#include "weight_round.h"
#include <stdio.h>

std::string WeightSort::do_weight_round_choice()
{
    int total = 0;

    for (size_t i = 0; i < _choices.size(); ++i) {
        /*
         * 每个后端peer都有三个权重变量，先解释下它们的含义。
         * (1) weight
         * 配置文件中指定的该后端的权重，这个值是固定不变的。
         * (2) effective_weight
         * 后端的有效权重，初始值为weight。
         * 在释放后端时，如果发现和后端的通信过程中发生了错误，就减小effective_weight。
         * 此后有新的请求过来时，在选取后端的过程中，再逐步增加effective_weight，最终又恢复到weight。
         * 之所以增加这个字段，是为了当后端发生错误时，降低其权重。
         * (3) current_weight
         * 后端目前的权重，一开始为0，之后会动态调整。那么是怎么个动态调整呢？
         * 每次选取后端时，会遍历集群中所有后端，对于每个后端，让它的current_weight增加它的effective_weight，
         * 同时累加所有后端的effective_weight，保存为total。
         * 如果该后端的current_weight是最大的，就选定这个后端，然后把它的current_weight减去total。
         * 如果该后端没有被选定，那么current_weight不用减小。
         *  
         *  弄清了三个weight字段的含义后，加权轮询算法可描述为：
         *  1. 对于每个请求，遍历集群中的所有可用后端，对于每个后端peer执行：
         *      peer->current_weight += peer->effecitve_weight。
         *      同时累加所有peer的effective_weight，保存为total。
         *  2. 从集群中选出current_weight最大的peer，作为本次选定的后端。
         *  3. 对于本次选定的后端，执行：peer->current_weight -= total。
         */

        _choices[i].cur_weight += _choices[i].effective_weight;
        total += _choices[i].effective_weight;
    }
    std::sort(_choices.begin(), _choices.end(), Choice::Sort());

    for (size_t i = 0; i < _choices.size(); ++i) {
        if (_choices[i].curselect_cnt++ <= _choices[i].maxselect_cnt)
        {
            _choices[i].cur_weight -= total;
            return _choices[i].name;
        }
    }

    return "";
}
