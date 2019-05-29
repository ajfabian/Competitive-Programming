//~ #pragma GCC optimize("Ofast")

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
#define pb push_back
#define sz(x) ((int)(x).size())

const int inf = 1e9;
const int N = 2e5+7;

struct Trie
{
  Trie(){}
  array<int, 5> nullnode{-1, -1, inf, inf, 0};
  vector<array<int, 5>> t{nullnode};
  void add(int key, int val)
  {
    int s = 0;
    for(int i=19;~i;--i)
    {
      int b = key >> i & 1;
      if(t[s][b] == -1)
      {
        t[s][b] = sz(t);
        t.pb(nullnode);
      }
      s = t[s][b];
      t[s][4]++;
      t[s][2] = min(t[s][2], val);
      t[s][3] = key;
    }
  }
  pii qry(int x)
  {
    int s = 0, val = 0;
    for(int i=19; ~i; --i)
    {
      int b = x >> i & 1;
      if(~t[s][b^1])
      {
        s = t[s][b^1];
        val += (b^1) << i;
      }else
      {
        s = t[s][b];
        val += b << i;
      }
      if(t[s][4] == 1) return mp(x ^ t[s][3], t[s][2]);
    }
    return mp(x ^ val, t[s][2]);
  }
};

const int Q = 1e6+1;

int ver=0, n, t = 0, w[N], from[N], to[N], id[N];
vector<Trie> st[Q];
void build()
{
  st[ver].resize(2 * n);
  for(int i=0;i<n;++i)
  {
    int p = n + i;
    while(p)
    {
      st[ver][p].add(w[id[i]], id[i]);
      p>>=1;
    }
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
      ans = st[ver][l++].qry(x);
      if(ans.fr > res.fr || (ans.fr == res.fr && ans.sc < res.sc)) res = ans;
    }
    if(r&1)
    {
      ans = st[ver][--r].qry(x);      
      if(ans.fr > res.fr || (ans.fr == res.fr && ans.sc < res.sc)) res = ans;
    }
  }

  return res;
}


vector<vector<int>> g[Q];
inline void eadd(int u, int v)
{
  g[ver][u].push_back(v);
  g[ver][v].push_back(u);
}

void tour(int u=1, int p=0)
{
  id[t]=u;
  from[u] = t++;
  for(int v: g[ver][u]) if(v != p) tour(v, u);
  to[u] = t;
}


void clean()
{
  t=0;
  ver++;
}

int main()
{
  int tt, q;
  read(tt);
  while(tt--)
  {
    read(n); read(q);
    for(register int i=1;i<=n;++i) read(w[i]);
    g[ver].resize(n+1);
    for(register int i=1;i<n;++i)
    {
      int u, v;
      read(u); read(v);
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
      v = vl ^ a, k = kl ^ b;
      auto ans = qry(k, from[v], to[v]);
      //~ auto ans = qry(b, from[a], to[a]);
      vl = ans.sc, kl = ans.fr;
      printf("%d %d\n", vl, kl);
    }
    //~ cerr << "queries done (" << 1.0 * clock() / CLOCKS_PER_SEC << "seg)\n";
    clean();
  }
  
  return 0;
}
