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
  
  int n;cin >> n;
  vector<int> a;
  vector<int> ff(n+1, 0);
  na(a, n);
  
  for(int& i: a)
  {
    i = n - i;
    ++ff[i];
  }
  
  vector<int> st(n+1, 0);
  int cur = 0;
  for(int i=1;i<=n;++i)
  {
    if(ff[i] && ff[i] % i) return !(cout << "Impossible\n");
    if(ff[i])
    {
      st[i] = cur;
      cur += ff[i] / i;
    }
  }
  
  //~ printVector(a);
  //~ printVector(st);
  
  cout << "Possible\n";
  for(int i: a)
  {
    cout << st[i] + (ff[i] + i - 1) / i << ' ';
    --ff[i];
  }
  cout << endl;
  
  return 0;
}
