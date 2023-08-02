#pragma once
#include <functional>
#include <vector>
#include <iostream>

namespace mds
{
    template <class T>
    struct SparseTable
    {
        std::vector<std::vector<T>> table;

        std::function<T(const T&, const T&)> applyFunction = [](const T& previousTableValue1, const T& previousTableValue2) {
            return min(previousTableValue1, previousTableValue2);
        };

        void build(const std::vector<T>& arr)
        {
            table.assign(log2(arr.size() + 2), std::vector<T>(arr.size(), 0));
            for (int i = 0; i < arr.size(); i++)
                table[0][i] = arr[i];
            for (int i = 1; i < table.size(); i++)
            {
                for (int j = 0; j < int(arr.size() - (1 << (i - 1))); j++)
                {
                    table[i][j] = applyFunction(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
                }
            }
        }
        T query(int l, int r)
        {
            if (table.empty()) throw "Table hasn't had data yet";
            int rg = (r - l + 1);
            int lg = log2(rg);
            return applyFunction(table[lg][l], table[lg][r - (1 << lg) + 1]);
        }
        void printTable()
        {
            std::cout << "Debug Table:\n";
            for (auto& rows : table)
            {
                for (auto& cols : rows)
                {
                    std::cout << cols << " ";
                }
                std::cout << "\n";
            }
            std::cout << "End Debug Table\n";
        }
    };

}