#include <bits/stdc++.h>
#define int long long 

#define INF 0x7f7f7f7f

using namespace std;
const int MAX_N = 1e5 + 10;
const int MAX_T = sqrt(1e5) + 10;

int n, a[MAX_N], pre[MAX_N];
int L[MAX_T], R[MAX_T], tag[MAX_T];

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
        }
        tag[i] = INF;
    }
}

inline void spread(int id) {
    if (tag[id] != INF) {
        for (int i = L[id]; i <= R[id]; i++) {
            a[i] = tag[id];
        }

        tag[id] = INF;
    }
}

inline int change(int l, int r, int d) {
    int p = pre[l], q = pre[r];

    int cnt = 0;
    if (p == q) {
        spread(p);
        for (int i = l; i <= r; i++) {
            a[i] == d ? cnt++ : a[i] = d;
        }
    } else {
        for (int i = p + 1; i <= q - 1; i++) {
            if (tag[i] != INF) {
                tag[i] == d ? cnt += (R[i] - L[i] + 1) : tag[i] = d;
            } else {
                for (int j = L[i]; j <= R[i]; j++) {
                    a[j] == d ? cnt++ : a[j] = d;
                }

                tag[i] = d;
            }
        }

        spread(p);
        for (int i = l; i <= R[p]; i++) {
            a[i] == d ? cnt++ : a[i] = d;
        }

        spread(q);
        for (int i = L[q]; i <= r; i++) {
            a[i] == d ? cnt++ : a[i] = d;
        }
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
        int l, r, c;
        cin >> l >> r >> c;
        cout << change(l, r, c) << '\n';
    }

    return 0;
}
