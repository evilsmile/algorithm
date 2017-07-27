#include "skiplist.h"
#include "time.h"
#include <assert.h>
#include <stdlib.h>
#include <string>
#include <iostream>

static const int INVALID_KEY = 0x7fffffff;

void debug(const std::string& msg)
{
#ifdef DEBUG
    std::cout << msg << std::endl;
#endif
}

void SkipList::create()
{
    // create nil node
    create_node_with_level(0, _nil);
    _nil->key = INVALID_KEY;

    // create skiplist
    _list = (skiplist_t*)malloc(sizeof(skiplist_t));
    // start from level-0
    _list->level = 0;
    // alloc header memory
    create_node_with_level(MAX_LEVEL, _list->header);
    // init header forward[] to nil
    for (int i = 0; i < MAX_LEVEL; ++i) {
        _list->header->forward[i] = _nil;
    }

    _size = 0;
}

void SkipList::create_node_with_level(const int level, node_t*&node) 
{
    int total_size = sizeof(node_t) + level * sizeof(node_t*);

    node = (node_t*)malloc(total_size);
    assert(node != NULL);
}

void SkipList::destroy()
{
    node_t* p = _list->header;
    node_t *q;
    while (p) {
        q = p->forward[0];
        free(p);
        p = q;
    }

    free(p);
    free(_list);
}

bool SkipList::insert(const KeyType& key, ValueType& value)
{
    node_t* update[MAX_LEVEL];
    node_t* node = _list->header;

    // 找到每层中的插入点
    for (int i = _list->level; i >= 0; --i) {
        while (node->forward[i]->key < key) {
            node = node->forward[i];
        }

        // 存储了每一层在其之后插入的结点
        update[i] = node;
    }

    // 检查第一层，后面的结点key重复?
    // 此时node是level0的插入点, node->forward[0]的level0的后结点
    node = node->forward[0];
    if (node->key == key) {
        node->value = value;
        return false;
    } 

    // 新生成一个层次
    int level = get_rand_level();
    // 如果比现在有层次高，则加一层
    if (level > _list->level) {
        level = ++_list->level;
        update[level] = _list->header;
    }

    // 生成新结点
    node_t* new_node;
    create_node_with_level(level, new_node);
    new_node->key = key;
    new_node->value = value;

    // 更新随机的level层以下的所有插入结点
    for (int i = level; i >= 0; --i) {
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }

    ++_size;

    return true;
}
bool SkipList::search(const KeyType& key, ValueType& value)
{
    node_t* node = _list->header;
    bool find = false;
    // 从最上层找
    for (int i = _list->level; !find && i >= 0; --i) {
        // 如果上一层找到了关键位置，则下一层从该结点开始，从下一个forward找
        while (node->forward[i]->key < key) {
            // forward里的i就是对应层数的结点
            node = node->forward[i];
        }
        // 找到了KEY!
        if (node->forward[i]->key == key) {
            find = true;
            node = node->forward[i];
        }
    }

    if (!find) {
        return false;
    }
     
    value = node->value;
    return true;
}

bool SkipList::remove(const KeyType& key, ValueType& value)
{
    node_t* update[MAX_LEVEL];
    int i;

    node_t* node = _list->header;
    for (i = _list->level; i >= 0; --i) {
        while(node->forward[i]->key < key) {
            node = node->forward[i];
        }

        update[i] = node;
    }

    node = node->forward[0];
    if (node->key != key) {
        return false;
    }

    value = node->value;
    for (i = 0; i <= _list->level; ++i) {
        if (update[i]->forward[i] != node) {
            break;
        }
        update[i]->forward[i] = node->forward[i];
    }

    free(node);

    while (_list->level > 0 
            && _list->header->forward[_list->level] == _nil) {
        --_list->level;
    }

    --_size;

    return true;
}

void SkipList::show_graph()
{
    node_t* node;
    for (int i = 0; i < _list->level; ++i) {
        std::cout << "Level[" << i << "]: ";
        node = _list->header->forward[i];

        std::cout << node->key;
        node = node->forward[i];
        while (node->key != INVALID_KEY) {
            std::cout << "->" << node->key;
            node = node->forward[i];
        }
        std::cout << std::endl;
    }
}

int SkipList::get_rand_level()
{
    int level = static_cast<int>(_rnd.uniform(MAX_LEVEL));
    if (level == 0) {
        level = 1;
    }

    return level;
}

int SkipList::get_current_level()
{
    return _list->level;
}
