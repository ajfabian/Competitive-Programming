/*
 * // code time: 10
 * Idea: use dp.
 * 
 * First compress given string transforming every interval of same letters
 * to one single letter. It can be seen that every answer string can be
 * obtained by expanding the leters in the compressed string and that
 * the obtained string has a compressed form which is a subsequence of
 * given string's compressed form.
 * 
 * dp(i, ka, kb, kc) - is number of strings with ka a's, kb b's and kc c's
 *  that can be formed expanding characters up to ith in the compressed form.
 * 
 * Editorial: https://codeforces.com/blog/entry/451
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

const int mod = 51123987;

int n;
string s;

int dp[155][55][55][55];
int nxt[155][3];

void add(int& a, int b)
{
  a += b;
  if(a > mod) a -= mod;
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  cin >> n >> s;
  //~ n = 150;s = "";
  //~ for(int i=0;i<n;++i)
    //~ s += (char)(i%3 + 'a');
  string sp="";
  for(int i=0;i<sz(s);++i)
    if(i == 0 || s[i] != s[i-1])
      sp += s[i];
  
  cerr << sp << endl;
  sp = " " + sp;
  
  int lastA=-1, lastB = -1, lastC = -1;
  for(int i=sz(sp)-1;~i;--i)
  {
    if(sp[i] == 'a') lastA = i;
    if(sp[i] == 'b') lastB = i;
    if(sp[i] == 'c') lastC = i;
    nxt[i][0] = lastA;
    nxt[i][1] = lastB;
    nxt[i][2] = lastC;
  }
  
  int ans = 0;
  dp[0][0][0][0] = 1;
  for(int i=0;i<sz(sp);++i)
  {
    for(int ka = 0; ka < 52; ++ka)
      for(int kb = 0; kb < 52; ++kb)
        for(int kc = 0; kc < 52;++kc)
        {
          if(~nxt[i][0]) add(dp[nxt[i][0]][ka + 1][kb][kc], dp[i][ka][kb][kc]);
          if(~nxt[i][1]) add(dp[nxt[i][1]][ka][kb + 1][kc], dp[i][ka][kb][kc]);
          if(~nxt[i][2]) add(dp[nxt[i][2]][ka][kb][kc + 1], dp[i][ka][kb][kc]);
        }
    for(int ka = 0; ka < 52; ++ka)
      for(int kb = max(0, ka-1); kb <= min(52, ka+1); ++kb)
        for(int kc = max(0, ka-1); kc <= min(52, ka+1); ++kc)
          if(labs(ka - kb) <= 1 && labs(ka - kc) <= 1 && labs(kb - kc) <= 1 && ka + kb + kc == n)
            add(ans, dp[i][ka][kb][kc]);
  }
  
  cout << ans << endl;
  
  return 0;
}
