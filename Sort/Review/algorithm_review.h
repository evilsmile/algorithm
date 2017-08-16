#ifndef __ALGRITHM_REVIEW_H__
#define __ALGRITHM_REVIEW_H__

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <boost/shared_ptr.hpp>

typedef std::vector<int> array_t;

class IAlgorithm {
    public:
        IAlgorithm(const std::string& name) 
            : _name(name){
//           printf("%s + \n", _name.c_str()); 
            }

        virtual void sort(array_t&) = 0;
        std::string get_name() {
            return _name;
        }

        ~IAlgorithm() {
 //           printf("%s ~\n", _name.c_str());
        }
    protected:
        void _swap(int& a, int& b);

    private:
        IAlgorithm() {}

    private:
        std::string _name;
};

/////////////////////////////////////////////////////////////////////
class BubbleSort : public IAlgorithm{
    public:
        BubbleSort() : IAlgorithm("bubble"){}
        virtual void sort(array_t&);
};

/////////////////////////////////////////////////////////////////////
class SelectSort : public IAlgorithm{
    public:
        SelectSort() : IAlgorithm("select") {}
        virtual void sort(array_t&);
};

/////////////////////////////////////////////////////////////////////
class InsertSort : public IAlgorithm{
    public:
        InsertSort() : IAlgorithm("insert") {}
        virtual void sort(array_t&);
};

/////////////////////////////////////////////////////////////////////
class QuickSort : public IAlgorithm{
    public:
        QuickSort() : IAlgorithm("quick") {}
        virtual void sort(array_t&);
    private:
        int _parition(array_t& data, int left, int right);
        void _quick(array_t& data, int left, int right);
};

/////////////////////////////////////////////////////////////////////
class ShellSort : public IAlgorithm{
    public:
        ShellSort() : IAlgorithm("shell") {}
        virtual void sort(array_t&);
};

/////////////////////////////////////////////////////////////////////
class HeapSort : public IAlgorithm{
    public:
        HeapSort() : IAlgorithm("heap") {}
        virtual void sort(array_t&);

    private:
        void _building_heap(array_t& data, int size);
        void _heap_adjust(array_t& data, int start_node, int size);
};

/////////////////////////////////////////////////////////////////////
class SortAlgorithm {
    public:
        enum SORT_ALG {
            NONE = 0x1,
            BUBBLE = 0x2,
            SELECT = 0x4,
            INSERT = 0x8,
            QUICK = 0x10,
            SHELL = 0x20,
            HEAP = 0x40,
            MAX_ALG = HEAP << 1,
        };

        static int ALL_ALGS;

        class AlgTypeTraversor {
            public:
                AlgTypeTraversor() : _alg_type(NONE) {}
                bool next() {
                    _alg_type = (SORT_ALG)(((static_cast<int>(_alg_type)))<<1);
                    if (_alg_type >= MAX_ALG) {
                        return false;
                    }
                    return true;
                }
                SORT_ALG get() {
                    return _alg_type;
                }
            private:
                SORT_ALG _alg_type;
        };

        SortAlgorithm();
        SortAlgorithm(SORT_ALG alg_type);

        void set_algrithm(SORT_ALG alg_type);

        void sort(array_t& data);

        std::string getName() ;

    private:
        SORT_ALG _alg_type;

        boost::shared_ptr<IAlgorithm> _alg_impl;
};

#endif
