#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

vector<int> pos, neg;

bool ok(int x, int y)
{
    int p1 = min(abs(x), abs(y));
    int p2 = max(abs(x), abs(y));

    int a1 = min(abs(x-y), abs(x+y));
    int a2 = max(abs(x-y), abs(x+y));

    return a1 <= p1 && p2 <= a2;
}

int bs1(int lo, int hi, int x, vector<int>& v)
{
    if(hi - lo <= 1)
    {
        for(int i=hi;i>=lo;--i)
            if(ok(x, v[i])) return i;
        return lo-1;
    }
    int m = (lo + hi) >> 1;
    int y = v[m];
    if(ok(x, y)) return bs1(m, hi, x, v);
    return bs1(lo, m-1, x, v);
}

int bs2(int lo, int hi, int x)
{
    if(hi - lo <= 1)
    {
        for(int i=hi;i>=lo;--i)
            if(ok(-x, pos[i])) return i;
        return lo-1;
    }
    int m = (lo + hi) >> 1;
    int y = pos[m];
    if(ok(-x, y)) return bs2(m, hi, x);
    return bs2(lo, m-1, x);
}

int bs3(int lo, int hi, int x)
{
    if(hi - lo <= 1)
    {
        if(ok(-x, pos[lo])) return lo;
        if(ok(-x, pos[++lo])) return lo;
        return ++lo;
    }
    int m = (lo + hi) >> 1;
    int y = pos[m];
    if(ok(-x, y)) return bs3(lo, m, x);
    return bs3(m+1, hi, x);
}

int main()
{
    int n;
    scanf("%d", &n);

//    vector<int> ve;

    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d", &x);
//        ve.push_back(x);
        if(x > 0) pos.push_back(x);
        else if(x < 0) neg.push_back(-x);
    }

    sort(pos.begin(), pos.end());
    sort(neg.begin(), neg.end());

    ll ans = 0;

    int n1 = pos.size();
    int n2 = neg.size();
    for(int i=0;i<n1;++i)
    {
        int p = bs1(i, n1-1, pos[i], pos); // fixed x
        ans += p - i;
    }

    for(int i=0;i<n2;++i)
    {
        int p = bs1(i, n2-1, neg[i], neg); // fixed x
        ans += p - i;
    }

    for(int x: neg)
    {
        int pp = lower_bound(pos.begin(), pos.end(), x) - pos.begin();
//        cerr << pp << endl;
        if(pp < n1)
        {
            int p1 = bs2(pp, n1-1, x);
            if(p1 >= pp)
                ans += p1 - pp + 1;
        }
        if(pp-1 >= 0)
        {
            int p2 = bs3(0, pp-1, x);
            if(p2 < pp)
                ans += pp - p2;
        }
    }

    cout << ans << endl;

//    ll ans1 = 0;
//    for(int i=0;i<n;++i)
//    {
//        for(int j=i+1;j<n;++j)
//            if(ok(ve[i], ve[j]))++ans1;
//    }
//
//    cout << "ans1 = " << ans1 << endl;

    return 0;
}
