/*
 * Idea: Use MST.
 * 
 * Sps the asnwer is (a,b) notice that they will be in the input.
 * Now sps we know value 'a', then we just need to find if the graph formed
 * by edges with g <= a is connected and what is the minimum value of b
 * that allows me to get this graph still connected. This can be done
 * with simple mst on the graph induced by edges with g <= a, just take the last
 * edge that joined two components in the kruskal algorithm.
 * 
 * This approach as it is will give TLE. But what we can do is to maintain
 * a MST while iterating among all possible a's. This can be done in NlogN 
 * time which is enough.
 * 
 * Complexity: O(M*N+NlogN)
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

const int N = 222;

struct edg
{
  int u, v;
  ll w1, w2;
  edg(int u=0, int v=0, ll w1=0, ll w2=0)
    : u(u), v(v), w1 (w1), w2(w2){}
  bool operator< (const edg& e)const
  {
    return w1 < e.w1;
  }
  void print()
  {
    cerr << u << ' ' << v << ' ' << w1 << ' ' << w2 <<  endl;
  }
};

int n, m;
int rt[N], rk[N];
vector<edg> E;

int fs(int x){if(rt[x] != x) return rt[x] = fs(rt[x]); return x;}
bool js(int  x, int y)
{
  x = fs(x);
  y = fs(y);
  if(x == y) return false;
  if(rk[x] < rk[y]) swap(x, y);
  rk[x] += rk[y];
  rt[y] = x;
  return true;
}

multiset<ll> costs;
set<pair<ll, int>> g[N];

edg findMax(int st, int nd)
{
  vector<bool> mk(n+1, false);
  vector<edg> d(n+1);
  queue<int> q;
  q.push(st);
  d[st] = edg(st, st);
  mk[st] = 1;
  
  //~ cerr << "Q\n";
  while(!q.empty())
  {
    int u = q.front();
    //~ cerr << u << ' ';
    if(u == nd)
    {
      //~ cerr << endl;
      break;
    }
    q.pop();
    for(auto to: g[u])
    {
      ll w = to.fr;
      int v = to.sc;
      if(mk[v]) continue;
      //~ cerr << "to: " << v << ' ' << w << endl;
      mk[v] = 1;
      if(w > d[u].w1)
        d[v] = edg(u, v, w);
      else d[v] = d[u];
      q.push(v);
    }
  }
  return d[nd];
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  cin >> n >> m;
  ll G, S;
  cin >> G >> S;
  
  for(int i=1;i<=m;++i)
  {
    int x, y;
    ll gg, s;
    cin >> x >> y >> gg >> s;
    if(x == y) continue;
    E.eb(x, y, gg * G, s * S);
  }
  
  for(int i= 1; i<= n;++i)
    rt[i] = i, rk[i] = 1;
  sort(all(E));
  
  int nc = n;
  ll ans = 2e18;
  for(edg e: E)
  {
    //~ e.print();
    if(js(e.u, e.v))
    {
      --nc;
      g[e.u].ins(mp(e.w2, e.v));
      g[e.v].ins(mp(e.w2, e.u));
      costs.ins(e.w2);
    }else
    {
      auto p = findMax(e.u, e.v);
      //~ cerr<<"finmax ";
      //~ p.print();
      if(e.w2 < p.w1)
      {
        g[p.u].ers(mp(p.w1, p.v));
        g[p.v].ers(mp(p.w1, p.u));
        costs.ers(costs.find(p.w1));
        
        g[e.u].ins(mp(e.w2, e.v));
        g[e.v].ins(mp(e.w2, e.u));
        costs.ins(e.w2);
      }
    }
    //~ cerr << "no comp: " << nc << endl;
    if(nc == 1) ans = min(ans, e.w1 + *costs.rbegin());
  }
  
  if(ans >= 2e18) cout << "-1\n";
  else cout << ans << endl;
  
  return 0;
}
