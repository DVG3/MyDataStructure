#pragma once
#include <vector>
namespace mds
{
    struct DSU
    {
        std::vector<int> parent, depth;
        DSU(int _sz)
        {
            parent.assign(_sz, 0);
            depth.assign(_sz, 0);
            reset();
        }

        DSU()
        {

        }

        void assign(int _sz)
        {
            parent.assign(_sz, 0);
            depth.assign(_sz, 0);
            reset();
        }

        int get_parent(int x)
        {
            return x == parent[x] ? x : parent[x] = get_parent(parent[x]);
        }

        int get_sz(int x)
        {
            x = get_parent(x);
            return depth[x];
        }

        bool join(int u, int v)
        {
            u = get_parent(u);
            v = get_parent(v);
            if (u == v) return 0;
            if (depth[u] < depth[v]) std::swap(u, v);
            depth[u] += depth[v];
            parent[v] = u;
        }

        void reset()
        {
            for (int i = 0; i < parent.size(); i++)
            {
                parent[i] = i;
                depth[i] = 1;
            }
        }
    };
}