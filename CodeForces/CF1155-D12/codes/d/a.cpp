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
const int N = 3e5+7;

inline int sign(d x) { return x < -eps ? -1 : x > eps; }
inline int realcmp(d x, d y) { return sign(x-y); }
template<typename T> void na(vector<T>& a, int n) {a = vector<T>(n);for(T& i: a) cin >> i;}
template<typename T> void pv(vector<T>& a) { for(T& i: a) cout << i << ' '; cout << endl; }
template<typename T> vector<T> shrink(vector<T>& x) { vector<T> vals = x; sort(all(vals)); unique(vals); for(T& i: x) i = ub(all(vals), i) - vals.begin(); return vals; }

ll dp[N][3], a[N];

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  int n;
  ll x;
  scanf("%d %lld", &n, &x);
  for(int i=1;i<=n;++i)
    scanf("%lld", a + i);
  
  dp[1][0] = max(0ll, a[1]);
  dp[1][1] = max(0ll, x * a[1]);
  dp[1][2] = max(0ll, a[1]);
  
  ll ans = 0;
  
  for(int i=1;i<=n;++i)
  {
    if(i>=2)
    {
      dp[i][0] = max({0ll, a[i], dp[i-1][0] + a[i]});
      dp[i][1] = max({0ll, dp[i-1][1] + x * a[i], dp[i-1][0] + x * a[i], x * a[i]});
      dp[i][2] = max({0ll, dp[i-1][1] + a[i], dp[i-1][2] + a[i], a[i]});
    }
    //~ cerr << i << ": " << dp[i][0] << ' '<< dp[i][1] << ' '<< dp[i][2] << '\n';
    ans = max({ans, dp[i][0],dp[i][1],dp[i][2]});
  }
  
  cout << ans << endl;
  
  return 0;
}

#warning you will remember this, overflow is there, though you might not see it ...

