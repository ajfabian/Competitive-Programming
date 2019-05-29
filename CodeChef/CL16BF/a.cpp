/*
 * Idea: Use Topological sort.
 * 
 * We first do a topological sort of the graph a then use dp to compute
 * the total number of paths from start to end.
 *  dp[start] = 1
 *  dp[v] += dp[u] (if edge (u, v) is in the graph)
 * answer is in dp[end].
 * 
 * Complexity: O(N+M)
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

const ll mod = 1e9+7;
const int N = 1e5+7;

ll dp[N];
int deg[N];
vector<int> g[N];
void eadd(int u,int v)
{
  g[u].pb(v);
  ++deg[v];
}


int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int n, m, p, q;
  cin >> n >> m >> p >> q;
  for(int i=1;i<=m;++i)
  {
    int u,v;
    cin >>u >>v;
    eadd(u,v);
  }
  
  queue<int> qq;
  for(int i=1;i<=n;++i)
    if(deg[i] == 0) qq.push(i);
  
  int my=-1, targ=-1;
  vector<int> ord;
  while(!qq.empty())
  {
    int u = qq.front();
    qq.pop();
    if(u == p) my = sz(ord);
    if(u == q) targ = sz(ord);
    ord.pb(u);
    for(int v: g[u])
    {
      --deg[v];
      if(deg[v] == 0) qq.push(v);
    }
  }
  
  dp[p] = 1;
  for(int i = my; i < targ;++i)
  {
    int u = ord[i];
    //~ cerr << u << ": ";
    for(int v: g[u])
    {
      dp[v] = (dp[v] + dp[u]) % mod;
      //~ cerr << v << ' ';
    }
    //~ cerr << endl;
  }
  cout << dp[q] << endl;
  return 0;
}
