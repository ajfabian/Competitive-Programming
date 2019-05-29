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

struct edg
{
  int u, v, w;
  edg(int u, int v, int w)
  :  u(u), v(v), w(w){}
  bool operator< (const edg& e)const
  {
    return w < e.w;
  }
};

const int N = 1e5+7;

int rt[N], rk[N];

int fs(int x)
{
  if(rt[x] != x) return rt[x] = fs(rt[x]);
  return x; 
}

bool mk[N];

bool js(int x, int y)
{
  x = fs(x);
  y = fs(y);
  if(x == y) return false;
  
  bool takeit = mk[x] && mk[y];
  
  mk[x] = mk[x] || mk[y];
  
  rk[x] += rk[y];
  rt[y] = x;
  
  return takeit;
}

typedef vector<vector<pair<int,int>>> graph;


int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  int n ,m, k;
  scanf("%d%d%d", &n, &m, &k);
  
  vector<int> special;
  for(int i=1;i<=k;++i)
  {
    int x; scanf("%d", &x);
    mk[x] = 1;
    special.pb(x);
  }
  
  vector<edg> E;
  for(int i=1;i<=m;++i)
  {
    int u,v,w;
    scanf("%d%d%d", &u, &v, &w);
    E.eb(u, v, w);
  }
  
  //~ vector<vector<pair<int,int>>> g(n + 1);
  
  for(int i=1;i<=n;++i)
    rt[i] = i, rk[i] = 1;
  
  sort(all(E));
  int ans = 0;
  for(edg& e: E)
  {
    if(js(e.u, e.v)) ans = max(ans, e.w);
  }
  
  for(int i = 1; i <= k; ++i)
    printf("%d ", ans);
  printf("\n");
  
  return 0;
}
