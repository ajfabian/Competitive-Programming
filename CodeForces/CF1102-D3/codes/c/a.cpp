#pragma GCC optimize("Ofast")

#include <iostream>
//~ #include <cstdio>
//~ #include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
//~ #include <unordered_set>
//~ #include <unordered_map>
//~ #include <ctime>
//~ #include <cassert>
//~ #include <complex>
#include <string>
//~ #include <cstring>
//~ #include <chrono>
//~ #include <random>
//~ #include <queue>
//~ #include <bitset>
using namespace std;

typedef double real;
typedef long long int ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const real eps = 1e-12;

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

inline int sign(real x){return x < -eps ? -1 : x > eps;}
inline int realcmp(real x, real y){return sign(x-y);}
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

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int n;
  ll x, y;
  cin >> n >> x >> y;
  if(x > y)  return !(cout << n << endl);
  
  vector<ll> a; na(a, n);
  
  multiset<ll> s;
  for(ll i: a)
    s.ins(i);
  
  int ans = 0;
  while(sz(s) && *s.begin() <= x)
  {
    auto it = s.ub(x);
    it--;
    
    s.ers(it);
    ++ans;
    
    if(sz(s) && *s.begin() <= x)
    {
      it = s.ub(x);
      --it;
      ll tmp;
      if((tmp = *it + y) > x) s.ers(it);
      else
      {
        s.ers(it);
        s.ins(tmp);
      }
    }
  }
  
  cout << ans << endl;
  
  return 0;
}
//~ "you will remember this, overflow is there, though you might not see it ..."

