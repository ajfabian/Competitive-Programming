/*
 * Idea: For every vertex sort and hash it's adjacency list,
 * then a possibility (u, v) is when this vertexes aren't friends
 * and another is when they are.
 * > if they are not friends then they adjacency list must match exactly
 * this means that ans sohuld count nC2 where n is the number of elements having same adj. list
 * > if they are friends then they are adjacents, so for every vertex
 * check it's adj. vertexes and see if their hashes coincide when removing
 * each element from it's friend list.
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

typedef unsigned long long ull;
const int N = 1e6+7;

vector<int> g[N];
void eadd(int u,int v)
{
  g[u].pb(v);
  g[v].pb(u);
}

const ull BASE = 1299709;
const ull mod = 1e9+7;
const ull mod1 = 1e9+3;
vector<ull> Hash[N];
vector<ull> Hash1[N];
pair<ull, ull> hashit(int u)
{
  if(sz(g[u]) == 0) return mp(0, 0);
  Hash[u] = vector<ull> (sz(g[u]));
  Hash1[u] = vector<ull> (sz(g[u]));
  sort(all(g[u]));
  Hash[u][0] = (ull)(g[u].front());
  Hash1[u][0] = (ull)(g[u].front());
  
  for(int i=1;i<sz(g[u]);++i)
  {
    Hash[u][i] = (Hash[u][i-1] * BASE % mod + (ull)(g[u][i])) % mod;
    Hash1[u][i] = (Hash1[u][i-1] * BASE % mod1 + (ull)(g[u][i])) % mod1;
  }
  return mp(Hash[u].back(), Hash1[u].back());
}

ull powe[2][N];
ull getHash(vector<ull>& h, int l, int r, ll m, int i)
{
  if(r < l || sz(h) == 0) return 0;
  if(l > 0) return (h[r] + m - h[l-1] * powe[i][r - l + 1] % m) % m;
  return h[r];
}

ull nHash(vector<ull>& h, int pp, ull m, int i)
{
  ull lhash = getHash(h, 0, pp-1, m, i);
  ull rhash = getHash(h, pp+1, sz(h)-1, m, i);
  
  ull nhash = (lhash * powe[i][sz(h)-1 - (pp+1) + 1] % m + rhash) % m;
  return nhash;
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  powe[0][0] = 1;
  powe[1][0] = 1;
  for(int i=1;i<N;++i) powe[0][i] = powe[0][i-1] * BASE % mod;
  for(int i=1;i<N;++i) powe[1][i] = powe[1][i-1] * BASE % mod1;
  
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i=1;i<=m;++i)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    eadd(u, v);
  }
  
  map<pair<ull, ull>, ll> f;
  for(int i=1;i<=n;++i)
  {
    f[hashit(i)]++;
    //~ cout << "HASH of " << i << " is " << tmp << endl;
  }
  
  ll ans = 0;
  for(auto it: f)
    ans += it.sc * (it.sc - 1) / 2;
  
  
  ll tmp = 0;
  for(int i=1;i<=n;++i)
  {
    for(int j=0;j<sz(g[i]);++j)
    {
      int v = g[i][j];
      int pp1 = j, pp2 = lb(all(g[v]), i) - g[v].begin();
      if(nHash(Hash[i], pp1, mod, 0) == nHash(Hash[v], pp2, mod, 0) &&
        nHash(Hash1[i], pp1, mod1, 1) == nHash(Hash1[v], pp2, mod1, 1)) ++ tmp;
    }
  }
  
  debug("%lld", tmp / 2ll);
  
  cout << ans + tmp / 2ll << endl;
  
  return 0;
}
