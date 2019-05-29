/*
 * link: http://codeforces.com/contest/1096/problem/D
 * submits: 2
 * TT: 30
 * CT: 10
 * Level: 5
 * Category: dp
 * Comment: Normal. Was thinking in a greedy at first, then just realize of simple dp.
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

typedef pair<int, ll> pil;

vector<ll> a,r;
const int N = 1e5+7;
const ll inf = 1e17;
ll dp[N][10];
string stmp, s, h = "$hard";

ll solve(int i, int j)
{
  if(~dp[i][j]) return dp[i][j];
  //~ cerr << i << ' ' << j  << endl;
  
  if(j < 1) return dp[i][j] = inf;
  if(i < 1) return dp[i][j] = 0;
  if(s[i] != h[j]) return dp[i][j] = solve(i-1, j);
  return dp[i][j] = min(solve(i-1, j) + r[i], solve(i-1, j-1));
}
int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int n;cin >> n;
  
  cin >> stmp; s = "";
  na(a, n);
  
  ll cum = 0;char last = '\0';
  for(int i = 0; i < n ; ++i)
  {
    if(stmp[i] != 'h' && stmp[i] != 'a' && stmp[i] != 'r' && stmp[i] != 'd') continue;
    if(stmp[i] == last) cum += a[i];
    else
    {
      s += last;
      r.pb(cum);
      last = stmp[i];
      cum = a[i];
    }
  }
  s += last;
  r.pb(cum);
  
  memset(dp, -1, sizeof dp);
  cout << solve(sz(s)-1, 4) << endl;
  
  return 0;
}
