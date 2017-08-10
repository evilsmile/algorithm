#include <iostream>
#include <string>
#include <stdio.h>
#include <assert.h>

#define NDEBUG

int s2i(const std::string& s)
{
    int len = s.size();
    int value = 0;
    bool neg = false;
    if (s[0] == '-') {
        neg = true;
    }

    for (int i = neg?0:1; i < len; ++i) {
        if (s[i] >= '0' && s[i] <= '9') {
            value = value * 10 + s[i] - '0';
        }
    }

    return value * (neg?-1:1);
}

void reverse(std::string& s)
{
    int len = s.size();
    for (int i = 0; i < (len >>1); ++i) {
        s[i] = s[len-i-1] + s[i];
        s[len-i-1] = s[i] - s[len-i-1];
        s[i] = s[i] - s[len-i-1];
    }
}

void upper(std::string& s)
{
    int len = s.size();

    for (int i = 0; i < len; ++i) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = s[i] - 'a' + 'A';
        }
    }
}

int test_data[] = {1, 2, 3, 4, 8, 9, 22, 84, 99};

int find(int k, int data[], int size)
{
    int idx = -1;

    int l = 0;
    int r = size - 1;
    int mid = 0;
    while (l <= r) {
        mid = (r+l)>>1;
        if (data[mid] == k) {
            idx = mid;
            break;
        }
        if (data[mid] < k) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return idx;
}

template <class T>
class Node {
    public:
        T i;
        Node *next;
        Node *prev;
};

template<class T>
class List {
    public:
        List();
        ~List();

        int add(T d);
        int insert(int idx, T d);

        void dump();
        void r_dump();

    private:
        int _size;
        Node<T> *_head;
        Node<T> *_tail;
} ;

template<class T>
List<T>::List()
    : _size(0), _head(NULL), _tail(NULL)
{
}

template<class T>
List<T>::~List()
{
    Node<T>* node = _head;
    Node<T>* next = NULL;
    while (node) {
        next = node->next;
        delete node;
        node = next;
    };
}

template<class T>
int List<T>::add(T d)
{
    Node<T>* new_node = new Node<T>; 

    if (!new_node) {
        fprintf(stderr, "MEMERR!\n");
        return -1;
    }

    new_node->i = d;

    if (_head == NULL || _tail == NULL) {
        new_node->next = NULL;
        new_node->prev = NULL;
        _head = new_node;
        _tail = new_node;
        _size++;

        return 0;
    }

    new_node->next = _head;
    new_node->prev = NULL;
    _head->prev = new_node;
    _head = new_node;
    _size++;

    return 0;
}

template<class T>
int List<T>::insert(int idx, T d)
{
    if (idx < 0) {
        idx = _size + idx;
    }

    Node<T>* node = _head;

    while (idx-- && node) { node = node->next; }

    if (!node) {
        fprintf(stderr, "out of range idx: %d\n", idx);
        return -1;
    }

    Node<T>* new_node = new Node<T>;

    new_node->i = d;
    new_node->next = node;
    new_node->prev = node->prev;
    node->prev->next = new_node;
    node->prev = new_node;

    if (node == _head) {
        _head = new_node;
    }

    if (node == _tail) {
        _tail = new_node;
    }

    _size++;

    return 0;
}

template<class T>
void List<T>::dump()
{
    Node<T>* node = _head;
    if (node) {
        printf("%d", node->i);
        node = node->next;
    }
    while (node) {
        printf("->%d", node->i);
        node = node->next;
    };
    printf("\n");
}

template<class T>
void List<T>::r_dump()
{
    Node<T>* node = _tail;
    if (node) {
        printf("%d", node->i);
        node = node->prev;
    }
    while (node) {
        printf("->%d", node->i);
        node = node->prev;
    };
    printf("\n");
}
int main()
{
    printf("%d\n", s2i("-1238809a"));

    std::string str = "123456";
    reverse(str);
    printf("reversed: %s\n", str.c_str());

    std::string str2 = "abcEf";
    upper(str2);
    printf("upper: %s\n", str2.c_str());

    printf("find '3' at [%d]\n", find(99, test_data, sizeof(test_data)/sizeof(test_data[0])));

    List<int> l;
    l.add(3);
    l.add(8);
    l.add(9);
    l.add(20);
    l.insert(1, 88);
    l.dump();
    l.r_dump();

    return 0;
}
