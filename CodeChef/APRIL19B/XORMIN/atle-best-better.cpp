#include <bits/stdc++.h>
using namespace std;

inline void read(int &x)
{
  x=0;
  int f=1;
  char ch=getchar();
  while(ch<'0'||ch>'9')
  {
    if(ch=='-')f=-1;
    ch=getchar();
  }
  while(ch>='0'&&ch<='9')
  {
    x=x*10+ch-'0';
    ch=getchar();
  }
  x*=f;
}

using pii = pair<int, int>;

#define fr first
#define sc second
#define mp make_pair

const int inf = 1e9;
const int N = 2e5+7;

pii qrys(vector<pii>& ve, int x)
{  
  int l=0, r=ve.size()-1;
  pii res(-1, inf);
  int cur=0;
  for(register int i=19;~i;--i)
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

int n, t = 0, w[N], from[N], to[N], id[N];
vector<pii> st[N<<1];
void build()
{
  for(register int p=n-1, l, r;p;--p)
  {
    l = p<<1, r = (p<<1)|1;
    st[p].resize(st[l].size() + st[r].size());
    merge(st[l].begin(), st[l].end(), st[r].begin(), st[r].end(), st[p].begin());
  }
}

pii qry(int x, int l, int r)
{
  //~ cerr << "========= " << l << ' ' << r << "=============\n";
  pii res(-1, inf), ans;
  for(l+=n, r+=n;l < r; l>>=1, r>>=1)
  {
    //~ cerr << l << ' ' << r << endl;
    if(l&1)
    {
      ans = qrys(st[l++], x);
      if(ans.fr > res.fr || (ans.fr == res.fr && ans.sc < res.sc)) res = ans;
    }
    if(r&1)
    {
      ans = qrys(st[--r], x);      
      if(ans.fr > res.fr || (ans.fr == res.fr && ans.sc < res.sc)) res = ans;
    }
  }

  return res;
}

void print()
{
  for(int i=1;i<2*n;++i)
  {
    cerr << "node: " << i << "-> ";
    for(pii j: st[i])
      cerr << "(" << j.fr << ' ' << j.sc << "),";
    cerr << endl;
  }
}

vector<int> g[N];
inline void eadd(int u, int v)
{
  g[u].push_back(v);
  g[v].push_back(u);
}

void tour(int u=1, int p=0)
{
  //~ cerr << "tour: " << u << endl;
  st[n+t] = {mp(w[u], u)};
  from[u] = t++;
  for(int v: g[u]) if(v != p) tour(v, u);
  to[u] = t;
}


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
  FILE* fi = fopen("int1", "w");
  int tt, q;
  read(tt);
  fprintf(fi, "%d\n", tt);
  while(tt--)
  {
    read(n); read(q);
    fprintf(fi, "%d %d\n", n, q);
    for(register int i=1;i<=n;++i)
    {
      read(w[i]);
      fprintf(fi, "%d ", w[i]);
    }
    fprintf(fi, "\n");
    
    for(register int i=1;i<n;++i)
    {
      int u, v;
      read(u); read(v);
      fprintf(fi, "%d %d\n", u, v);
      eadd(u, v);
    }
    
    tour();
    
    build();
    //~ cerr << "build done (" << 1.0 * clock() / CLOCKS_PER_SEC << "seg)\n";

    //~ print();
    
    register int kl=0, vl=0, a, b, v, k;
    while(q--)
    {
      read(a); read(b);
      fprintf(fi, "%d %d\n", a ^ vl, b ^ kl);
      //~ v = vl ^ a, k = kl ^ b;
      //~ auto ans = qry(k, from[v], to[v]);
      auto ans = qry(b, from[a], to[a]);
      vl = ans.sc, kl = ans.fr;
      printf("%d %d\n", vl, kl);
    }
    cerr << "queries done (" << 1.0 * clock() / CLOCKS_PER_SEC << "seg)\n";
    clean();
  }
  
  return 0;
}
