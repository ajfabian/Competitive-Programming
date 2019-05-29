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

const int N = 2e5+7;

int a[N];
int b[N];

map<int, int> last;

int st[N * 5];

void build(int i, int lo , int hi)
{
  if(lo == hi)
  {
    st[i] = b[lo];
    return;
  }
  
  int m = (lo + hi) / 2, l, r;
  build(l = i << 1, lo, m);
  build(r = l | 1, m+1, hi);
  st[i] = max(st[l], st[r]);
}

int qry(int x, int y, int i, int lo,int hi)
{
  if(x > hi || y < lo) return 0;
  
  if(x <= lo && hi <= y) return st[i];
  
  int m = (lo + hi) / 2;
  return max( qry(x, y, i << 1, lo, m),
              qry(x, y, (i << 1) | 1, m+1, hi));
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  int n;
  scanf("%d", &n);
  for(int i=1;i<=n;++i)
  {
    scanf("%d", a + i);
  }
  
  for(int i=n;i;--i)
  {
    if(!last.count(a[i])) last[a[i]] = i;
    b[i] = last[a[i]];
  }
  
  //~ for(int i=1;i<=n;++i)
    //~ cerr << b[i] << ' ';
  //~ cerr << endl;
  
  build(1, 1, n);
  
  cerr << "qr " << qry ( 1, 3, 1, 1, n) << endl;
  cerr << st[2] << endl;
  
  
  int tot = 0;
  for(int i=1;i<=n;)
  {
    int j = b[i], p;
    while((p = qry(i, j, 1, 1, n)) > j)
    {
      //~ cerr << i << ' ' << j << ' ' <<  p << endl;
      j = p;
    }
    ++tot;
    //~ cerr << i << ' ' << j << endl;
    i = j + 1;
  }
  
  cerr << tot << endl;
  
  ll mod = 998244353;
  
  ll ans = 1;
  for(int i=1;i<tot;++i)
    ans = (ans * 2) % mod;
  cout << ans << endl;
  
  return 0;
}
//~ "you will remember this, overflow is there, though you might not see it ..."

