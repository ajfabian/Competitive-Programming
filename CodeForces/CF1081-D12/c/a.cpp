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

const ll mod = 998244353;
const int N = 2222;

ll dp[N][N];

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int n, m, k;
  cin >> n >> m >> k;
  if(k == 0) return !(cout << m << endl);
  
  ++k;
  //~ dp[0][0] = 1;
  dp[1][1] = m;
  for(int i=1;i<n;++i)
  {
    for(int j=1;j<=k;++j)
    {
      dp[i+1][j] = (dp[i+1][j] + dp[i][j]) % mod;
      if(j+1 <= k)
        dp[i+1][j+1] = (dp[i+1][j+1] + dp[i][j] * (1ll * m - 1ll) % mod) % mod;
    }
  }
  
  cout << dp[n][k] << endl;
  
  
  return 0;
}
