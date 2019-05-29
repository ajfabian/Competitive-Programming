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

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int n; cin >>n;
  vector<ll> b;
  na(b, n/2);
  vector<ll> a(n, 0);
  
  a[sz(a)-1] = b[0];
  a[0] = 0;
  auto it = a.begin();it++;
  auto jt = a.end();
  jt--;
  if(it == jt)
  {
    printVector(a);
    return 0;
  }
  jt--;
  //~ return 0;
  ll m = b[0];
  ll f = 0;
  for(int i=1;i<n/2;++i)
  {
    ll y = min(m, b[i]);
    *it = b[i] - y;
    *jt = y;
    if(*it < f)
    {
      *it = f;
      *jt = b[i] - *it;
    }
    m = *jt;
    f = *it;
    it++;
    jt--;
  }
  
  printVector(a);
  
  return 0;
}
