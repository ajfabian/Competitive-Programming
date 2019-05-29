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

pll getColors(ll x1, ll y1, ll x2, ll y2)
{
  ll h = y2 - y1 + 1;
  ll w = x2 - x1 + 1;
  
  ll T = h * w, a, b;
  ll T1 = (a = (h + 1) / 2) * (b = (w + 1)/ 2);
  T1 += (h - a) * (w - b);
  ll T2 = T - T1;
  if((x1 + y1) & 1) // this point is black
    return mp(T2, T1);
  return mp(T1, T2);
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int tt;
  cin >> tt;
  while(tt--)
  {
    ll n, m;
    cin >> n >> m;
    
    auto tmp = getColors(1,1,n,m);
    ll Tn, Tb;
    Tb = tmp.fr; Tn = tmp.sc;
    //~ debug("%lld %lld %lld %lld", Tb, );
    
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    tmp = getColors(x1, y1, x2, y2);
    ll b0 = tmp.fr, n0 = tmp.sc;
    Tb += n0, Tn -=n0;
    
    ll x3, y3, x4, y4;
    cin >> x3 >> y3 >> x4 >> y4;
    tmp = getColors(x3, y3, x4, y4);
    ll b1 = tmp.fr, n1 = tmp.sc;
    Tb -= b1, Tn += b1;
    
    // the hard part
    ll lx = max(x1, x3), rx = min(x2, x4);
    if(lx > rx)
    {
      cout << Tb << ' ' << Tn << endl;
      continue;
    }
    
    ll ly = max(y1, y3), ry = min(y2, y4);
    if(ly > ry)
    {
      cout << Tb << ' ' << Tn << endl;
      continue;
    }
    tmp = getColors(lx, ly, rx, ry);
    ll b2 = tmp.fr, n2 = tmp.sc;
    Tb -= n2, Tn += n2;
    
    cout << Tb << ' ' << Tn << endl;
  }
  
  return 0;
}
