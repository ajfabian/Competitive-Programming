/*
 * CF1101-D12-F
 * Idea: binary search
 * SC: 2
 * TT: 10
 * CT: 20
 * lev: 8
 * Category: binary search, greedy
 * Important. Trick from bloodewoosh#6 seems to be quite useful.
 * */

#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const int N = 4444;
const int M = 5e5+7;

int n, m;


struct node
{
  int u;
  ll v, r;
  node(int u, ll v, ll r)
  : u(u), v(v), r(r) {}
  
  bool operator <(const node& p)const
  {
    if(r != p.r) return r < p.r;
    return v < p.v;
  }
};
ll x[N];
ll s[M], f[M], c[M], r[M];


bool check(int k, ll V)
{
  ll mdist = V / c[k];
  int tt = 0;
  for(int i=s[k], j; i < f[k];)
  {
    j = i;
    while(j < f[k])
      if(mdist >= x[j+1] - x[i]) ++j;
      else break;
    if(i == j) return false;
    i = j;
    if(i < f[k]) ++tt;
  }
  //~ cerr << "tsteps: " << tt << endl;
  return tt <= r[k];
}

ll bs(int i, ll lo, ll hi)
{
  if(hi - lo <= 1ll)
  {
    if(check(i, lo)) return lo;
    if(check(i, lo+1)) return lo+1;
    return lo+2;
  }
  ll m = (lo + hi) / 2;
  if(check(i, m)) return bs(i, lo, m);
  return bs(i, m+1, hi);
}

ll solve(int i, ll ans)
{
  if(check(i, ans)) return ans;
  return bs(i, ans, 1e18);
}

int main()
{
  
  scanf("%d%d", &n, &m);
  
  for(int i=1;i<=n;++i)
    scanf("%lld", x + i);
  
  for(int i=1;i<=m;++i)
    scanf("%lld%lld%lld%lld", s + i, f + i, c + i, r + i);
  
  vector<int> ord;
  for(int i=1;i<=m;++i)
    ord.push_back(i);
  
  random_device rd;
  mt19937 gen(rd());
  shuffle(ord.begin(), ord.end(), gen);
  
  ll ans = 0;
  for(int i: ord)
    ans = max(ans, solve(i, ans));
  
  cout << ans << endl;
  
  return 0;
}
