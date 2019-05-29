#include <bits/stdc++.h>
using namespace std;

using ll = long long int;

const int N = 1e5+7;

int n;
ll x;
ll a[N];
vector<int> g[N];

void eadd(int u, int v)
{
  g[u].push_back(v);
  g[v].push_back(u);
}

ll dfs(int u=0, int p=-1)
{
  if(u && g[u].size() == 1) return 0;
  
  ll res = 0;
  for(int v: g[u])
  {
    if(v != p) res += max(-x, dfs(v, u) + a[v]);
  }
  return res;
}

void clean()
{
  for(int i=0;i<=n;++i) g[i].clear();
}

int main()
{
  int tt;
  scanf("%d", &tt);
  while(tt--)
  {
    scanf("%d%lld", &n, &x);
    for(int i=1;i<=n;++i) scanf("%lld", a + i);
    for(int i=1, u, v;i<n;++i)
    {
      scanf("%d%d", &u, &v);
      eadd(u, v);
    }
    eadd(0, 1);
    printf("%lld\n", dfs());
    clean();
  }
  
  return 0;
}
