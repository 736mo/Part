#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MAX_N = 5e4 + 10;
const int MAX_T = sqrt(5e4) + 10;

int n, a[MAX_N], pre[MAX_N];
int L[MAX_T], R[MAX_T], add[MAX_T], sum[MAX_T];
bool tag[MAX_T];

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
            sum[i] += a[j];
        }
    }
}

inline void change(int l, int r) {
    int p = pre[l], q = pre[r];

    if (p == q) {
        if (!tag[p]) {
            for (int i = l; i <= r; i++)    a[i] = sqrt(a[i]);

            sum[p] = 0, tag[p] = true;
            for (int i = L[p]; i <= R[p]; i++) {
                sum[p] += a[i];
                if (a[i] != 1) {
                    tag[p] = false;
                }
            }
        }
    } else {
        for (int i = p + 1; i <= q - 1; i++) {
            if (!tag[i]) {
                sum[i] = 0, tag[i] = true;
                for (int j = L[i]; j <= R[i]; j++) {
                    a[j] = sqrt(a[j]);
                    sum[i] += a[j];
                    if (a[j] != 1) {
                        tag[i] = false;
                    }
                }
            }
        }

        if (!tag[p]) {
            for (int i = l; i <= R[p]; i++) a[i] = sqrt(a[i]);

            sum[p] = 0, tag[p] = true;
            for (int i = L[p]; i <= R[p]; i++) {
                sum[p] += a[i];
                if (a[i] != 1) {
                    tag[p] = false;
                }
            }
        }

        if (!tag[q]) {
            for (int i = L[q]; i <= r; i++) a[i] = sqrt(a[i]);
                
            sum[q] = 0, tag[q] = true;
            for (int i = L[q]; i <= R[q]; i++) {
                sum[q] += a[i];
                if (a[i] != 1) {
                    tag[q] = false;
                }
            }
        }
    }
}

inline int ask(int l, int r) {
    int p = pre[l], q = pre[r];

    int ans = 0;
    if (p == q) {
        for (int i = l; i <= r; i++)    ans += a[i];
    } else {
        for (int i = p + 1; i <= q - 1; i++)    ans += sum[i];
        for (int i = l; i <= R[p]; i++) ans += a[i];
        for (int i = L[q]; i <= r; i++) ans += a[i];
    }

    return ans;
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
            change(l, r);
        } else {
            cout << ask(l, r) << '\n';
        }
    }

    return 0;
}
