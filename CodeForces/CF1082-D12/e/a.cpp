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
{a = vector<T>(n);for(T& i: a) scanf("%d", &i);}
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

const int N = 5e5+7;

int T[N];
vector<int> pos[N];

int n, c;
int qry(int a, int b)
{
  if(b < 0 || a > n-1) return 0;
  if(a > 0) return T[b] - T[a-1];
  return T[b];
}

int go(int x)
{
  int res=0;
  int mxA=0;
  for(int i=0;i<sz(pos[x]);++i)
  {
    int ai = qry(0,pos[x][i]-1) - i;
    mxA = max(mxA, ai);
    int bi = i+1 + qry(pos[x][i]+1, n-1);
    res = max(res, mxA + bi);
    //~ debug("%d %d", ai, bi);
  }
  //~ cerr << "=======\n";
  return res;
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  scanf("%d%d", &n, &c);
  vector<int> a;
  na(a, n);
  
  for(int i=0;i<n;++i)
  {
    T[i] = (i > 0 ? T[i-1] : 0) + (a[i] == c);
    pos[a[i]].pb(i);
  }
  
  int ans = 0;
  for(int i=*min_element(all(a)), ii = *max_element(all(a));i<=ii;++i)
    ans = max(ans, go(i));
  
  printf("%d\n", ans);
  
  return 0;
}
