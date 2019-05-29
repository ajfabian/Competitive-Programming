#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;cin >> n;
    int f[256];
    memset(f, 0, sizeof f);
    for(int i=1;i<=n;++i)
    {
        string s;
        cin >> s;
        f[(int)s.front()]++;
    }

    int ans = 0;
    for(int i='a';i<='z';++i)
    {
        int N = f[i] / 2;
        int e = f[i] % 2;
        ans += N * (N - 1);
        if(e) ans += N;
    }
    cout << ans << endl;
    return 0;
}
