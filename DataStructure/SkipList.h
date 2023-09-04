#pragma once


#define _MAX_NODE_LEVEL 25
template <class T>
struct SkipListNode
{
    SkipListNode<T>* nxt[_MAX_NODE_LEVEL];
    int width[_MAX_NODE_LEVEL];
    T value;
    SkipListNode() {
        value = T();
        for (int i = 0; i < _MAX_NODE_LEVEL; i++)
        {
            nxt[i] = 0;
            width[i] = 0;
        }

    }
};

template<class T>
struct SkipList
{
private:
    SkipListNode<T>* tmp[_MAX_NODE_LEVEL];
    int stepAtLevel[_MAX_NODE_LEVEL];
    int _sz = 0;
public:
    SkipListNode<T>* head;
    SkipList()
    {
        head = new SkipListNode<T>();
    }
    int size()
    {
        return _sz;
    }

    SkipListNode<T>* lower_bound(const T& x)
    {
        SkipListNode<T>* cur = head;
        for (int i = _MAX_NODE_LEVEL - 1; i >= 0; i--)
        {
            while (cur->nxt[i] != 0 && cur->nxt[i]->value < x)
            {
                cur = cur->nxt[i];
            }
        }
        return cur->nxt[0];
    }
    int key_of(const T& x)
    {
        int idx = 0;
        SkipListNode<T>* cur = head;
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
        SkipListNode<T>* cur = head;
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

        SkipListNode<T>* cur = head;
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

        int levelAdd = std::max(std::min(_MAX_NODE_LEVEL, 1 - int(log2((double)rand() / (double)(RAND_MAX)))), 1);
        int steps = 0;
        SkipListNode<T>* newNode = new SkipListNode<T>();
        for (int i = 0; i < levelAdd; i++)
        {

            SkipListNode<T>* pre = tmp[i];
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
        SkipListNode<T>* cur = head;
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
        //SkipListNode<T>* remain = tmp[0]->nxt[0];
        SkipListNode<T>* tmp2 = tmp[0]->nxt[0];
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

