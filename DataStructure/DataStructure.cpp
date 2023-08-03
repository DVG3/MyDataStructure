#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include "LIWDO.h"

using namespace std;



mds::LIWDO<int> liwdo;


int main()
{
    liwdo.push_back(5);
    liwdo.for_each([&](int x) {
        cout << x << "\n";
        });
    return 0;
}
