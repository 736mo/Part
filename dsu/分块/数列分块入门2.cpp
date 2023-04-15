#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MAX_N = 5e4 + 10;
const int MAX_T = sqrt(5e4) + 10;

int n, a[MAX_N];
int L[MAX_T], R[MAX_T], pre[MAX_N], add[MAX_T];
vector<int> block[MAX_T];

inline void init() {
    int t = sqrt(n);

    for (int i = 1; i <= t; i++) {
        L[i] = (i - 1) * t + 1;
        R[i] = i * t;
    }

    if (R[t] < n) {
        t++;
        L[t] = R[t - 1] + 1;
        R[t] = n;
    }

    for (int i = 1; i <= t; i++) {
        for (int j = L[i]; j <= R[i]; j++) {
            pre[j] = i;
            block[i].push_back(a[j]);
        }

        sort(block[i].begin(), block[i].end());
    }
}

inline void upd(int id) {
    block[id].clear();
    for (int i = L[id]; i <= R[id]; i++) {
        block[id].push_back(a[i]);
    }

    sort(block[id].begin(), block[id].end());
}

inline void change(int l, int r, int d) {
    int p = pre[l], q = pre[r];

    if (p == q) {
        for (int i = l; i <= r; i++)    a[i] += d;
        upd(p);
    } else {
        for (int i = p + 1; i <= q - 1; i++)    add[i] += d;

        for (int i = l; i <= R[p]; i++) a[i] += d;
        upd(p);

        for (int i = L[q]; i <= r; i++) a[i] += d;
        upd(q);
    }
}

inline int ask(int l, int r, int d) {
    int p = pre[l], q = pre[r];

    int cnt = 0;
    if (p == q) {
        for (int i = l; i <= r; i++)    cnt += (a[i] + add[p] < d);
    } else {
        for (int i = p + 1; i <= q - 1; i++) {
            cnt += lower_bound(block[i].begin(), block[i].end(), d - add[i]) - block[i].begin();
        }

        for (int i = l; i <= R[p]; i++) cnt += (a[i] + add[p] < d);
        for (int i = L[q]; i <= r; i++) cnt += (a[i] + add[q] < d);
    }

    return cnt;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    init();

    int temp = n;
    while (temp--) {
        int op, l, r, c;
        cin >> op >> l >> r >> c;
        if (op == 0) {
            change(l, r, c);
        } else {
            cout << ask(l, r, c * c) << '\n';
        }
    }

    return 0;
}
