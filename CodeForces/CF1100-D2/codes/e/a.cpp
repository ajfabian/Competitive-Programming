/*
 * CF1100-D2-E
 * Idea: binary search + topological sort
 * SC: 2
 * TT: 7
 * CT: 22
 * lev: 6.5
 * Category: binary search, topological sort
 * Interesting.
 * */

#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

struct edg
{
  int u, v, c;
  edg(int u,int v,int c)
    : u(u), v(v), c(c) {}
  int nxt(int x)
  {
    if(x == u) return v;
    return u;
  }
};

const int N = 1e5+7;
vector<edg> g;
void eadd(int u,int v, int c)
{
  g.emplace_back(u, v, c);
}

int n, m;
int pos[N];
bool check(int c)
{
  vector<int> deg(n+1, 0);
  vector<vector<int>> adj(n+1);
  for(edg& e: g)
  {
    if(e.c <= c) continue;
    adj[e.u].push_back(e.v);
    ++deg[e.v];
  }
  
  queue<int> q;
  for(int i=1;i<=n;++i)
  {
    pos[i] = -1;
    if(!deg[i]) q.push(i);
  }
  
  int t = 0;
  while(!q.empty())
  {
    int u = q.front();
    pos[u] = t++;
    q.pop();
    for(int v: adj[u])
    {
      --deg[v];
      if(deg[v] == 0) q.push(v);
    }
  }
  
  for(int i=1;i<=n;++i)
    if(deg[i] != 0) return false;
  return true;
}

int bs(int lo, int hi)
{
  if(hi - lo <= 1)
  {
    if(check(lo)) return lo;
    if(check(lo+1)) return lo+1;
    return lo+2; // wow if this happens
  }
  
  int mid = (lo + hi) / 2;
  if(check(mid)) return bs(lo, mid);
  return bs(mid+1, hi);
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  cin >> n >> m;
  for(int i=1;i<=m;++i)
  {
    int u, v, c;
    cin >> u >> v >> c;
    eadd(u, v, c);
  }
  
  int ans = bs(0, 1e9);
  
  check(ans);
  
  vector<int> vans;
  for(int i=1;i<=m;++i)
  {
    if(g[i-1].c <= ans && pos[g[i-1].u] > pos[g[i-1].v]) vans.push_back(i);
  }
  
  cout << ans << ' ' << vans.size() << endl;
  
  for(int i: vans)
    cout << i << ' ';
  cout << endl;
  
  return 0;
}
