#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 7;

vector<int> g[N];
void eadd(int u, int v)
{
  g[u].push_back(v);
  g[v].push_back(u);
}

int n;
int mk[N];
vector<int> ans;

int dfs(int u,int p=0)
{
  bool all_bad = true;
  for(int v: g[u])
  {
    if(v == p) continue;
    dfs(v, u);
    
    all_bad &= mk[v];
  }
  if(mk[u] && all_bad) ans.push_back(u);
}

int main()
{
  
  int rt=-1;
  scanf("%d", &n);
  for(int i=1;i<=n;++i)
  {
    int p;
    scanf("%d%d", &p, &mk[i]);
    if(~p) eadd(p, i);
    else rt = i;
  }
  assert(~rt);
  
  dfs(rt);
  
  sort(ans.begin(), ans.end());
  if(ans.size() == 0) return !(cout << "-1\n");
  for(int i: ans) printf("%d ", i);
  printf("\n");
  
  return 0;
}
