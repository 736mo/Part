#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
int a[N];
struct SegmentTree {
    int l, r;
    int dat, add;
} t[N << 2];
inline void updata(int p) {
    t[p].dat = t[p << 1].dat + t[p << 1 | 1].dat;
}
inline void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) {
        t[p].dat = a[l];
        return ;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    updata(p);
}
inline void spread(int p) {
    if (t[p].add) {
        t[p << 1].dat += t[p].add * (t[p << 1].r - t[p << 1].l + 1);
        t[p << 1 | 1].dat += t[p].add * (t[p << 1 | 1].r - t[p << 1 | 1].l + 1);
        t[p << 1].add += t[p].add, t[p << 1 | 1].add += t[p].add;
        t[p].add = 0;
    }
}
inline void change(int p, int l, int r, int k) {
    if (l <= t[p].l && r >= t[p].r) {
        t[p].dat += k * (t[p].r - t[p].l + 1), t[p].add += k;
        return ;
    }
    spread(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid)   change(p << 1, l, r, k);
    if (r > mid)    change(p << 1 | 1, l, r, k);
    updata(p);
}
inline int ask(int p, int l, int r) {
    if (l <= t[p].l && r >= t[p].r) return t[p].dat;
    spread(p);
    int mid = (t[p].l + t[p].r) >> 1, val = 0;
    if (l <= mid)   val += ask(p << 1, l, r);
    if (r > mid)    val += ask(p << 1 | 1, l, r);
    return val;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];
    build(1, 1, n);
    while (m --) {
        int op, l, r, d;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> d;
            change(1, l, r, d);
        }
        else {
            cout << ask(1, l, r) << endl;
        }
    }
    return 0;
}
