#include <bits/stdc++.h>
#define int long long
#define ld long double
#define ri register int
#define inf64 0x7fffffff
#define endl '\n'
#define N signed(1e5 + 10)
using namespace std;
struct SegmentTree {
    int l, r, sum, add, mul;
} t[N << 2];
int n, m, a[N], mod;
inline void updata(int p) {
    t[p].sum = (t[p << 1].sum + t[p << 1 | 1].sum) % mod;
}
inline void spread(int p) {
    t[p << 1].sum = (t[p << 1].sum * t[p].mul + t[p].add * (t[p << 1].r - t[p << 1].l + 1)) % mod;
    t[p << 1 | 1].sum = (t[p << 1 | 1].sum * t[p].mul + t[p].add * (t[p << 1 | 1].r - t[p << 1 | 1].l + 1)) % mod;
    t[p << 1].mul = (t[p << 1].mul * t[p].mul) % mod;
    t[p << 1 | 1].mul = (t[p << 1 | 1].mul * t[p].mul) % mod;
    t[p << 1].add = (t[p << 1].add * t[p].mul + t[p].add) % mod;
    t[p << 1 | 1].add = (t[p << 1 | 1].add * t[p].mul + t[p].add) % mod;
    t[p].add = 0, t[p].mul = 1;
}
inline void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r, t[p].mul = 1;
    if (l == r)
    {
        t[p].sum = a[l] % mod;
        return ;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    updata(p);
}
inline void changeadd(int p, int l, int r, int v) {
    if (l <= t[p].l && r >= t[p].r) {
        t[p].add = (t[p].add + v) % mod;
        t[p].sum = (t[p].sum + v * (t[p].r - t[p].l + 1)) % mod;
        return ;
    }
    spread(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid)   changeadd(p << 1, l, r, v);
    if (r > mid)    changeadd(p << 1 | 1, l, r, v);
    updata(p);
}
inline void changemul(int p, int l, int r, int v) {
    if (l <= t[p].l && r >= t[p].r) {
        t[p].add = (t[p].add * v) % mod;
        t[p].mul = (t[p].mul * v) % mod;
        t[p].sum = (t[p].sum * v) % mod;
        return ;
    }
    spread(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid)   changemul(p << 1, l, r, v);
    if (r > mid)    changemul(p << 1 | 1, l, r, v);
    updata(p);
}
inline int ask(int p, int l, int r) {
    if (l <= t[p].l && r >= t[p].r) return t[p].sum;
    spread(p);
    int mid = (t[p].l + t[p].r) >> 1;
    int val = 0;
    if (l <= mid)   val = (val + ask(p << 1, l, r)) % mod;
    if (r > mid)    val = (val + ask(p << 1 | 1, l, r)) % mod;
    return val % mod;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> mod;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];
    build(1, 1, n);
    while (m --) {
        int op, l, r, k;
        scanf("%lld%lld%lld", &op, &l, &r);
        if (op == 1) {
            scanf("%lld", &k);
            changemul(1, l, r, k);
        }
        else if (op == 2) {
            scanf("%lld", &k);
            changeadd(1, l, r, k);
        }
        else {
            cout << ask(1, l, r) % mod << '\n';
        }
    }
    return 0;
}
