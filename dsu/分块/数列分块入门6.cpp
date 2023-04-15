#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MAX_N = 2e5 + 10;
const int MAX_T = sqrt(2e5) + 10;

int n, a[MAX_N];
vector<int> v[MAX_T];

inline void init() {
    int t = sqrt(n);

    for (int i = 1; i <= t; i++) {
        for (int j = (i - 1) * t + 1; j <= i * t; j++) {
            v[i].push_back(a[j]);
        }
    }

    if (t * t < n) {
        for (int i = t * t + 1; i <= n; i++) {
            v[t + 1].push_back(a[i]);
        }
    }
}

inline void change(int p, int x) {
    int i = 1, R = v[1].size();
    while (R < p)   i++, R += v[i].size();
    
    v[i].insert(v[i].begin() + (p - (R - v[i].size())) - 1, x);
}

inline void ask(int p) {
    int i = 1, R = v[1].size();
    while (R < p)   i++, R += v[i].size();

    cout << v[i][p - (R - v[i].size()) - 1] << '\n';
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
            ask(r);
        }
    }

    return 0;
}
