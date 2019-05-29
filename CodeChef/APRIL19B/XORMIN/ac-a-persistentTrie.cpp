/*
 * Idea: use persistent trie.
 * 
 * Create a trie for every prefix of an euler tour of the tree and in
 * each node of the trie keep the count of numbers passing through it
 * (done efficiently with persistence), then for a range query (l, r)
 * move simultaniously in both l-1 and r tries only if the count from both
 * differs in at least one.
 * */

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(x) ((int)(x).size())
#define mp make_pair

const int N = 2e5+7;

int n, q, dt=0, w[N], id[N], st[N], nd[N];
vector<int> g[N];

void tour(int u=1, int p=0)
{
  id[st[u] = ++dt] = u;
  for(int v: g[u]) if(v != p) tour(v, u);
  nd[u] = dt;
}

struct node {int c=0;int ch[2]{-1, -1};} nullTrie;
vector<node> t;

int upd(int lr, int key)
{
  int r = sz(t); t.pb(t[lr]);
  for(int i=19, s = r, nv, b;~i;--i)
  {
    b = key >> i & 1, nv = sz(t);
    if(~t[s].ch[b]) t.pb(t[t[s].ch[b]]);
    else t.pb(nullTrie);
    s = t[s].ch[b] = nv;
    t[s].c++;
  }
  return r;
}

int qry(int s1, int s2, int key)
{
  int xorn = 0;
  for(int i=19;~i;--i)
  {
    int b = key >> i & 1;
    if(s1 == -1)
    {
      if(~t[s2].ch[b^1]) s2 = t[s2].ch[b^1], xorn += 1 << i;
      else s2 = t[s2].ch[b];
    }else
    {
      if(~t[s2].ch[b^1])
      {
        if(t[s1].ch[b^1] == -1 || t[t[s2].ch[b^1]].c - t[t[s1].ch[b^1]].c > 0)
          s1 = t[s1].ch[b^1], s2 = t[s2].ch[b^1], xorn += 1 << i;
        else
          s1 = t[s1].ch[b], s2 = t[s2].ch[b];
      }else s1 = t[s1].ch[b], s2 = t[s2].ch[b];
    }
  }
  return xorn ^ key;
}

int Log2[N];
void init()
{
  int x = -1;
  for(int i=1;i<N;++i)
  {
    if(!(i&(i-1)))++x;
    Log2[i]=x;
  }
}

struct RMQ
{
  using pii = pair<int, int>;
  #define fr first
  #define sc second

  vector<vector<pii>> t;

  RMQ():t(1){}

  void add(pii x){t[0].pb({x});}

  pii mn(pii& a, pii& b)
  {
    if(a.sc < b.sc) return a;
    return b;
  }

  void build()
  {
    int n = sz(t[0]);
    for(int k=1;(1<<k)<=n;++k)
    {
      t.pb({});
      for(int i=0;i+(1<<(k-1))<n;++i)
        t[k].pb(mn(t[k-1][i], t[k-1][i+(1 << (k-1))]));
    }
  }

  int qry(int l, int r)
  {
    int d=Log2[r-l+1];
    return mn(t[d][l],t[d][r-(1<<d)+1]).sc;
  }

  #undef fr
  #undef sc
};

int clean()
{
  dt = 0;
  t.clear();
  for(int i=1;i<=n;++i) g[i].clear();
}

int main()
{
  //~ freopen("in", "r", stdin);
  init();

  int tt;
  cin >> tt;
  while(tt--)
  {
    cin >> n >> q;
    for(int i=1;i<=n;++i) cin >> w[i];
    for(int u, v, i=1;i<n;++i)
    {
      cin >> u >> v;
      g[u].pb(v);
      g[v].pb(u);
    }

    tour();

    vector<int> root(n+1, 0);
    t.pb(nullTrie);
    for(int i=1;i<=n;++i) root[i] = upd(root[i-1], w[id[i]]);

    vector<int> vals;
    for(int i=1;i<=n;++i) vals.pb(w[i]);
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    vector<RMQ> rmq(sz(vals));
    for(int i=1;i<=n;++i)
    {
      int lb = lower_bound(vals.begin(), vals.end(), w[id[i]]) - vals.begin();
      rmq[lb].add(mp(i, id[i]));
    }
    for(RMQ& r: rmq) r.build();

    int a, b, vl = 0, xl = 0;
    while(q--)
    {
      cin >> a >> b;
      vl ^= a;
      xl ^= b;
      int nx = qry(root[st[vl] - 1], root[nd[vl]], xl);
      int pos = lower_bound(vals.begin(), vals.end(), nx) - vals.begin();
      a = lower_bound(rmq[pos].t[0].begin(), rmq[pos].t[0].end(), mp(st[vl], 0)) - rmq[pos].t[0].begin();
      b = upper_bound(rmq[pos].t[0].begin(), rmq[pos].t[0].end(), mp(nd[vl], N)) - rmq[pos].t[0].begin();
      vl = rmq[pos].qry(a, b-1);
      //~ printf("%d %d\n", vl, xl ^= nx);
      cout << vl << ' ' << (xl ^= nx) << '\n';
    }
    clean();
  }

  return 0;
}
