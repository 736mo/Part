#include <bits/stdc++.h>
#define int long long
using namespace std;
template<typename T>
inline void read(T & x){
    x = 0; T f = 1; char ch = getchar();
    while (ch < '0' || ch > '9')    { if (ch == '-')    f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9')  { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
const int MAXN = 1e5 + 10;
const int LOG_MAXN = 30;
int N, M, ST[MAXN][LOG_MAXN], LogN[MAXN];
inline void init() {
    LogN[1] = 0;
    for (int i = 2; i <= MAXN; i ++)
        LogN[i] = LogN[i / 2] + 1;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read(N), read(M);
    for (int i = 1; i <= N; i ++)
        read(ST[i][0]);
    init();
    for (int j = 1; j <= LOG_MAXN; j ++)
        for (int i = 1; i + (1 << j) - 1 <= N; i ++)
            ST[i][j] = max(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
    while (M --) {
        int l, r; read(l), read(r);
        int k = LogN[r - l + 1];
        cout << max(ST[l][k], ST[r - (1 << k) + 1][k]) << '\n';
    }
    return 0;
}
