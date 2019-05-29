#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

typedef double d;
typedef long long int ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define INIT ios_base::sync_with_stdio(false); cin.tie(0),cout.tie(0)
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
#define debug(_fmt,...) fprintf(stderr,"("#__VA_ARGS__ ") = (" _fmt")\n",__VA_ARGS__)

const d eps = 1e-12;

inline int sign(d x) { return x < -eps ? -1 : x > eps; }
inline int realcmp(d x, d y) { return sign(x-y); }
template<typename T> void na(vector<T>& a, int n) {a = vector<T>(n);for(T& i: a) cin >> i;}
template<typename T> void pv(vector<T>& a) { for(T& i: a) cout << i << ' '; cout << endl; }
template<typename T> vector<T> shrink(vector<T>& x) { vector<T> vals = x; sort(all(vals)); unique(vals); for(T& i: x) i = ub(all(vals), i) - vals.begin(); return vals; }

ll lcm(ll a, ll b)
{
  return (a / __gcd(a, b)) * b;
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  ll a, b;
  cin >> a >> b;
  
  if(a < b) swap(a, b);
  
  ll T = a - b;
  ll ansV = lcm(a, b),
      ansK = 0;
  
  for(int i=1;1ll * i * i <= T; ++i)
  {
    if(T % i) continue;
    
    {
      ll k = 1ll * (b + i - 1) / i;
      k = k * i - b;
      ll tmp = lcm(a + k, b + k);
      if(tmp < ansV) ansV = tmp, ansK = k;
      else if(tmp == ansV) ansK = min(ansK, k);
    }
    {
      ll j = T / i;
      ll k = 1ll * (b + j - 1) / j;
      k = k * j - b;
      ll tmp = lcm(a + k, b + k);
      if(tmp < ansV) ansV = tmp, ansK = k;
      else if(tmp == ansV) ansK = min(ansK, k);
    }
  }
  
  cout << ansK << endl;
  
  return 0;
}

#warning you will remember this, overflow is there, though you might not see it ...

