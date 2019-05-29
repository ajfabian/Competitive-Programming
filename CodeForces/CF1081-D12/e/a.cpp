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
  //~ INIT;
  int n;
  cin >> n;
  vector<ll> M(n);
  
  ll p = 0;
  for(int i=0, j=1; j<n; i+=2, j+=2)
  {
    ll a;
    cin >> a;
    ll tt2=-1, tt1=-1;
    for(ll d = 1; d * d <= a;++d)
    {
      if(a % j) continue;
      ll d1 = a / j;
      if((d + d1) & 1) continue;
      ll t2 = (d + d1) / 2;
      ll t1 = d1 - t2;
      if(p <= t1 * t1)
      {
        tt1 = t1;
        tt2 = t2;
        break;
      }
    }
    cout << tt1 << ' ' << tt2 << endl;
    assert(~tt2 && ~tt1);
    ll x = tt1 * tt1 - p;
    cout << x << endl;
    p += x + a;
  }
  cout << endl;
  
  //~ cout << "Yes\n";
  //~ printVector(M);
  
  return 0;
}
