/*
 * link: http://codeforces.com/contest/1091/problem/E
 * submits: 5
 * TT: 60
 * CT: 60
 * Level: 7.25
 * Category: graphs, binary search
 * Comment: Interesting. I knew about the other theorem linked in the statement but it wasn't useful, didn't check the link during competition though. Lots of submitions firstly due to implementation errors and overflow. Most of the coding time was thinking (this is a mistake!!!, I know).
 * 
 * 
 * Theorem: A sequence di realizes a simple graph iff
 *  sum(i, 1, k, d[i]) <= k * (k - 1) + sum(i, k+1, n, min(k, d[i]))
 * */

#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <algorithm>
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

const int N = 5e5 + 7;


int n;
ll a[N];

bool ok1(ll nval)
{
  vector<ll> d, tail;
  for(int i=1;i<=n;++i)
    if(a[i] > nval) d.pb(a[i]);
    else tail.pb(a[i]);
  int pos = sz(d);
  d.pb(nval);
  for(ll i: tail) d.pb(i);
  
  int nn = sz(d);
  vector<ll> cum(nn, 0);
  for(int i = 0; i < nn;++i)
    cum[i] = (i ? cum[i-1] : 0) + d[i];
  
  for(int k = 0, j = nn-1; k < pos; ++k)
  {
    while(j && d[j] < k+1) --j;
    
    ll left = cum[k];
    ll right = 1ll * k * (k + 1);
    if(j > k) right += 1ll * (j - k) * (k + 1) + cum.back() - cum[j];
    else right += cum.back() - cum[k];
    
    if(left > right) return false;
  }
  return true;
}

bool ok2(ll nval)
{
  vector<ll> d, tail;
  for(int i=1;i<=n;++i)
    if(a[i] > nval) d.pb(a[i]);
    else tail.pb(a[i]);
  int pos = sz(d);
  d.pb(nval);
  for(ll i: tail) d.pb(i);
  
  int nn = sz(d);
  vector<ll> cum(nn, 0);
  for(int i = 0; i < nn;++i)
    cum[i] = (i ? cum[i-1] : 0) + d[i];
  
  for(int k = 0, j = nn-1; k < nn; ++k)
  {
    while(j && d[j] < k+1) --j;
    
    if(k < pos) continue;
    
    ll left = cum[k];
    ll right = 1ll * k * (k + 1);
    if(j > k) right += 1ll * (j - k) * (k + 1) + cum.back() - cum[j];
    else right += cum.back() - cum[k];
    
    if(left > right) return false;
  }
  return true;
}
ll bs1(ll lo, ll hi, ll sum)
{
  if(hi - lo <= 1)
  {
    if(ok1(2 * lo  + sum)) return lo;
    if(ok1(2 * ++lo  + sum)) return lo;
    return ++lo; 
  }
  ll m = (lo + hi) / 2;
  if(ok1(2 * m + sum)) return bs1(lo, m, sum);
  return bs1(m+1, hi, sum);
}

ll bs2(ll lo, ll hi, ll sum)
{
  if(hi - lo <= 1)
  {
    if(ok2(2 * hi  + sum)) return hi;
    if(ok2(2 * --hi  + sum)) return hi;
    return --hi;
  }
  ll m = (lo + hi) / 2;
  if(ok2(2 * m + sum)) return bs2(m, hi, sum);
  return bs2(lo, m-1, sum);
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  scanf("%d", &n);
  ll sum = 0;
  for(int i=1;i<=n;++i)
  {
    scanf("%lld", a + i);
    sum += a[i];
  }
  
  sum &= 1ll;
  
  sort(a + 1, a + n + 1, greater<ll>());
  
  ll loans, hians;
  
  loans = bs1(0, (n+1)/2 + 2000, sum);
  hians = bs2(0, (n+1)/2 + 2000, sum);

  cerr << loans << ' ' << hians << endl;

  if(loans > hians)
   return !(cout << "-1\n");
  
  while(loans <= hians)
    cout << (loans++) * 2 + sum << ' ';
  cout << endl;
  
  return 0;
}
