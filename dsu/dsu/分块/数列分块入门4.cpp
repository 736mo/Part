#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MAX_N = 5e4 + 10;
const int MAX_T = sqrt(5e4) + 10;

int n, a[MAX_N], pre[MAX_N];
int L[MAX_T], R[MAX_T], add[MAX_T], sum[MAX_T];

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

inline void change(int l, int r, int d) {
    int p = pre[l], q = pre[r];

    if (p == q) {
        for (int i = l; i <= r; i++)    a[i] += d;
        sum[p] += (r - l + 1) * d;
    } else {
        for (int i = p + 1; i <= q - 1; i++)    add[i] += d;
            
        for (int i = l; i <= R[p]; i++) a[i] += d;
        sum[p] += (R[p] - l + 1) * d;
        for (int i = L[q]; i <= r; i++) a[i] += d;
        sum[q] += (r - L[q] + 1) * d;
    }
}

inline int ask(int l, int r, int mod) {
    int p = pre[l], q = pre[r];

    int ans = 0;
    if (p == q) {
        for (int i = l; i <= r; i++)    ans = (ans + a[i]) % mod;
        ans = (ans + add[p] * (r - l + 1) % mod) % mod;
    } else {
        for (int i = p + 1; i <= q - 1; i++)    ans = (ans + sum[i] + add[i] * (R[i] - L[i] + 1) % mod) % mod;
        for (int i = l; i <= R[p]; i++) ans = (ans + a[i]) % mod;
        ans = (ans + add[p] * (R[p] - l + 1) % mod) % mod;
        for (int i = L[q]; i <= r; i++) ans = (ans + a[i]) % mod;
        ans = (ans + add[q] * (r - L[q] + 1) % mod) % mod;
    }

    return ans % mod;
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
            cout << ask(l, r, c + 1) << '\n';
        }
    }

    return 0;
}
