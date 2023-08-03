#pragma once
#include <iostream>

namespace mds
{
    //LIWDO:Linked list with dynamic offset
    template<class T>
    struct LIWDONode
    {
        T value = T();
        LIWDONode<T>* next, * prev;
        LIWDONode(T val, LIWDONode<T>* prev, LIWDONode<T>* next) :value(val), prev(prev), next(next) {}
        LIWDONode(LIWDONode<T>* prev, LIWDONode<T>* next) : prev(prev), next(next) {}
        LIWDONode(T val) : value(val) {
            next = 0;
            prev = 0;
        }
        LIWDONode() { next = 0; prev = 0; }
    };

    template<class T>
    std::ostream& operator<<(std::ostream& os, LIWDONode<T>* obj)
    {
        os << obj->value;
        return os;
    }

    template<class T>
    struct LIWDO
    {
    private:
        int sz = 0;
    public:
        const int size() const
        {
            return sz;
        }
        LIWDONode<T>* head;
        LIWDONode<T>* tail;
        LIWDO()
        {
            LIWDONode<T>* nullpointer = 0;
            head = new LIWDONode<T>(nullpointer, tail);
            tail = new LIWDONode<T>(head, nullpointer);
            head->next = tail;
        }

        LIWDONode<T>* push_back_at(LIWDONode<T>* pos, const T& value)
        {
            sz++;
            LIWDONode<T>* x = new LIWDONode<T>(value, pos, pos->next);
            pos->next->prev = x;
            pos->next = x;
            return x;
        }

        LIWDONode<T>* push_front_at(LIWDONode<T>* pos, const T& value)
        {
            sz++;
            LIWDONode<T>* x = new LIWDONode<T>(value, pos->prev, pos);
            pos->prev->next = x;
            pos->prev = x;
            return x;
        }
        void erase(LIWDONode<T>* pos)
        {
            sz--;
            pos->prev->next = pos->next;
            pos->next->prev = pos->prev;
            delete pos;
        }
        void pop_back_at(LIWDONode<T>* pos)
        {
            if (!pos->next) return;
            erase(pos->next);
        }

        void pop_front_at(LIWDONode<T>* pos)
        {
            if (!pos->prev) return;
            erase(pos->prev);
        }

        LIWDONode<T>* push_back(const T& value)
        {
            return push_front_at(tail, value);
        }

        LIWDONode<T>* push_front(const T& value)
        {
            return push_back_at(head, value);
        }

        void pop_back()
        {
            if (!sz) return;
            erase(tail->prev);
        }

        void pop_front()
        {
            if (!sz) return;
            erase(head->next);
        }

        LIWDONode<T>* GetNode(int idx)
        {
            if (idx == -1) return tail->prev;
            if (idx >= sz) return 0;
            auto p = head->next;
            while (--idx) p = p->next;
            return p;
        }

        LIWDONode<T>* first()
        {
            return head->next;
        }

        template <class Func>
        void for_each(Func func)
        {
            LIWDONode<T>* p = head->next;
            while (p->next)
            {
                func(p->value);
                p = p->next;
            }
        }
        template <class Func>
        void for_each_back(Func func)
        {
            LIWDONode<T>* p = tail->prev;
            while (p->prev)
            {
                func(p->value);
                p = p->prev;
            }
        }
    };
}