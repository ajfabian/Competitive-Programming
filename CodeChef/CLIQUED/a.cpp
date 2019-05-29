/*
 * Idea: Dijkstra.
 * 
 * First we build a new network from the one given in the input. 
 * we say that nodes 1..k are compressed in node k and the cost for entering
 * such node is X, then for every one of then a new node also is created,
 * this allows paths that do not enter the clique and just touch it.
 * After this we only need to run dijkstra from node S.
 * If node S is inside the clique we run dijkstra from node K and from
 * node S+n.
 * 
 * Complexity: O(N+MlogN);
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

const int N = 3e5+7;


int n, k, m, s, extra=0;
ll x;
vector<pair<ll,int>> g[N];
void eadd(int u,int v,ll w)
{
  g[max(k,u)].eb(w, max(k,v));
  g[max(k,v)].eb(w, max(k,u));
  if(u <= k && v <= k) return;
  if(u <= k)
  {
    g[u+n].eb(w, v);
    g[v].eb(w, u+n);
  }
  if(v <= k)
  {
    g[v+n].eb(w, u);
    g[u].eb(w, v+n);
  }
}


const ll inf = 1e18;
ll cost[N];
ll dist[N];
void dijkstra()
{
  for(int i=1;i<=n+k;++i)
    dist[i] = inf;
  priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
  
  if(s <= k)
  {
    pq.emplace(cost[s], k);
    dist[k] = cost[s];
    pq.emplace(0, s+n);
    dist[s+n] = 0;
  }else 
  {
    pq.emplace(0, s);
    dist[s] = 0;
  }
  
  while(!pq.empty())
  {
    int u = pq.top().sc;
    ll c = pq.top().fr;
    pq.pop();
    if(c != dist[u]) continue;
    for(auto to: g[u])
    {
      if(dist[to.sc] > c + to.fr + cost[to.sc])
      {
        dist[to.sc] = c + to.fr + cost[to.sc];
        pq.emplace(c + to.fr + cost[to.sc], to.sc);
      }
    }
  }
}

void clean()
{
  for(int i=1;i<=n+k;++i)
  {
    g[i] .clear();
    cost[i] = 0;
    dist[i] = 0;
  }
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  int tt;
  scanf("%d", &tt);
  while(tt--)
  {
    scanf("%d%d%lld%d%d", &n, &k, &x, &m, &s);
    for(int i=1;i <= m;++i)
    {
      int u,v;
      ll w;
      scanf("%d%d%lld", &u, &v, &w);
      eadd(u,v,w);
    }
    for(int i=1;i<=k;++i)
      cost[i] = x;
    
    dijkstra();
    //~ return 0;
    for(int i=1;i<=n;++i)
    {
      if(i <= k)
        printf("%lld%c", min(dist[max(k, i)], dist[i+n]), " \n"[i == n]);
      else printf("%lld%c", dist[i], " \n"[i == n]);
    }
    clean();
  }
  
  return 0;
}
