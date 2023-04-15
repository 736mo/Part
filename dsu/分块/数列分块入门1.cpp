#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MAX_N = 5e4 + 10;
const int MAX_T = sqrt(5e4) + 1;

int n, a[MAX_N], L[MAX_N], R[MAX_N];
int pre[MAX_N], add[MAX_T];

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
    }
}

inline void change(int l, int r, int d) {
    int p = pre[l], q = pre[r];
    if (p == q) {
        for (int i = l; i <= r; i++)    a[i] += d;
    } else {
        for (int i = p + 1; i <= q - 1; i++)    add[i] += d;
        for (int i = l; i <= R[p]; i++) a[i] += d;
        for (int i = L[q]; i <= r; i++) a[i] += d;
    }
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
            cout << a[r] + add[pre[r]] << '\n';
        }
    }

    return 0;
}
