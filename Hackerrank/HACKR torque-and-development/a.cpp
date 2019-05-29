/*
 * Idea: just BFS.
 * 
 * For every component of the graph sum to the answer the best option of
 * 1. Build one library and spanning tree of component.
 * 2. Build a library for every node in the component.
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

vector<int> g[N];
int n;
void eadd(int u,int v)
{
  g[u].pb(v);
  g[v].pb(u);
}

bool mk[N];

int bfs(int st)
{
  queue<int> q;
  q.emplace(st);
  mk[st] = 1;
  int ret=1;
  while(!q.empty())
  {
    int u = q.front();
    q.pop();
    for(int v: g[u])
    {
      if(mk[v]) continue;
      mk[v] = true;
      q.push(v);
      ++ret;
    }
  }
  return ret;
}

void clean()
{
  for(int i=1;i<=n;++i)
    mk[i] = false, g[i].clear();
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int tt;
  cin >> tt;
  while(tt--)
  {
    int m;
    ll cl, cr;
    cin >> n >> m >> cl >> cr;
    for(int i=1;i<=m;++i)
    {
      int u,v;
      cin >> u >> v;
      eadd(u,v);
    }
    
    ll ans = 0;
    for(int i=1;i<=n;++i)
    {
      if(mk[i]) continue;
      int tot = bfs(i);
      //~ cerr << tot << endl;
      ans += min(cl + cr * (tot-1), cl * tot);
    }
    cout << ans << '\n';
    clean();
  }
  
  return 0;
}
