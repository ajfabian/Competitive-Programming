#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+7;

using ll = long long int;

int n;
ll v[N], m[N];
vector<int> g[N];
void eadd(int u, int v)
{
  g[u].push_back(v);
  g[v].push_back(u);
}

void dfs(vector<pair<int, ll>>& ans, int u=1, int p=0, ll gcd=0)
{
  if(u != 1 && g[u].size() == 1)
  {
    gcd = __gcd(gcd, v[u]);
    gcd = __gcd(gcd, m[u]);
    ans.emplace_back(u, m[u] - gcd);
    return;
  }
  for(int vv: g[u]) if(vv != p) dfs(ans, vv, u, __gcd(gcd, v[u]));
}

void clean()
{
  for(int i=1;i<=n;++i) g[i].clear();
}

int main()
{
  int tt;
  scanf("%d", &tt);
  while(tt--)
  {
    scanf("%d", &n);
    for(int i=1;i<n;++i)
    {
      int u, v;
      scanf("%d%d", &u, &v);
      eadd(u, v);
    }
    
    for(int i=1;i<=n;++i) scanf("%lld", v + i);
    for(int i=1;i<=n;++i) scanf("%lld", m + i);
    
    vector<pair<int, ll>> ans;
    dfs(ans);
    sort(ans.begin(), ans.end());
    for(auto p: ans) printf("%lld ", p.second);
    printf("\n");
    clean();
  }
  return 0;
}
