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

struct tri
{
  int t, i, x;
  tri(int t, int i, int x)
    : t(t), i(i), x(x){}
};

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  int n;
  cin >> n;
  vector<int> a;
  na(a, n);
  
  vector<tri> ans;
  ans.eb(1, n-1, 1e5);
  
  for(int i=0;i<n;++i)
  {
    int cur = a[i] + 1e5;
    ans.eb(2, i, cur - i - 1);
  }
  
  cout << sz(ans) << endl;
  for(tri t: ans)
    cout << t.t << ' ' << t.i + 1 << ' ' << t.x << endl;
  
  return 0;
}
