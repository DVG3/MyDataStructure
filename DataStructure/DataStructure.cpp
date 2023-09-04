#pragma GCC optimize("O2")
#pragma GCC target("avx,avx2,fma")
#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <chrono>
#include <set>
#include <algorithm>
#include <random>
#include <unordered_map>
#include "SkipList.h"
using namespace std;

using namespace std::chrono;
struct Timer
{
    steady_clock::time_point startime; 
    Timer()
    {
        startime = high_resolution_clock::now();
    }
    ~Timer()
    {
        auto cur = high_resolution_clock::now();
        cout << "took " << duration_cast<milliseconds>(cur - startime).count() << " miliseconds" << endl;
    }
};



#define _MAX_NODE_LEVEL 25
template <class T>
struct AutoSortArrayNode
{
    AutoSortArrayNode<T>* nxt[_MAX_NODE_LEVEL];
    int width[_MAX_NODE_LEVEL];
    T value;
    AutoSortArrayNode() {
        value = T();
        for (int i = 0; i < _MAX_NODE_LEVEL; i++)
        {
            nxt[i] = 0;
            width[i] = 0;
        }

    }
};

template<class T>
struct AutoSortArray
{
private:
    AutoSortArrayNode<T>* tmp[_MAX_NODE_LEVEL];
    int stepAtLevel[_MAX_NODE_LEVEL];
    int _sz = 0;
public:
    AutoSortArrayNode<T>* head;
    AutoSortArray()
    {
        head = new AutoSortArrayNode<T>();
    }
    int size()
    {
        return _sz;
    }

    AutoSortArrayNode<T>* lower_bound(const T & x)
    {
        AutoSortArrayNode<T>* cur = head;
        for (int i = _MAX_NODE_LEVEL - 1; i >= 0; i--)
        {
            while (cur->nxt[i] != 0 && cur->nxt[i]->value < x)
            {
                cur = cur->nxt[i];
            }
        }
        return cur->nxt[0];
    }
    int key_of(const T & x)
    {
        int idx = 0;
        AutoSortArrayNode<T>* cur = head;
        for (int i = _MAX_NODE_LEVEL - 1; i >= 0; i--)
        {
            while (cur->nxt[i] != 0 && cur->nxt[i]->value < x)
            {
                idx += cur->width[i];
                cur = cur->nxt[i];
            }
        }
        return idx + 1;
    }
    T& operator[](int index)
    {
        AutoSortArrayNode<T>* cur = head;
        index++;
        for (int i = _MAX_NODE_LEVEL - 1; i >= 0; i--)
        {
            while (index > cur->width[i])
            {
                index -= cur->width[i];
                if (cur->nxt[i]) cur = cur->nxt[i];
                else break;
            }
        }
        return cur->value;
    }

    void insert(T x)
    {

        AutoSortArrayNode<T>* cur = head;
        for (int i = _MAX_NODE_LEVEL - 1; i >= 0; i--)
        {
            stepAtLevel[i] = 0;
            tmp[i] = 0;
            while (cur->nxt[i] != 0 && cur->nxt[i]->value <= x)
            {
                if (cur->value == x) return;
                stepAtLevel[i] += cur->width[i];
                cur = cur->nxt[i];
            }
            tmp[i] = cur;
        }

        int levelAdd = max(min(_MAX_NODE_LEVEL, 1 - int(log2((double)rand() / (double)(RAND_MAX)))), 1);
        int steps = 0;
        AutoSortArrayNode<T>* newNode = new AutoSortArrayNode<T>();
        for (int i = 0; i < levelAdd; i++)
        {

            AutoSortArrayNode<T>* pre = tmp[i];
            newNode->width[i] = pre->width[i] - steps;
            pre->width[i] = steps + 1;
            newNode->value = x;
            newNode->nxt[i] = pre->nxt[i];
            pre->nxt[i] = newNode;
            steps += stepAtLevel[i];

        }
        for (int i = levelAdd; i < _MAX_NODE_LEVEL; i++)
        {
            tmp[i]->width[i] += 1;
        }
        _sz++;
    }


    void remove(const T& x)
    {
        AutoSortArrayNode<T>* cur = head;
        for (int i = _MAX_NODE_LEVEL - 1; i >= 0; i--)
        {
            tmp[i] = 0;
            while (cur->nxt[i] != nullptr && cur->nxt[i]->value < x)
            {
                cur = cur->nxt[i];
            }
            tmp[i] = cur;
        }
        int cnt = 0;
        if (tmp[0]->nxt[0] == 0 || tmp[0]->nxt[0]->value > x) return;
        //AutoSortArrayNode<T>* remain = tmp[0]->nxt[0];
        AutoSortArrayNode<T>* tmp2 = tmp[0]->nxt[0];
        for (int i = 0; i < _MAX_NODE_LEVEL; i++)
        {
            cnt++;
            if (tmp[i]->nxt[i] == 0 || tmp[i]->nxt[i]->value > x) break;
            //remain = tmp2;
            tmp[i]->width[i] += tmp2->width[i] - 1;
            tmp[i]->nxt[i] = tmp2->nxt[i];
        }
        for (int i = cnt - 1; i < _MAX_NODE_LEVEL; i++)
        {
            tmp[i]->width[i]--;
        }
        //delete[](*remain).nxt;
        delete tmp2;
        _sz--;
    }


};


AutoSortArray<pair<int,int>> arr;


int main()
{
    arr.insert({1,2});
    arr.insert({ 2,3 });
    arr.insert({ 3,4 });
    cout << arr.key_of({3,4}) << "\n";
    arr.remove({2,3});
    cout << arr.key_of({ 3,4 }) << "\n";
    return 0;
}
