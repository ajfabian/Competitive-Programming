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
  
  int n; cin >> n;
  vector<int> ord;
  for(int i=1;i<=n;++i)
    ord.pb(i);
  
  vector<int> ss;
  int tt=0,tle=1000;
  do
  {
    ++tt;
    for(int i: ord)
      ss.pb(i);
  }while( next_permutation(all(ord)));
  
  int ans=0;
  int targ = n * (n + 1) / 2;
  for(int i=0,o=1,p=1,h=0, x=0;i+n<=sz(ss);++i,++o,++p)
  {
    int sum = 0;
    for(int j=i;j<i+n;++j)
    {
      sum += ss[j];
    }
    //~ if(sum == targ)cout << setw(3) << left << sum << ' ';
    if(sum == targ)
    {
      //~ ++h;
      ++ans;
    }
    int lh = h;
    if(o == n) ++x, o = 0/*, cout << h<< endl*/, h = 0;
    //~ if(x == 6) cout << lh << endl, x=0;
    //~ if(p == tt) p = 0, cout << "===========\n";
    
  }
  cout << endl << ans << endl;
  
  return 0;
}
