#pragma once
#include <iostream>

namespace mds
{
    template<class T>
    struct LinkedListNode
    {
        T value = T();
        LinkedListNode<T>* next, * prev;
        LinkedListNode(T val, LinkedListNode<T>* prev, LinkedListNode<T>* next) :value(val), prev(prev), next(next) {}
        LinkedListNode(LinkedListNode<T>* prev, LinkedListNode<T>* next) : prev(prev), next(next) {}
        LinkedListNode(T val) : value(val) {
            next = 0;
            prev = 0;
        }
        LinkedListNode() { next = 0; prev = 0; }
    };

    template<class T>
    std::ostream& operator<<(std::ostream& os, LinkedListNode<T>* obj)
    {
        os << obj->value;
        return os;
    }

    template<class T>
    struct LinkedList
    {
    private:
        int sz = 0;
    public:
        const int size() const
        {
            return sz;
        }
        LinkedListNode<T>* head;
        LinkedListNode<T>* tail;
        LinkedList()
        {
            LinkedListNode<T>* nullpointer = 0;
            head = new LinkedListNode<T>(nullpointer, tail);
            tail = new LinkedListNode<T>(head, nullpointer);
            head->next = tail;
        }
        void push_back(const T& value)
        {
            sz++;
            auto x = new LinkedListNode<T>(value, tail->prev, tail);
            tail->prev->next = x;
            tail->prev = x;
        }

        void push_front(const T& value)
        {
            sz++;
            auto x = new LinkedListNode<T>(value, head, head->next);
            head->next->prev = x;
            head->next = x;
        }

        void pop_back()
        {
            if (!sz) return;
            LinkedListNode<T>* x = tail->prev;
            tail->prev = x->prev;
            x->prev->next = tail;
            delete x;
        }

        void pop_front()
        {
            if (!sz) return;
            LinkedListNode<T>* x = head->next;
            head->next = x->next;
            x->next->prev = head;
            delete x;
        }


        LinkedListNode<T>* first()
        {
            return head->next;
        }

        template <class Func>
        void for_each(Func func)
        {
            LinkedListNode<T>* p = head->next;
            while (p->next)
            {
                func(p->value);
                p = p->next;
            }
        }
        template <class Func>
        void for_each_back(Func func)
        {
            LinkedListNode<T>* p = tail->prev;
            while (p->prev)
            {
                func(p->value);
                p = p->prev;
            }
        }
    };
}

