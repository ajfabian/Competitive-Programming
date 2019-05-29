/*
 * Idea: Use segment tree.
 * 
 * This problem looks like a harder version of the: "find the longest sum
 * subinterval", it's just now it is: "find the longest hill subinterval".
 * 
 * There are several cases to compute the answer and properties of 
 * a node in the segment tree:
 *  1. hill starts on begin of left son and ends somwhere in right son.
 *  2. hill starts somewhere on left son and ends on the end of right son.
 *  3. hill starts somewhere on left son and ends somewhere on right son.
 * These can be say fast, but it's a little tedious to get all those cases
 * right.
 * In the implementation was used prefix and suffix computations of what
 * I like to call prehills (hills that can get bigger). 
 * */

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = 3e5+7;

ll arr[N], lazy[N << 2];

struct Node
{
  ll lval, rval;
  ll lval1, rval1;
  int sdown, sup, pdown, pup, ans;
  Node(ll lval=0, ll rval=0, ll lval1=0, ll rval1=0, int sdown=1, int sup=1, int pdown=1, int pup=1, int ans=1)
    : lval(lval), rval(rval), lval1(lval1), rval1(rval1), sdown(sdown), sup(sup), pdown(pdown), pup(pup), ans(ans){}
  int l, r;
  int size()
  {
    return r - l + 1;
  }

  void dump()
  {
    cerr << l << ' ' << r << ' '  << lval << ' ' << rval << ' ' << pdown << ' ' << pup << ' ' << sdown << ' ' << pdown << ' ' << ans << endl;
  }
}tree[N << 2];

void merge(Node& i, Node& l, Node& r)
{
  i.lval = l.lval;
  i.rval = r.rval;

  i.lval1 = l.lval1;
  i.rval1 = r.rval1;

  if(r.size() == 1)
    i.rval1 = l.rval;
  if(l.size() == 1)
    i.lval1 = r.lval;

  i.ans = max(l.ans, r.ans);
  if(r.sdown == r.size() && l.rval < r.lval)
    i.sdown = r.size() + l.sdown;
  else i.sdown = r.sdown;

  if(l.pdown == l.size() && l.rval > r.lval)
    i.pdown = l.size() + r.pdown;
  else i.pdown = l.pdown;

  if(r.sup == r.size())
  {
    if(r.size() > 1 && r.lval < r.lval1)
    {
      if(l.rval < r.lval) i.sup = r.size() + l.sdown;
      else i.sup = r.sup;
    }else if(l.rval < r.lval) i.sup = r.size() + l.sdown;
    else if(l.rval > r.lval) i.sup = r.size() + l.sup;
    else i.sup = r.sup;
  }else i.sup = r.sup;

  if(l.pup == l.size())
  {
    if(l.size() > 1 && l.rval < l.rval1)
    {
      if(l.rval > r.lval) i.pup = l.size() + r.pdown;
      else i.pup = l.pup;
    }else if(l.rval > r.lval) i.pup = l.size() + r.pdown;
    else if(l.rval < r.lval) i.pup = l.size() + r.pup;
    else i.pup = l.pup;
  }else i.pup = l.pup;

  i.ans = max({i.ans, i.sup, i.pup, i.sdown, i.pdown});
  if(l.rval > r.lval)
    i.ans = max(i.ans, l.sup + r.pdown);
  if(l.rval < r.lval)
    i.ans = max(i.ans, l.sdown + r.pup);
}

int n;

void build(int i=1,int lo=1, int hi=-1)
{
  if(hi == -1) hi = n;
  tree[i].l = lo;
  tree[i].r = hi;
  if(lo == hi)
  {
    tree[i] = Node(arr[lo], arr[lo], arr[lo], arr[lo]);
    tree[i].l = lo;
    tree[i].r = hi;
    return;
  }
  int m = (lo + hi) / 2;
  int l,r;
  build(l = i << 1, lo, m);
  build(r = l | 1, m + 1, hi);
  merge(tree[i], tree[l], tree[r]);
}

void prop(int i, int lo, int hi)
{
  if(lazy[i])
  {
    tree[i].lval += lazy[i];
    tree[i].rval += lazy[i];
    tree[i].lval1 += lazy[i];
    tree[i].rval1 += lazy[i];
    if(lo != hi)
      lazy[i << 1] += lazy[i],
      lazy[(i << 1) | 1] += lazy[i];
    lazy[i] = 0;
  }
}

void upd(int x, int y, ll d, int i=1, int lo=1,int hi=-1)
{
  if(hi == -1) hi = n;
  prop(i, lo, hi);

  if(y < lo || hi < x)return;

  if(x <= lo && hi <= y)
  {
    lazy[i] += d;
    prop(i, lo, hi);
    return;
  }

  int l, r, m = (lo + hi) / 2;
  upd(x, y, d, l = i << 1, lo, m);
  upd(x, y, d, r = l | 1, m+1, hi);

  merge(tree[i], tree[l], tree[r]);
}

ll tmp[N];

int main()
{
  cerr<< N<<endl;
  int q;
  scanf("%d", &n);
  for(int i=1;i<=n;++i)
    scanf("%lld", &arr[i]), tmp[i] = arr[i];
  build();

  //~ tree[1].dump();

  //~ printTree();

  scanf("%d", &q);
  while(q--)
  {
    int l, r;
    ll d;
    scanf("%d%d%lld", &l, &r, &d);
    upd(l, r, d);
    //~ printTree();
    //~ tree[1].dump();
    printf("%d\n", tree[1].ans);
    //~ for(;l<=r;++l)
      //~ tmp[l] += d;
  }
  //~ for(int i=1;i<=n;++i)
    //~ cerr << tmp[i] << " \n"[i == n];
  return 0;
}
