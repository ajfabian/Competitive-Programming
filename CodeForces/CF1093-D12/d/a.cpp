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

const int N = 3e5+7;
const ll mod = 998244353;

int n, m;

vector<int> g[N];
void eadd(int u,int v)
{
  g[u].pb(v);
  g[v].pb(u);
}

ll powe[N];
bool mk[N];
ll ans = 1;
int col[N];

ll solve(int st)
{
  queue<int> q;
  q.push(st);
  mk[st] = 1;
  col[st] = 1;
  int tot = 1, tot2 = 1;
  while(!q.empty())
  {
    int u = q.front();
    q.pop();
    for(int v: g[u])
    {
      if(mk[v])
      {
        if(col[v] == col[u]) return 0;
        continue;
      }
      mk[v] = true;
      col[v] = col[u] * -1;
      if(col[v] == 1) ++tot2;
      ++tot;
      q.push(v);
    }
  }
  //~ cerr << tot << ' '  << tot2 << endl;
  if(tot == 1) return 3ll;
  return (powe[tot2] + powe[tot - tot2]) % mod;
}

void clean()
{
  for(int i=1;i<=n;++i) 
  {
    g[i].clear();
    mk[i] = false;
    col[i] = 0;
  }
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  powe[0] =1;
  for(int i = 1; i < N;++i) 
    powe[i] = powe[i-1] * 2 % mod;
  
  int tt;
  scanf("%d", &tt);
  
  while(tt --)
  {
    scanf("%d%d", &n, &m);
    for(int i=1;i<=m;++i)
    {
      int u, v;
      scanf("%d%d", &u, &v);
      eadd(u, v);
    }
    
    ans = 1;
    for(int i=1;i<=n;++i)
    {
      if(mk[i]) continue;
      ans = (ans * solve(i)) % mod;
    }
    printf("%lld\n", ans);
    clean();
  }
  
  return 0;
}
