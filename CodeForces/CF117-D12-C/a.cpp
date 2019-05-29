/*
 * Idea: Every Cycle has a three cycle.
 * 
 * from editorial: https://codeforces.com/blog/entry/2752
 * */

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

const int N = 5555;

int n;
bool gmat[N][N];
vector<int> g[N];

bool found = false;

bool onstack[N], seen[N];
stack<int> stk;
vector<int> cycle;

void dfs(int u)
{
  onstack[u] = 1;
  seen[u] = 1;
  stk.push(u);
  for(int v: g[u])
  {
    if(found) return;
    if(onstack[v])
    {
      found = true;
      int cur = u;
      cycle.pb(cur);
      do
      {
        stk.pop();
        cur = stk.top();
        cycle.pb(cur);
      }while(cur!=v);
      return;
    }
    if(!seen[v]) dfs(v);
  }
  onstack[u] = false;
  stk.pop();
}


int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  cin >> n;
  for(int i=1; i<=n;++i)
    for(int j=1;j<=n;++j)
    {
      char c;
      cin >> c;
      if(c == '1')
        g[i].pb(j), gmat[i][j] = 1;
    }
  
  for(int i = 1; i <= n && !found; ++i)
    if(!seen[i])
      dfs(i);
      
  reverse(all(cycle));
  //~ printVector(cycle);
  
  if(!found) cout << "-1\n";
  else
  {
    int j=1, k=2;
    while(k < sz(cycle))
    {
      if(gmat[cycle[k]][cycle[0]])
      {
        cout << cycle[0] << ' '  << cycle[j] << ' ' << cycle[k] << '\n';
        break;
      }
      ++k, ++j;
    }
  }
  
  return 0;
}
