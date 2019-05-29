#pragma GCC optimize("Ofast")

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
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

const int inf = 1e9;
const int N = 2e5+7;

struct Trie2
{
  Trie2(){}
  struct node
  {
    node(){}
    int mini=inf;
    int nxt[10]{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  }nullnode;
  vector<node> t{nullnode};

  inline void convert(int val, short p[6])
  {
    int cnt=0;
    while(val > 0)
    {
      p[cnt++] = val % 10;
      val /= 10;
    }
    while(cnt < 6) p[cnt++] = 0;
    reverse(p, p + 6);
  }

  void add(int key, int val)
  {
    short p[6];
    convert(key, p);

    int s = 0;
    for(int i=0;i<6;++i)
    {
      if(t[s].nxt[p[i]] == -1)
      {
        t[s].nxt[p[i]] = sz(t);
        t.pb(nullnode);
      }
      s = t[s].nxt[p[i]];
      t[s].mini = min(t[s].mini, val);
    }
  }

  int qry(int st, int ed)
  {
    //~ assert(st <= ed);
    short S[6], E[6];
    convert(st, S);
    convert(ed, E);

    int s=0, i, sta = 0, ret = inf, s1=-2, s2=-2;
    for(i = 0;i < 6;++i)
    {
      if(S[i] != E[i]) ++ sta;
      if(sta == 0)
      {
        if(t[s].nxt[S[i]] == -1) return inf;
        s = t[s].nxt[S[i]];
      }else
      {
        for(int j=S[i]+1; j<E[i];++j)
          if(~t[s].nxt[j])
            ret = min(ret, t[t[s].nxt[j]].mini);
        s1 = t[s].nxt[S[i]];
        s2 = t[s].nxt[E[i]];
        break;
      }
    }

    if(i == 6) return assert(sta == 0), t[s].mini;

    assert(s1 != -2 && s2 != -2);
    
    int j;
    for(j=i+1;s1 != -1 && j<6;++j)
    {
      for(int k=S[j]+1;k<10;++k) if(~t[s1].nxt[k])
        ret = min(ret, t[t[s1].nxt[k]].mini);
      s1 = t[s1].nxt[S[j]];
    }
    
    if(~s1) assert(j == 6), ret = min(ret, t[s1].mini);
    
    for(j=i+1;s2 != -1 && j<6;++j)
    {
      for(int k=E[j]-1;~k;--k) if(~t[s2].nxt[k])
        ret = min(ret, t[t[s2].nxt[k]].mini);
      s2 = t[s2].nxt[E[j]];
    }
    
    if(~s2) assert(j == 6), ret = min(ret, t[s2].mini);

    return ret;
  }
};

struct node
{
  Trie2 t2;
  int id = inf, nxt[2]{-1, -1};
  node(){}
};
vector<node> t;
void add(int x, int id, int pos)
{
  int s = 0, b, i;
  for(i=19;~i;--i)
  {
    b = x >> i & 1;
    if(t[s].nxt[b] == -1)
    {
      t[s].nxt[b] = sz(t);
      t.pb(node());
    }
    s = t[s].nxt[b];
    t[s].t2.add(pos, id);
  }
  t[s].id = min(t[s].id, id);
}

pii qry(int x, int l, int r)
{
  int xorn = 0, s = 0;
  for(int i=19;~i;--i)
  {
    int b = x >> i & 1;
    if(~t[s].nxt[b^1] && t[t[s].nxt[b^1]].t2.qry(l, r) != inf)
    {
      s = t[s].nxt[b^1];
      xorn += 1 << i;
    }else
      s = t[s].nxt[b];
  }
  
  return mp(xorn, t[s].t2.qry(l, r));
}

int n, dt = 0, w[N], from[N], to[N], id[N];
void initTrie()
{
  t.clear();
  t.pb(node());
  for(int i=1;i<=n;++i)
    add(w[id[i]], id[i], i);
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
  id[++dt] = u;
  from[u] = dt;
  for(int v: g[u]) if(v != p) tour(v, u);
  to[u] = dt;
}


void clean()
{
  dt=0;
  for(int i=1;i<=n;++i)
  {
    g[i].clear();
  }
}

int main()
{
  int tt, q;
  read(tt);
  vector<pii> vans;
  while(tt--)
  {
    read(n); read(q);
    for( int i=1;i<=n;++i) read(w[i]);
    for( int i=1;i<n;++i)
    {
      int u, v;
      read(u); read(v);
      eadd(u, v);
    }
    
    tour();
    
    initTrie();
    cerr << "trie initialized (" << 1.0 * clock() / CLOCKS_PER_SEC << "seg)\n";

    int kl=0, vl=0, a, b, v, k;
    while(q--)
    {
      read(a); read(b); 
      a = 4;
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
