#include <string>

class Choice {
    public:
        Choice(const std::string& name, int weight) ;

        std::string name;
        int weight;
        int cur_weight;
        int effective_weight;

        class Sort {
        public:
            bool operator()(const Choice&l, const Choice& r);
        };
};
