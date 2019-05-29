// editorial: https://codeforces.com/blog/entry/63461
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

vector<int> g[N];
void eadd(int u,int v)
{
  g[u].pb(v);
  g[v].pb(u);
}

int ssz[N];

void dfs(int u, vector<int>& t, int p = 0)
{
  if(u != 1 && sz(g[u]) == 1)
    ssz[u] = 1;
  for(int v: g[u])
  {
    if(v == p) continue;
    dfs(v, t, u);
    ssz[u] += ssz[v];
  }
  t.pb(ssz[u]);
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  int n;
  scanf("%d", &n);
  if(n == 1)
  {
    cout << 1 << endl;
    return 0;
  }
  for(int i=2;i<=n;++i)
  {
    int p;
    scanf("%d", &p);
    eadd(p, i);
  }
  
  vector<int> t;
  dfs(1, t);
  
  sort(all(t));
  printVector(t);
  
  return 0;
}
