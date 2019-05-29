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

ll sumP(ll n){return n*(n+1);}
ll sumI(ll n){return (n+1)*(n+1);}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int q;
  cin >> q;
  while(q--)
  {
    ll l, r;
    cin >> l >> r;
    if(l == r)
    {
      if(l & 1) cout << -l << endl;
      else cout << l << endl;
      continue;
    }
    
    ll i=l;
    ll lsumP=0, rsumP=0;
    while(i&1)++i;
    lsumP = sumP(i / 2 - 1);
    i = r;
    while(i&1)--i;
    rsumP = sumP(i / 2);
    
    ll lsumI = 0, rsumI = 0;
    i = l;
    while(i % 2 == 0)++i;
    lsumI = sumI((i - 1) / 2 - 1);
    i = r;
    while(i % 2 == 0)--i;
    rsumI = sumI((i - 1) / 2);
    
    cout << rsumP - lsumP - (rsumI - lsumI) << endl;
  }
  
  return 0;
}
