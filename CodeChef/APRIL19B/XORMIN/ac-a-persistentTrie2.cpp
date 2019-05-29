/*
 * Idea: Use smaller to large - technique and a persistent trie
 * 
 * While doing the smaller to large technique, the trie of a vertex v
 * is the trie of it's largest child union the elements in the subtrees
 * of the other children, just keep track of what is the root of the 
 * trie corresponding to every vertex.
 * */

#include <bits/stdc++.h>
using namespace std;

#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())

using pii = pair<int, int>;

const int N = 2e5+7, inf = 1e9;

struct node {int id = inf, ch[2]{0, 0};} nullTrie;

vector<node> t;
int n, q, w[N], root[N], rt[N], fa[N];
vector<int> g[N];
vector<vector<pii>> s;

int add(int r, int key, int val)
{
  t.pb(t[r]); r = sz(t)-1;
  int s = r;
  for(int i=19;~i;--i)
  {
    int b = key >> i & 1;
    if(t[s].ch[b]) t.pb(t[t[s].ch[b]]);
    else t.pb(nullTrie);
    s = t[s].ch[b] = sz(t) - 1;
  }
  t[s].id = min(t[s].id, val);
  return r;
}

pii qry(int s, int key)
{
  int xorn = 0;
  for(int i=19;~i;--i)
  {
    int b = key >> i & 1;
    if(t[s].ch[b^1]) s = t[s].ch[b^1], xorn += 1 << i;
    else s = t[s].ch[b];
  }
  return mp(t[s].id, xorn);
}

int fs(int x)
{
  if(fa[x] != x) return fa[x] = fs(fa[x]);
  return x;
}

int js(int x, int y)
{
  x = fs(x);
  y = fs(y);
  if(x == y) return x;
  if(sz(s[x]) < sz(s[y])) swap(x, y);
  fa[y] = x;
  for(pii& e: s[y])
    s[x].pb(e), rt[x] = add(rt[x], e.fr, e.sc);
  return x;
}

int dfs(int u =1, int p = 0)
{
  int mys = sz(s);
  s.pb({mp(w[u], u)});
  rt[mys] = add(0, w[u], u);

  for(int v: g[u]) if(v != p)
    mys = js(mys, dfs(v, u));

  root[u] = rt[mys];
  return mys;
}

void clean()
{
  s.clear();
  //~ t.clear();
  for(int i=1;i<=n;++i) g[i].clear();
}

int main()
{
  //~ freopen("in", "r" ,stdin);
  int tt;
  scanf("%d", &tt);
  while(tt--)
  {
    scanf("%d%d", &n, &q);
    for(int i=1;i<=n;++i) scanf("%d", w + i);
    for(int i=1;i<n;++i)
    {
      int u, v;
      scanf("%d%d", &u, &v);
      g[u].pb(v);
      g[v].pb(u);
    }

    t.clear(); t.pb(nullTrie);
    for(int i=0;i<=n;++i) fa[i] = i;
    dfs();

    int xl=0, vl=0;
    while(q--)
    {
      int a, b;
      scanf("%d%d", &a, &b);
      vl ^= a; xl ^= b;
      tie(vl, xl) = qry(root[vl], xl);
      cout << vl << ' ' << xl << '\n';
    }

    clean();
  }

  return 0;
}
