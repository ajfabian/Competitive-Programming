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
  vector<int> a;
  na(a, n);
  
  vector<int> ondiam;
  deque<int> leafs;
  
  for(int i=0;i<n;++i)
  {
    if(a[i] > 1) ondiam.pb(i);
    else leafs.pb(i);
  }
  
  if(sz(ondiam) == 0)
  {
    if(n > 2) return !(cout << "NO\n");
    if(n == 2)
    {
      cout << "YES 1\n";
      cout << "1\n";
      cout << "1 2\n";
      return 0;
    }
    cout << "YES 0\n";
    cout << "0\n";
    return 0;
  }
  
  for(int i=1;i<sz(ondiam);++i)
    if(a[ondiam[0]] < a[ondiam[i]]) swap(ondiam[0], ondiam[i]);
  for(int i=1;i<sz(ondiam)-1;++i)
    if(a[ondiam.back()] < a[ondiam[i]]) swap(ondiam[sz(ondiam)-1], ondiam[i]);
  
  vector<pii> ans;
  int diam = sz(ondiam) - 1;
  for(int i=0;i<sz(ondiam)-1;++i)
  {
    ans.eb(ondiam[i], ondiam[i+1]);
    a[ondiam[i]]--;
    a[ondiam[i+1]]--;
  }
  
  if(sz(leafs) >= 1)
  {
    if(a[ondiam.front()] > 0)
    {
      ans.eb(leafs.front(), ondiam.front());
      a[ondiam.front()] --;
      leafs.pop_front();
      ++ diam;
      cerr << "fetched front diam: " << ondiam.front() + 1 << endl;
    }
    
    if(sz(leafs) >= 1 && a[ondiam.back()] > 0)
    {
      ans.eb(leafs.front(), ondiam.back());
      a[ondiam.back()] --;
      leafs.pop_front();
      ++diam;
      cerr << "fetched back diam: " << ondiam.front() + 1 << endl;
    }
  }
  
  auto it = ondiam.begin();
  for(int l: leafs)
  {
    while(it != ondiam.end() && a[*it] == 0)
      it++;
    if(it == ondiam.end()) return !(cout << "NO\n");
    ans.eb(l, *it);
    a[*it] --;
  }
  
  cout << "YES " << diam << endl;
  cout << sz(ans) << endl;
  for(pii t: ans)
    cout << t.fr + 1 << ' ' << t.sc + 1 << endl;
  
  return 0;
}
