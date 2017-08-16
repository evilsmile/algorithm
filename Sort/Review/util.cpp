#include <vector>
#include <string>

#include <iostream>

namespace Util {

void pr(const std::string& header_msg, std::vector<int>& v)
{
    std::cout << header_msg << " ";
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

}
