/*
 * Idea: Use bitsets.
 * 
 * Let's check from left to right if ith element is good.
 * 
 * Let a[i] be the ith element, then we check for every other element with 
 * index j (j < i) if number a[i] - a[j] can be formed as sum of two
 * elements with indexes smaller than i.
 * 
 * To accomplish this store the sum of ith element with every other 
 * element with index at most i, using a bitset.
 * 
 * So the time complexity is O(N^2)
 * 
 * link: ...
 * submits: 1
 * TT: 19
 * CT: 6
 * Level: 4
 * Category: bitset
 * Comment: Interesting. 10**9 bits is just 134 MB of memory.
 * */

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
//~ #include <string>
//~ #include <cstring>
//~ #include <chrono>
//~ #include <random>
//~ #include <queue>
#include <bitset>
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

const int N = 5e3+7;
const int M = 2e5+7;
const int ZERO = 5e8+1;

bitset<M*N> b;

bool can(int i)
{
  return b[i + ZERO];
}

void setv(int i)
{
  b.set(i + ZERO);
}

int a[N];

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int n, ans = 0;
  cin >> n;
  for(int i=1;i<=n;++i)
  {
    cin >> a[i];
    for(int j = 1; j < i; ++j)
    {
      if(can(a[i] - a[j]))
      {
        ++ans;
        break;
      }
    }
    for(int j = 1; j <= i; ++ j)
      setv(a[i] + a[j]);
  }
  cout << ans << endl;
    
  return 0;
}
