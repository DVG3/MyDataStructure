#include <iostream>
#include <string>
#include <deque>
using namespace std;

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
        auto x = new LinkedListNode<T>(value, tail->prev, tail);
        tail->prev->next = x;
        tail->prev = x;
    }

    void push_front(const T& value)
    {
        auto x = new LinkedListNode<T>(value, head, head->next);
        head->next->prev = x;
        head->next = x;
    }

    void pop_front()
    {

        LinkedListNode *x = head->next;


    }
    
    LinkedListNode<T>* first()
    {
        return head->next;
    }


    void for_each(void (*func)(T))
    {
        LinkedListNode<T>* p = head->next;
        while (p->next)
        {
            func(p->value);
            p = p->next;
        }
    }
};

LinkedList<int> ll;

int main()
{
    ll.push_front(4);
    ll.push_front(3);
    ll.push_front(2);
    //Linked list 1,2,3,4,5,6
    auto p = ll.first();
    ll.for_each([](int x) {
        cout << x << "\n";
        });
    return 0;
}
