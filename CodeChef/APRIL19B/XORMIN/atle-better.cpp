#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

#define fr first
#define sc second
#define mp make_pair

const int inf = 1e9;
const int N = 2e5+7;

pii qrys(vector<pii>& ve, int x)
{
  //~ cerr << "query: " << x << "\n";
  //~ for(pii i: ve) cerr << "(" << i.fr << ',' << i.sc << ")\n";
  
  int l=0, r=ve.size()-1;
  pii res(-1, inf);
  int cur=0;
  for(int i=19;~i;--i)
  {
    int p = lower_bound(ve.begin()+l, ve.begin()+r+1, mp(cur + (1 << i), 0)) - ve.begin();
    if(x >> i & 1)
    {
      if(p == l) // no zeroes
        res = ve[p], cur += 1 << i;
      else r=p-1;
    }else
    {
      if(p == r+1) // no ones
        ;
      else res = ve[p], cur += 1 << i, l = p;
    }
  }
  //~ assert(~res.fr);
  res.fr ^= x;
  return res;
}

struct SegmentTree
{
  int n;
  vector<vector<pii>> st;
  
  SegmentTree(vector<pii>& A)
    : n(A.size()-1), st(A.size() << 4)
  {
    build(A);
    //~ print();
  }
  
  void build(vector<pii>& A, int i=1, int lo=1, int hi = -1)
  {
    if(hi == -1) hi = n;
    if(lo == hi)
    {
      st[i].push_back(A[lo]);
      return;
    }
    int m = lo + hi >> 1, l, r;
    build(A, l=i<<1, lo, m);
    build(A, r=l|1, m+1, hi);
    
    st[i].resize(st[l].size() + st[r].size());
    merge(st[l].begin(), st[l].end(), st[r].begin(), st[r].end(), st[i].begin());
  }
  
  pii qry(int x, int l, int r, int i=1, int lo=1, int hi=-1)
  {
    if(hi == -1) hi = n;
    if(l <= lo && hi <= r) return qrys(st[i], x);
    if(lo > r || hi < l) return mp(-1, inf);
    int m = lo + hi  >> 1;
    
    pii lans = qry(x, l, r, i << 1, lo, m);
    pii rans = qry(x, l, r, (i << 1)|1, m+1, hi);
    
    if(lans.fr > rans.fr) return lans;
    if(lans.fr < rans.fr) return rans;
    if(lans.sc < rans.sc) return lans;
    return rans;
  }
  
  void print()
  {
    for(int i=1;i<st.size();++i)
    {
      cerr << "node: " << i << "-> ";
      for(pii j: st[i])
        cerr << "(" << j.fr << ' ' << j.sc << "),";
      cerr << endl;
    }
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
    vector<pii> aa(n+1);
    for(int i=1;i<=n;++i)
    {
      aa[i] = mp(w[id[i]], id[i]);
      //~ cerr << id[i] << " \n"[i==n];
    }
    
    int kl=0, vl=0;
    SegmentTree st(aa);
    cerr << "Segment tree (" << 1.0 * clock() / CLOCKS_PER_SEC << "seg)\n";

    while(q--)
    {
      int a, b;
      scanf("%d%d", &a, &b);
      int v = vl ^ a;
      int k = kl ^ b;
      //~ cerr << "qryl: " << vl << ' ' << kl << endl;
      cerr << "qry: " << v << ' ' << k << "( " << from[v] << '-' << to[v] << ")\n";
      auto ans = st.qry(k, from[v], to[v]);
      //~ a = 4;
      //~ auto ans = st.qry(b, from[a], to[a]);
      printf("%d %d\n", ans.sc, ans.fr);
      vl = ans.sc;
      kl = ans.fr;
    }
        cerr << "queries done (" << 1.0 * clock() / CLOCKS_PER_SEC << "seg)\n";

    clean();
  }
  
  return 0;
}
