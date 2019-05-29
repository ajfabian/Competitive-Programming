/*
 * Idea: use segment tree + binary search
 * 
 * The problem could be solve just by keeping a trie in every node of
 * a segment tree, but it just give TLE. What is done is to keep for
 * every node of the segment tree a vector of sorted elements in the range
 * an them for answering a query in that node use binary search of i-th
 * bit to know wether it can be set or not.
 * */

#include <bits/stdc++.h>
using namespace std;

#define fr first
#define sc second
#define mp make_pair

const int inf = 1e9;

int qrys(vector<int>& ve, int x)
{
  int l=0, r=ve.size()-1;
  int val=0;
  
  for(int i=20;~i;--i)
  {
    int p = lower_bound(ve.begin()+l, ve.begin()+r+1, val + (1 << i)) - ve.begin();
    
    if(x >> i & 1)
    {
      if(p == l) // no zeroes
        val += 1 << i;
      else
        r = p-1;
    }else
    {
      if(p == r+1) // no ones
        ;
      else val += 1 << i, l = p;
    }
  }
  
  return x ^ val; 
}

struct SegmentTree
{
  int n;
  vector<vector<int>> st;
  
  SegmentTree(vector<int>& A)
    : n(A.size()-1), st(A.size() << 4)
  {
    build(A);
  }
  
  void build(vector<int>& A, int i=1, int lo=1,int hi=-1)
  {
    if(hi == -1) hi = n;
    if(lo == hi)
    {
      st[i].push_back(A[lo]);
      return;
    }
    
    int m = lo + hi >> 1, l, r;
    build(A, l=i<<1, lo, m);
    build(A, r=l|1, m+1, hi);
    
    st[i].resize(st[l].size() + st[r].size());
    merge(st[l].begin(), st[l].end(), st[r].begin(), st[r].end(), st[i].begin());
  }
  
  int qry(int x, int l, int r, int i=1, int lo=1, int hi=-1)
  {
    if(hi == -1) hi = n;
    if(l <= lo && hi <= r) return qrys(st[i], x);
    if(hi < l || lo > r) return -1;
    int m = lo + hi >> 1;
    return max(qry(x, l, r, i<<1, lo, m), qry(x, l, r, (i<<1)|1, m+1, hi));
  }
};

int main()
{
  int n;
  scanf("%d", &n);
  vector<int> a(n+1);
  for(int i=1;i<=n;++i) scanf("%d", &a[i]);
  
  SegmentTree st(a);
  
  int q;
  scanf("%d", &q);
  while(q--)
  {
    int l, r, x;
    scanf("%d%d%d", &l, &r, &x);
    printf("%d\n", st.qry(x, l, r));
  }
  
  return 0;
}
