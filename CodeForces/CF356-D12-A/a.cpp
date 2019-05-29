/*
 * Idea: Use Segment Tree.
 * Update all the range, just don't update Intervals that are already fully updated.
 * 
 * link: https://codeforces.com/contest/356/problem/A
 * lv: 3
 * category: segment tree
 * TT: 10
 * CT: 10
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

const int N = 3e5+7;

int n, m;
int ans[N], tot[N << 2];

void upd(int a, int b, int x, int i=1, int lo=1,int hi = -1)
{
  if(hi == -1) hi = n;
  if(a > hi || b < lo || tot[i] == hi - lo + 1) return;
  if(lo == hi)
  {
    if(x == lo) return;
    ans[lo] = x;
    tot[i] = 1;
    return ;
  }
  int l,r,m = (lo + hi) /2;
  upd(a, b, x, l = i << 1, lo, m);
  upd(a, b, x, r = l | 1, m+1, hi);
  tot[i] = tot[l] + tot[r];
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  
  cin >> n >> m;
  while(m--)
  {
    int l, r, x;
    cin >> l >> r >> x;
    upd(l, r, x);
  }
  
  for(int i=1;i<=n;++i)
    cout << ans[i] << " \n"[i==n];
  
  return 0;
}
