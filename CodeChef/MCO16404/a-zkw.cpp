#include <bits/stdc++.h>
using namespace std;

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

const int N = 3e5+7;

int n;
vector<int> t[N << 1];

void merge(vector<int>& l, vector<int>& r, vector<int>& p)
{
  p.resize(l.size() + r.size());
  merge(l.begin(), l.end(), r.begin(), r.end(), p.begin());
}

void build()
{
  for(int i=n-1;i;--i) merge(t[i<<1], t[i<<1|1], t[i]);
}

int qry(int l, int r, int x)
{
  int res = -1;
  for(l+=n, r+=n; l<r; l>>=1 , r>>=1)
  {
    if(l&1) res = max(res, qrys(t[l++], x));
    if(r&1) res = max(res, qrys(t[--r], x));
  }
  return res;
}

int main()
{
  scanf("%d", &n);
  for(int x, i=0;i<n;++i)
  {
    scanf("%d", &x);
    t[n+i]={x};
  }
  
  build();
  
  int q;
  scanf("%d", &q);
  while(q--)
  {
    int l, r, x;
    scanf("%d%d%d", &l, &r, &x);
    --l;
    printf("%d\n", qry(l, r, x));
  }
  
  return 0;
}
