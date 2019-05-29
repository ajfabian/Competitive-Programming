/*
 * Idea: Use N dijkstras.
 * 
 * It tuns out that it can be solved in N^3 with floyd-warshal.
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

const int N = 444;
const int inf = 1e9;
int dist[N][N];

int cost[N][N];
vector<int> g[N];
void eadd(int u, int v,int c)
{
  g[u].eb(v);
  cost[u][v] = c;
}
int n;

void bfs(int st)
{
  for(int i=1;i<=n;++i)
    dist[st][i] = inf;
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.emplace(0, st);
  dist[st][st] = 0;
  while(!pq.empty())
  {
    int u = pq.top().sc;
    int c = pq.top().fr;
    pq.pop();
    if(dist[st][u] != c) continue;
    for(int v: g[u])
    {
      int w = cost[u][v];
      if(dist[st][v] > c + w)
      {
        dist[st][v] = c + w;
        pq.emplace(c + w, v);
      }
    }
  }
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int m;
  cin >> n >> m;
  for(int i=1;i<=m;++i)
  {
    int u, v, c;
    cin >> u >> v >> c;
    eadd(u, v, c);
  }
  
  for(int i=1;i<=n;++i)
  {
    bfs(i);
  }
  
  int q;
  cin >> q;
  while(q--)
  {
    int a,b;
    cin >> a >> b;
    if(dist[a][b] < inf)cout << dist[a][b]<< '\n';
    else cout << "-1\n";
  }
  
  return 0;
}
