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
#include <deque>
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

const int N = 3e5+7;

int a[N];
int x[3];
deque<int> pos[3];

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int n;
  //~ scanf("%d", &n);
  cin >> n;
  int t = n / 3;
   x[0] = x[1] = x[2] = t;
  
  for(int i=1;i<=n;++i)
  {
    char c;
    cin >> c;
    a[i] = c - '0';
    pos[a[i]].pb(i);
    x[a[i]]--;
  }
  
  if(x[0] > 0)
  {
    while(x[0] && (x[1] < 0 || x[2] < 0))
    {
      if(x[2] >= 0)
      {
        pos[0].pb(*pos[1].begin());
        pos[1].pop_front();
        ++x[1];
      }else if(x[1] >= 0)
      {
        pos[0].pb(*pos[2].begin());
        pos[2].pop_front();
        ++x[2];
      }else
      {
        auto i1 = pos[1].begin();
        auto i2 = pos[2].begin();
        if(*i1 < *i2)
        {
          pos[0].pb(*pos[1].begin());
          pos[1].pop_front();
          ++x[1];
        }else
        {
          pos[0].pb(*pos[2].begin());
          pos[2].pop_front();
          ++x[2];
        }
      }
      --x[0];
    }
  }
  
  if(x[2] > 0)
  {
    while(x[2] && (x[0] < 0 || x[1] < 0))
    {
      if(x[1] >= 0)
      {
        pos[2].pb(*pos[0].rbegin());
        pos[0].pop_back();
        ++x[0];
      }else if(x[0] >= 0)
      {
        pos[2].pb(*pos[1].rbegin());
        pos[1].pop_back();
        ++x[1];
      }else
      {
        auto i1 = pos[0].rbegin();
        auto i2 = pos[1].rbegin();
        if(*i1 > *i2)
        {
          pos[2].pb(*pos[0].rbegin());
          pos[0].pop_back();
          ++x[0];
        }else
        {
          pos[2].pb(*pos[1].rbegin());
          pos[1].pop_back();
          ++x[1];
        }
      }
      --x[2];
    }
  }
  
  if(x[1] > 0)
  {
    while(x[1] && (x[0] < 0 || x[2] < 0))
    {
      if(x[2] >= 0)
      {
        pos[1].pb(*pos[0].rbegin());
        pos[0].pop_back();
        ++x[0];
      }else if(x[0] >= 0)
      {
        pos[1].pb(*pos[2].begin());
        pos[2].pop_front();
        ++x[2];
      }else
      {
        pos[1].pb(*pos[2].begin());
        pos[2].pop_front();
        ++x[2];
      }
      --x[1];
    }
  }
  
  vector<int> ans(n+1);
  for(int i=0;i<3;++i)
  {
    cerr << "=== " << i << ": ";
    for(int j: pos[i])
      ans[j] = i, cerr << j << ' ';
    cerr << endl;
  }
    
  for(int i=1;i<=n;++i)
    cout << ans[i];
  cout << endl;
  
  
  return 0;
}
//~ "you will remember this, overflow is there, though you might not see it ..."

