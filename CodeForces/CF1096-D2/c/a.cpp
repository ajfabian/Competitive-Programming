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

const ll maxN = 998244353;

ll lcm(ll x, ll y)
{
  ll g = __gcd(x, y);
  return (x/g) * y;
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
    ll a;
    cin >> a;
    ll l = lcm(a, 180ll);
    ll n, r;
    ll P = l;
    n = P / a;
    ll ans=-1;
    while(n <= maxN)
    {
      r = P / 180;
      if(r <= n-2)
      {
        ans = n;
        break;
      }
      P += l;
      n = P / a;
    }
    cout << ans << endl;
  }
  
  return 0;
}
