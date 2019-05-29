/*
 * Idea: Use MST and LCA.
 * 
 * Build Minimum spanning tree and answer the queries in log C just
 * finding the maximum element in the path of the Tree.
 * */

#include <bits/stdc++.h>
using namespace std;

const int N = 3333;

struct edge
{
  int u, v, w;
  edge(int u,int v,int w)
  : u(u), v(v), w(w){}
  bool operator< (const edge& e)const
  {
    return w < e.w;
  }
};

int rt[N], rk[N];
int fs(int x)
{
  if(rt[x] != x) return rt[x] = fs(rt[x]);
  return x;
}

bool js(int x, int y)
{
  x = fs(x);
  y = fs(y);
  if(x == y) return false;
  if(rk[x] < rk[y]) swap(x, y);
  rk[x] += rk[y];
  rt[y] = x;
  return true;
}

typedef pair<int,int> pii;
#define fr first 
#define sc second

int p[N][13], lv[N];
int cc[N][13];
void blca(vector<vector<pair<int,int>>>& g)
{
  int n = g.size();
  for(int i=1;i<=n;++i) memset(p[i], 0, sizeof p[i]);
  queue<int> q;
  q.push(1);
  lv[1] = 0;
  while(!q.empty())
  {
    int u = q.front();
    q.pop();
    for(pii& to: g[u])
    {
      if(p[u][0] == to.sc) continue;
      p[to.sc][0] = u;
      cc[to.sc][0] = to.fr;
      lv[to.sc] = lv[u] + 1;
      q.push(to.sc);
    }
  }
  
  for(int i=1;i<13;++i)
    for(int j = 1;j <= n; ++j)
    {
      p[j][i] = p[p[j][i-1]][i-1];
      cc[j][i] = max(cc[j][i-1], cc[p[j][i-1]][i-1]);
    }
}

int qry(int u, int v)
{
  if(lv[u] < lv[v]) swap(u, v);
  int res = 0;
  for(int i=12;~i;--i)
    if(p[u][i] && lv[p[u][i]] >= lv[v])
    {
      res = max(res, cc[u][i]);
      u = p[u][i];
    }
  if(u == v) return res;
  for(int i=12;~i;--i)
    if(p[u][i] != p[v][i])
    {
      res = max({res, cc[u][i], cc[v][i]});
      u = p[u][i];
      v = p[v][i];
    }
  res = max({res, cc[u][0], cc[v][0]});
  return res;
}

int c, l, h;

int main()
{
  while(scanf("%d%d%d", &c, &l, &h), ~c && ~l && ~h)
  {
    vector<edge> g;
    for(int i = 1;i <= l;++i)
    {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      g.emplace_back(u, v, w);
    }
    sort(g.begin(), g.end());
    
    vector<vector<pair<int, int>>> tree(c+1);
    for(int i=1;i<=c;++i)
      rt[i] = i, rk[i] = 1;
    for(edge& e: g)
    {
      if(js(e.u, e.v))
      {
        tree[e.u].emplace_back(e.w, e.v);
        tree[e.v].emplace_back(e.w, e.u);
      }
    }
    
    blca(tree);
    
    vector<int> ans;
    while(h--)
    {
      int s, t;
      scanf("%d%d", &s, &t);
      ans.push_back(qry(s,t));
    }
    for(int i=0;i<(int)ans.size();++i)
      printf("%d%c", ans[i], " \n"[i+1 == (int)ans.size()]);
  }
  return 0;
}
