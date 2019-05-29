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

bool connected(ll a, ll b)
{
  for(int i=1;i<=n;++i)
    rt[i] = i, rk[i] = 1;
    
  int nc = n;
  for(edg e: E)
    if(e.w1 <= a && e.w2 <= b && js(e.u, e.v))
    {
      --nc;
    }
  return nc == 1;
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
  
  ll maxa = 0, maxb = 0;
  
  for(int i=1;i<=m;++i)
  {
    int x, y;
    ll gg, s;
    cin >> x >> y >> gg >> s;
    if(x == y) continue;
    E.eb(x, y, gg * G, s * S);
    maxa= max(maxa, gg * G);
    maxb= max(maxb, s * S);
  }
  
  ll ans = 2e18, lasta=-1, lastb=-1;
  for(ll a = 1; a <= maxa; ++a)
    for(ll b = 1; b <= maxb; ++b)
    {
      if(connected(a, b))
      {
        if(ans > a + b)
          ans = a+b, lasta = a, lastb = b;
      }
    }
  
  cerr << lasta << ' ' << lastb << endl;
  if(ans >= 2e18) cout << "-1\n";
  else cout << ans << endl;
  
  return 0;
}
