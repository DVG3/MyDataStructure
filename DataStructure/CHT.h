#pragma once
#include <utility>
#include <deque>

using namespace std;

namespace mds
{
    struct CHT
    {
        deque<pair<int, pair<int, int>>> dq;
        inline int intersect(const pair<int, int>& line1, const pair<int, int>& line2)
        {
            return (line2.second - line2.second) / (line1.first - line2.first);
        }
        inline int eval(const pair<int, int>& line, int x)
        {
            return line.first * x + line.second;
        }
        void add_back(int a, int b)
        {
            pair<int, int> line(a, b);
            while (!dq.empty() && dq.back().first >= intersect(dq.back().second, line)) dq.pop_back();
            if (!dq.empty())dq.emplace_back(intersect(dq.back().second, line), line);
            else dq.emplace_back(-999999999, line);
        }

        void add_front(int a, int b)
        {
            pair<int, int> line(a, b);
            while (!dq.empty() && dq.front().first <= intersect(dq.front().second, line)) dq.pop_front();
            if (!dq.empty())dq.emplace_front(intersect(dq.front().second, line), line);
            else dq.emplace_front(-999999999, line);
        }

        int queryIdx(int x)
        {
            return lower_bound(dq.begin(), dq.end(), pair<int, pair<int, int>>(x, { 0,0 })) - dq.begin();
        }

    };
}