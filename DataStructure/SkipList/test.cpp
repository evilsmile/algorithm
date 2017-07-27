#include "skiplist.h"
#include <iostream>

static const int TEST_NODES_NUM = 20;

int main(int argc, char *argv[])
{
    std::cout << "test skiplist ... " << std::endl;

    SkipList slist;

    int value;
    for (int i = 0; i < TEST_NODES_NUM; ++i) {
        value = i + 10;
        slist.insert(i, value);
    }

    slist.show_graph();

    std::cout << "The number of elements in skiplist: " << slist.size() << std::endl;

    if (slist.size() != TEST_NODES_NUM) {
        std::cerr << "insert failed." << std::endl;
    } else {
        std::cout << "Insert succ." << std::endl;
    }

    for (int i = 0; i < TEST_NODES_NUM; ++i) {
        if (slist.search(i, value)) {
            std::cout << "search " << i << " succ. get value: " << value << std::endl;
        } else {
            std::cerr << "search " << i << " failed." << std::endl;
        }
    }

    int rm_key = 4;
    if (slist.remove(rm_key, value)) {
        std::cout << "delete " << rm_key << " succ. get ret value: " << value << std::endl;
    } else {
        std::cout << "delete " << rm_key << " failed." << std::endl;
    }
    slist.show_graph();

    std::cout << "test finished." << std::endl;

    return 0;
}
