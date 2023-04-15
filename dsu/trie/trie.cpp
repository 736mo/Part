#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MAX_N = 3e6 + 5;

int trie[MAX_N][65], cnt[MAX_N], tot;

inline int get(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 26;
    } else {
        return c - '0' + 52;
    }
} 

inline void insert(string s) {
    int p = 0;
    for (int i = 0; i < s.size(); i++) {
        int c = get(s[i]);
        if (!trie[p][c])    trie[p][c] = ++tot;
        p = trie[p][c], cnt[p]++;
    }
}

inline int find(string s) {
    int p = 0, ans = 0;
    for (int i = 0; i < s.size(); i++) {
        p = trie[p][get(s[i])];
        if (!p) return cnt[p];
    }
    return cnt[p];
}

inline void solve() {
    for (int i = 0; i <= tot; i++)
        for (int j = 0; j <= 64; j++)
            trie[i][j] = 0;
    for (int i = 0; i <= tot; i++)
        cnt[i] = 0;
    tot = 0;

    int n, Q;
    cin >> n >> Q;

    while (n--) {
        string s;
        cin >> s;
        insert(s);
    }

    while (Q--) {
        string t;
        cin >> t;
        cout << find(t) << '\n';
    }
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
