/*
 * Idea: Use MST.
 * 
 * The shortest path from node A to B is the one that has the minimum
 * maximum value on an edge this implies that paths induce a MST, so
 * the problem reduces to compute the sum over all paths on a tree,
 * this can be done in linear time with DFS.
 * */

#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define INIT ios_base::sync_with_stdio(false);\
             cin.tie(0),cout.tie()
#define endl '\n'
#define fr first
#define sc second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define ers erase
#define sz(c) ((int)(c).size())
#define all(x) (x).begin(),(x).end()
#define unique(x) (x).resize(unique(all(x))-(x).begin())
#define debug(_fmt,...) \
fprintf(stderr,"("#__VA_ARGS__ ") = (" _fmt")\n",__VA_ARGS__)

template<class T>
void na(vector<T>& a, int n)
{a = vector<T>(n);for(T& i: a) cin >> i;}
template<class T>
void printVector(vector<T>& a)
{for(T& i: a) cout << i << ' '; cout << endl;}
template<class T>
vector<T> shrink(vector<T>& x)
{
  vector<T> vals = x;
  sort(all(vals)); unique(vals);
  for(T& i: x) i = ub(all(vals), i) - vals.begin();
  return vals;
}

const int N = 1e5+7;
const int M = 4e5+7;

int n,m;
int ans[M];

struct edg
{
  int u,v,w;
  edg(int u,int v,int w)
    : u(u), v(v), w(w){}
  bool operator<(const edg& e)const
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

vector<int> toBinary(ll val)
{
  vector<int> res;
  if(val == 0) res.pb(0);
  while(val)
  {
    res.pb(val%2);
    val /= 2;
  }
  return res;
}

int lastBit = 0;
void updAns(ll val, int pos)
{
  //~ cerr << val << ' ' << pos << endl;
  vector<int> binar = toBinary(val);
  int carr = 0;
  auto it = binar.begin();
  int i;
  for(i=pos;it != binar.end();++i,++it)
  {
    int tmp = (*it + ans[i] + carr)%2;
    if(*it + ans[i] + carr > 1) carr = 1;
    else carr = 0;
    ans[i] = tmp;
    lastBit = max(lastBit, i);
  }
  while(carr)
  {
    int tmp = (ans[i] + carr)%2;
    if(ans[i] + carr > 1) carr = 1;
    else carr = 0;
    ans[i] = tmp;
    lastBit = max(lastBit, i);
    ++i;
  }
}

vector<pii> g[N];

int dfs(int u=1,int p=0)
{
  int sz = 1;
  for(pii to: g[u])
  {
    int w = to.fr;
    int v = to.sc;
    if(v == p) continue;
    int A = dfs(v, u);
    int B = n - A;
    
    ll tot = 1ll * A * B;
    //~ cerr << u << ' ' << A << ' ' << B << endl;
    
    updAns(tot, w);
    
    sz += A;
  }
  return sz;
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  vector<edg> E;
  scanf("%d%d", &n, &m);
  for(int i=1;i<=m;++i)
  {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    E.eb(u, v, w);
  }
  
  sort(all(E));
  for(int i=1;i<=n;++i)
    rt[i] = i, rk[i] =1;
  for(edg e: E)
  {
    if(js(e.u, e.v))
      g[e.u].eb(e.w, e.v),
      g[e.v].eb(e.w, e.u);
  }
  lastBit=0;
  dfs();
  
  for(int i=lastBit;~i;--i)
    printf("%d", ans[i]);
  printf("\n");
  
  return 0;
}
