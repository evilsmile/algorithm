#include <vector>
#include <string>

#include <iostream>

namespace Util {

void pr(std::vector<int>& v)
{
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

}
