#ifndef __SKIP_LIST_H__
#define __SKIP_LIST_H__

#include <stddef.h>
#include "random.h"

#define DEBUG 

const int MAX_LEVEL = 16;

typedef int KeyType;
typedef int ValueType;

typedef struct node_s node_t;
struct node_s {
    KeyType key;
    ValueType value;
    node_t* forward[1];
};

typedef struct skiplist_s skiplist_t;
struct skiplist_s {
    int level;
    node_t* header;
};

class SkipList {
    public:
        SkipList() : _rnd (0xdeadbeef) {
            create();
        }

        ~SkipList() {
            destroy();
        }

        bool search(const KeyType& key, ValueType& value);

        bool insert(const KeyType& key, ValueType& value);

        bool remove(const KeyType& key, ValueType& value);

        int size() const {
            return _size;
        }

        int get_current_level();

        void show_graph();

    private:

        void create();

        void destroy();

        void create_node_with_level(const int level, node_t*& node);

        int get_rand_level();

    private:
        skiplist_t* _list;
        node_t* _nil;
        size_t _size;
        Random _rnd;
};

#endif
