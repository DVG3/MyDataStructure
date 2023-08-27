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


#define mySet SkipList


mySet<int> myst;
set<int> st;
vector<int> vt;
void make_random()
{
    for (int i = 200000; i >= 1; i--)
    {
        vt.push_back(i);
    }
    shuffle(vt.begin(), vt.end(), default_random_engine(time(0)));
}

void test1()
{
    cout << "My Set:\n";
    Timer time;;
    for (auto x: vt)
    {
        myst.insert(x);
    }
    for (int i = 1; i <= 10; i++)
    {
        cout << myst[i] << "\n";
    }
}

void test2()
{
    cout << "Set:\n";
    Timer time;
    for (auto x: vt)
    {
        st.insert(x);
    }
    int cnt = 11;
    for (auto x : st)
    {
        cnt--;
        if (!cnt) break;
        cout << x << "\n";
    }
}


int main()
{
    srand(time(0));
    make_random();
    test1();
    test2();
    return 0;
}
