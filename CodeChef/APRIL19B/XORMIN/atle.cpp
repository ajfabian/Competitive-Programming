#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

#define fr first
#define sc second
#define mp make_pair

const int inf = 1e9;
const int N = 2e5+7;

struct node
{
  int id;
  vector<node*> nxt;
  node() : nxt(2, nullptr), id(inf){}
};

void wadd(node* r, int x, int id)
{
  for(int i=19;~i;--i)
  {
    int b = x >> i & 1;
    if(r->nxt[b] == nullptr) r->nxt[b] = new node;
    r = r->nxt[b];
  }
  r->id = min(r->id, id);
}

pair<int, int> qrys(node* r, int x)
{
  int xorn=0;
  for(int i=19;~i;--i)
  {
    int b = x >> i & 1;
    if(r->nxt[b^1] != nullptr)
    {
      xorn |= 1 << i;
      r = r->nxt[b^1];
    }else r = r->nxt[b];
  }
  return make_pair(xorn, r->id);
}

struct SegmentTree
{
  int n;
  vector<pii> a; // pair(val, id)
  vector<node*> st;
  SegmentTree(vector<pii>& a)
    : n(a.size()-1), a(a), st(a.size() << 4) // a is 1-indexed
  {
    for(auto& i: st) i = new node;
    for(int i=1;i<=n;++i) enter(i, a[i]);
  }
  
  void enter(int x, pii v, int i=1, int lo=1, int hi=-1)
  {
    if(hi==-1) hi=n;
    
    if(x > hi || x < lo) return;
    if(lo == hi)
    {
      wadd(st[i], v.fr, v.sc);
      return;
    }
    
    int m = lo + hi >> 1;
    enter(x, v, i<<1, lo, m);
    enter(x, v, (i<<1)|1, m+1, hi);
    
    wadd(st[i], v.fr, v.sc);
  }
  
  pii qry(int v, int x, int y, int i=1, int lo=1, int hi=-1)
  {
    if(hi == -1) hi = n;
    if(x <= lo && hi <= y) return qrys(st[i], v);
    
    if(x > hi || y < lo) return mp(-1, inf);
    
    int m = lo + hi >> 1;
    
    pii lans = qry(v, x, y, i<<1, lo, m);
    pii rans = qry(v, x, y, (i<<1)|1, m+1, hi);
    
    if(lans.fr > rans.fr) return lans;
    if(rans.fr > lans.fr) return rans;
    if(lans.sc < rans.sc) return lans;
    return rans;
  }
};

vector<int> g[N];
void eadd(int u, int v)
{
  g[u].push_back(v);
  g[v].push_back(u);
}

int from[N], to[N], id[N], t = 0;
void tour(int u=1, int p=0)
{
  //~ cerr << "tour: " << u << endl;
  id[++t] = u;
  from[u] = t;
  for(int v: g[u]) if(v != p) tour(v, u);
  to[u] = t;
}

int n, q;
void clean()
{
  t=0;
  for(int i=1;i<=n;++i)
  {
    g[i].clear();
  }
}

int main()
{
  int tt;
  scanf("%d", &tt);
  while(tt--)
  {
    scanf("%d%d", &n, &q);
    vector<int> w(n+1);
    for(int i=1;i<=n;++i) scanf("%d", &w[i]);
    for(int i=1;i<n;++i)
    {
      int u, v;
      scanf("%d%d", &u, &v);
      eadd(u, v);
    }
    
    tour();
    
    //~ cerr << "t = " << t << endl;
    vector<pii> a(n+1);
    for(int i=1;i<=n;++i)
    {
      a[i] = mp(w[id[i]], id[i]);
      //~ cerr << id[i] << " \n"[i==n];
    }
    
    int kl=0, vl=0;
    SegmentTree st(a);
    while(q--)
    {
      int a, b;
      scanf("%d%d", &a, &b);
      int v = vl ^ a;
      int k = kl ^ b;
      //~ cerr << "qryl: " << vl << ' ' << kl << endl;
      //~ cerr << "qry: " << v << ' ' << k << "( " << from[v] << '-' << to[v] << ")\n";
      auto ans = st.qry(k, from[v], to[v]);
      printf("%d %d\n", ans.sc, ans.fr);
      vl = ans.sc;
      kl = ans.fr;
    }
    clean();
  }
  
  return 0;
}
