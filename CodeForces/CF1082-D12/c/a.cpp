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

const int N = 1e5+7;

vector<ll> ve[N];

ll dp[N];

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int n, m;
  cin >> n >> m;
  for(int i=1;i<=n;++i)
  {
    int s, r;
    cin >> s >> r;
    ve[s].pb(r);
  }
  
  for(int i=1;i<=m;++i)
  {
    sort(all(ve[i]), greater<ll>());
    ll sum = 0;
    for(int j=0;j<sz(ve[i]);++j)
    {
      if(sum + ve[i][j] < 0) break;
      sum += ve[i][j];
      dp[j+1] += sum;
    }
  }
  
  ll ans=0;
  for(int i=1;i<N;++i)
    ans = max(ans, dp[i]);
    
  cout << ans << endl;
  
  return 0;
}
