/*
 * Idea: use Segment Tree.
 * 
 * The nodes in the segment tree keeps track for an interval how many
 * buggy lines are there.
 * For updating I use lazy propagation.
 * For queries just need to see in what child of the current node is
 * the l-th buggy line, i.e., if my left child has at least the number of
 * buggy lines that I'm looking for, then the buggy line is in it's subtree,
 * otherwise just need to look for (l - #buggylinesonleftchild)-th buggy
 * line on my right child.
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

const int N = 1e6+7;

int tree[N << 2];

void build(int i, int lo, int hi)
{
  if(lo == hi)
  {
    tree[i] = 1;
    return;
  }
  int m = (lo + hi) >> 1, l, r;
  build(l = i << 1, lo, m);
  build(r = (i << 1) | 1, m+1, hi);
  tree[i] = tree[l] + tree[r];
}

int lazy[N << 2];

void prop(int i,int lo,int hi)
{
  if(i >= N << 2) return;
  if(lazy[i])
  {
    tree[i] = hi - lo + 1 - tree[i];
  
    if(lo != hi) lazy[i << 1] ^= 1, lazy[(i << 1) | 1] ^= 1;
  }
  lazy[i] = 0;
}

void upd(int x, int y, int i, int lo, int hi)
{
  //~ cerr << x << ' ' << y << ' ' << i << ' ' << lo << ' ' << hi << ' ' << lazy[i] << endl;
  prop(i, lo, hi);
  if(hi < x || lo > y) return;
  if(x <= lo && hi <= y)
  {
    lazy[i] = 1;
    prop(i, lo, hi);
    return;
  }
  int m = (lo + hi) >> 1,l,r;
  upd(x, y, l = i << 1, lo, m);
  upd(x, y, r = (i << 1) | 1, m+1, hi);
  
  tree[i] = tree[l] + tree[r];
}

int qry(int l, int i, int lo, int hi)
{
  //~ cerr << l << ' ' << i << ' ' << lo << ' ' << hi << endl;
  prop(i, lo, hi);
  if(lo == hi) return lo;
  
  int m = (lo + hi) / 2;
  prop(i << 1, lo, m);
  prop((i << 1) | 1, m+1, hi);
  
  //~ cerr << "left: " << tree[i << 1] << " right: " << tree[(i << 1) | 1] << endl;
  
  if(tree[i << 1] < l) return qry(l - tree[i << 1], (i << 1) | 1, m+1, hi);
  return qry(l, i << 1, lo, m);
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  int n, m, l;
  scanf("%d %d %d", &n, &m, &l);
  
  build(1, 1, n);
  
  while(m--)
  {
    int a,b;
    scanf("%d%d", &a, &b);
    //~ cerr << "==========\n";
    upd(a, b,1,1,n);
    if(tree[1] >= l) printf("%d\n", qry(l,1,1,n));
    else printf("AC?\n");
    //~ cerr << "buggy: "<< tree[1] << endl;
  }
  
  return 0;
}
