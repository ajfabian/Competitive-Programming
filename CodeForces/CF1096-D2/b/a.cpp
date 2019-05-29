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

const ll mod = 998244353;

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  ll n;
  cin >> n;
  string s;
  cin >> s;
  
  int psz = 0;
  char x = s.front();
  auto it = s.begin();
  while(it != s.end() && *it == x)
  {
    ++psz;
    ++it;
  }
  
  int ssz = 0;
  char y = s.back();
  auto jt = s.end();jt--;
  while(*jt == y)
  {
    ++ssz;
    jt--;
  }
  cerr << psz << ' ' << ssz << endl;
  
  if(x != y) return !(cout << (psz + ssz + 1) % mod << endl);
  
  cout << 1ll * (psz + 1ll) * (ssz + 1ll) % mod  << endl;
  
  return 0;
}
