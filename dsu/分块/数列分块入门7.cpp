#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MAX_N = 1e5 + 10;
const int MAX_T = sqrt(1e5) + 10;
const int mod = 10007;

int n, a[MAX_N], pre[MAX_N];
int L[MAX_T], R[MAX_T], sum[MAX_T], sub[MAX_T];

inline void init() {
    for (int i = 0; i < MAX_T; i++) {
        sub[i] = 1;
    }

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
        }
    }
}

inline void spread(int id) {
    for (int i = L[id]; i <= R[id]; i++) {
        a[i] = ((a[i] * sub[id]) % mod + sum[id]) % mod;
    }

    sum[id] = 0, sub[id] = 1;
}

inline void change_sum(int l, int r, int d) {
    int p = pre[l], q = pre[r];

    if (p == q) {
        spread(p);
        for (int i = l; i <= r; i++)    a[i] = (a[i] + d) % mod;
    } else {
        for (int i = p + 1; i <= q - 1; i++) {
            sum[i] = (sum[i] + d) % mod;
        }

        spread(p);
        for (int i = l; i <= R[p]; i++) a[i] = (a[i] + d) % mod;
        spread(q);
        for (int i = L[q]; i <= r; i++) a[i] = (a[i] + d) % mod;
    }
}

inline void change_sub(int l, int r, int d) {
    int p = pre[l], q = pre[r];

    if (p == q) {
        spread(p);
        for (int i = l; i <= r; i++)    a[i] = (a[i] * d) % mod;
    } else {
        for (int i = p + 1; i <= q - 1; i++) {
            sum[i] = (sum[i] * d) % mod;
            sub[i] = (sub[i] * d) % mod;
        }

        spread(p);
        for (int i = l; i <= R[p]; i++) a[i] = (a[i] * d) % mod;
        spread(q);
        for (int i = L[q]; i <= r; i++) a[i] = (a[i] * d) % mod;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] %= mod;
    }

    init();

    int temp = n;
    while (temp--) {
        int op, l, r, c;
        cin >> op >> l >> r >> c;
        if (!op) {
            change_sum(l, r, c);
        } else if (op == 1) {
            change_sub(l, r, c);
        } else {
            int t = pre[r];
            cout << ((a[r] * sub[t]) % mod + sum[t]) % mod << '\n';
        }
    }

    return 0;
}
