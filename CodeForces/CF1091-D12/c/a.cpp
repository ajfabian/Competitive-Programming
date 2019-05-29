/*
 * link: http://codeforces.com/contest/1091/problem/C
 * submits: 3
 * TT: 60
 * CT: 3
 * Level: 4.5
 * Category: algebra, number theory
 * Comment: Interesting. Maths aren't my best field, so when the solution is a combination of maths stuffs I get confused. 2 submits due to overflow
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

set<ll> ans;

void add(ll x, ll n)
{
  ll N = n / x - 1;
  ans.ins(N + x * N * (N + 1) / 2 + 1);
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int n;
  cin >> n;
  for(int i=1;1ll * i * i <= 1ll * n;++i)
  {
    if(n % i) continue;
    int d = n / i;
    add(i, n);
    add(d, n);
  }
  
  for(ll i: ans)
    cout << i << ' ';
  cout << endl;
   
  return 0;
}
