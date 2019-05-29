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

const ll inf = 1e15;
ll n, x, y, d;

ll cost(ll a, ll b)
{
  if(a == b) return 0;
  ll s = (labs(b-a) + d - 1) / d;
  if(a < b)
  {
    ll na = a + s * d;
    if(na == b || b == n) return s;
    return inf;
  }
  ll na = a - s * d;
  if(na == b || b == 1) return s;
  return inf;
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
    cin >> n >> x >> y >> d;
    //~ cerr << cost(x,y) << endl;
    //~ cerr << cost(x, 1) + cost(1, y) << endl;
    //~ cerr << cost(x, n) + cost(n, y) << endl;
    ll ans=min({cost(x,y), cost(x, 1) + cost(1, y), cost(x, n) + cost(n, y)});
    if(ans < inf)cout << ans << endl;
    else cout << -1 << endl;
  }
  
  return 0;
}
