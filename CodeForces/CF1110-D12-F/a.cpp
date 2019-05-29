#pragma GCC optimize("Ofast")


#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<int, int> pll;


#define fr first
#define sc second

const int N = 5e5+7;
const ll inf = 1e15;

vector<pll> g[N];
inline void eadd(int u,int v,ll w)
{
  g[u].emplace_back(w, v);
  g[v].emplace_back(w, u);
}

typedef pair<int, int> query;
vector<query> Q;
vector<int> qs[N];
inline void qadd(int u, int l, int r)
{
  Q.emplace_back(l, r);
  qs[u].emplace_back(Q.size()-1);
}
ll ans[N];

int sz[N],mc[N],pz[N],q[N];
bool mk[N];
int gc(int st)
{
  int b=0,e=0;
  q[e++]=st, mc[st]=0, pz[st]=-1, sz[st]=1;
  while(b<e)
  {
    int u=q[b++];
    for(auto to: g[u])
    {
      int v = to.sc;
      if(pz[u]==v||mk[v])continue;
      pz[v]=u;
      mc[v]=0;
      sz[v]=1;
      q[e++]=v;
    }
  }
  for(int i=e-1;~i;--i)
  {
    int u=q[i];
    int bc=max(e-sz[u],mc[u]);
    if(2*bc<=e)
    {
      st=u;
      break;
    }
    sz[pz[u]]+=sz[u];
    mc[pz[u]]=max(mc[pz[u]], sz[u]);
  }
  return st;
}

ll tree[4 * N];
int n, qq;
int used[N], tp=0;
//~ int ppos[N];
void tbuild(int i, int lo, int hi)
{
  if(lo == hi)
  {
    tree[i] = inf;
    //~ ppos[lo] = i;
    return ;
  }
  int m = lo+hi>>1, l, r;
  tbuild(l = i << 1, lo, m);
  tbuild(r = l | 1, m+1, hi);
  tree[i] = inf;
}

void tupd(int x, ll val, int i, int lo,int hi)
{
  if(x > hi || x < lo) return ;
  if(lo == hi)
  {
    tree[i] = val;
    //~ used.push_back(i);
    used[tp++] = i;
    return ;
  }
  int m = lo+hi>>1, l, r;
  tupd(x, val, l = i << 1, lo, m);
  tupd(x, val, r = l | 1, m+1, hi);
  tree[i] = min(tree[l], tree[r]);
}

ll tqry(int x, int y, int i, int lo, int hi)
{
  if(y < lo || x > hi) return inf;
  if(x <= lo && hi <= y) return tree[i];
  int m = lo+hi>>1;
  return min(tqry(x, y, i << 1, lo, m), tqry(x, y, (i<<1)|1, m+1, hi));
}

void upd(int u, int p=0, ll dist=0)
{
  if(g[u].size() == 1)
  {
    //~ cerr << "updating: " << u << ' ' << dist << endl;
    tupd(u, dist, 1, 1, n);
    //~ assert(ppos[u]);
    return;
  }
  
  for(auto to : g[u])
  {
    if(to.sc == p || mk[to.sc] == 1) continue;
    upd(to.sc, u, dist + to.fr);
  }
}


void calc(int u, int p=0, ll dist=0)
{
  for(int qi: qs[u])
  {
    ll tmp = tqry(Q[qi].fr, Q[qi].sc, 1, 1, n);
    //~ cerr <<  u << "querying : " << Q[qi].fr <<' ' <<  Q[qi].sc  << "is " << tmp << endl;
    ans[qi] = min(ans[qi], dist + tmp);
  }
  for(auto to : g[u])
  {
    if(to.sc == p || mk[to.sc] == 1) continue;
    calc(to.sc, u, dist + to.fr);
  }
}

void solve(int u)
{
  upd(u);
  calc(u);
  for(int i=0;i<tp;++i)
    while(used[i])
    {
      tree[used[i]] = inf;
      used[i] >>= 1;
    }
  //~ cerr <<" " << used.size() << endl;
  tp = 0;
}

void dfs(int u=1)
{
  u = gc(u);
  mk[u] = 1;
  //~ cerr << "cent: " << u << ' ';
  
  solve(u);
  
  for(auto to: g[u])
  {
    if(mk[to.sc]) continue;
    dfs(to.sc);
  }
}

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

int main()
{
  scanf("%d%d", &n, &qq);
  for(int i=2;i<=n;++i)
  {
    int p; read(p);
    int w; read(w);
    eadd(i, p, w);
  }
  
  for(int i=0;i<qq;++i)
  {
    int u, l, r;
    read(u);
    read(l);
    read(r);
    //~ scanf("%d%d%d", &u, &l, &r);
    qadd(u, l, r);
  }
    
  for(int i=0;i<qq;++i)
    ans[i] = inf;
  
  tbuild(1, 1, n);
  
  dfs();
  
  //~ solve(3);
  
  for(int i=0;i<qq;++i)
    printf("%lld\n", ans[i]);
  
  return 0;
}
