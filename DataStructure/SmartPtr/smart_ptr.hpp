#include <iostream>

template <class T>
class smart_ptr;

// 所有smart_ptr 共享一个 ref指针，由第一个smart_ptr把这个ref给new出来，后面的smart_ptr就只操作_use
template <class T>
class smart_ptr_ref {
    friend class smart_ptr<T>;
    public:
        smart_ptr_ref(T* ptr) 
            : _ptr(ptr), _use(1)  
        {
        }

        ~smart_ptr_ref() {
            delete _ptr; 
        }

        T& operator*() {
            return *_ptr;
        }

        T* operator->() {
            return _ptr;
        }

    private:
        T* _ptr;
        size_t _use;
};

template <class T>
class smart_ptr {
    public:
        smart_ptr(T* ptr) 
            : _ref(new smart_ptr_ref<T>(ptr))
        {
        }

        smart_ptr(smart_ptr<T>& r) 
            : _ref(r._ref)
        {
            ++_ref->_use;
        }

        smart_ptr& operator=(const smart_ptr& r) {
            ++r._ref->_use;
            if (--_ref->_use == 0) {
                delete _ref;
            }

            _ref = r._ref;

            return *this;
        }

        ~smart_ptr() {
            if (--_ref->_use == 0) {
                delete _ref;
            }
        }

        T* get() const {
            return _ref->_ptr;  
        }

        T& get_ref() {
            return *_ref->ptr;
        }

        int count_ref() const {
            return _ref->_use;
        }

    private:
        // 所有smart_ptr共享同一个_ref, 包含计数和真实指针 
        smart_ptr_ref<T>* _ref;
};
