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
  
  ll n;
  cin >> n;
  
  if((n * (n+1)) % 4ll == 0) cout << "0\n";
  else cout << "1\n";
  
  return 0;
}
//~ "you will remember this, overflow is there, though you might not see it ..."

