#include <bits/stdc++.h>
#define int long long

using namespace std;

struct DSU {
    int fa[100010];

    inline void init(int n) {
        for (int i = 1; i <= n; i ++)
            fa[i] = i;
    };

    inline int get(int x) {
        if (x == fa[x]) return x;
        return fa[x] = get(fa[x]);
    };

    inline void merge(int x, int y) {
        fa[get(x)] = get(y);
    };

    inline bool query(int x, int y) {
        return get(x) == get(y);
    };

    inline int sum(int n) {
        int res = 1;
        for (int i = 1; i <= n; i ++)
            res += (i == get(i));
        return res;
    };
};
