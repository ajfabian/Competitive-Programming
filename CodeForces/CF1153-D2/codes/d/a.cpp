#include <bits/stdc++.h>
using namespace std;

const int N = 3e5+7;

int op[N];

vector<int> g[N];
void eadd(int u, int v)
{
  g[u].push_back(v);
  g[v].push_back(u);
}


int lc[N], dp[N];
void dfs1(int u=1, int p=0)
{
  lc[u] = g[u].size() == 1 && u != 1;
  for(int v: g[u]) if(v != p)
  {
    dfs1(v, u);
    lc[u] += lc[v];
  }
}
void dfs(int u=1, int p=0)
{
  if(g[u].size() == 1 && u != 1)
  {
    dp[u] = 1;
    return;
  }
  int tot = lc[u];
  for(int v: g[u]) if(v != p)
  {
    dfs(v, u);
    if(op[u] == 1) dp[u] = max(dp[u], lc[u] - lc[v] + dp[v]);
    else dp[u] += lc[v] - dp[v] + 1;
  }
  if(op[u] == 0) dp[u] = lc[u] - dp[u] + 1;
}

int main()
{
  int n;
  scanf("%d", &n);
  if(n == 1)
  {
    cout << "1\n";
    return 0;
  }
  for(int i=1;i<=n;++i) scanf("%d", op + i);
  for(int x, i=2;i<=n;++i)
  {
    scanf("%d", &x);
    eadd(x, i);
  }
  
  dfs1();
  dfs();
  
  cout << dp[1] << endl;
  
  return 0;
}
