#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

const int N = 2e6+7;

int ft[N];

void upd(int x, int v)
{
  for(;x < N; x+=x&-x)
    ft[x] += v;
}
int qry(int x)
{
  int res=0;
  for(;x;x-=x&-x)
    res += ft[x];
  return res;
}

int zero;

int main()
{
  int n, q;
  scanf("%d%d", &n, &q);
  for(int i=1;i<=n;++i) upd(i, 1);
  
  int cur = 0;
  zero=0;
  int nn = n;
  while(q--)
  {
    //~ cerr << "zero = " << zero << " n = " << n << endl;
    //~ for(int i=+1;i<=nn;++i)
      //~ cerr << qry(i)- qry(i-1)<< " \n"[i == nn];
    int t;
    scanf("%d", &t);
    if(t == 1)
    {
      int p;
      scanf("%d", &p);
      
      if(cur == 0)
      {
        int i = zero+1, j = zero+p;
        int l = zero+2*p;
        if(l <= n)
        {
          for(;i<=j;++i,--l)
            //~ cerr << "a[" << l << "] += " << i << endl,
            upd(l, qry(i) - qry(i-1));
          zero += p;
        }else
        {
          p = n-zero-p;
          j = n-p+1;
          l = n-2*p+1;
          vector<int> vals;
          for(i = n;i >= j;--i)
            vals.push_back(qry(i) - qry(i-1));
          for(int v: vals)
            upd(l++, v);
          n -= p;
          cur ^= 1;
        }
      }else
      {
        //~ p = n-zero-p;
        int j = n-p+1;
        int l = n-2*p+1;
        if(l > zero)
        {
          vector<int> vals;
          for(int i = n;i >= j;--i)
            vals.push_back(qry(i) - qry(i-1));
          for(int v: vals)
            upd(l++, v);
          n -= p;
        }else
        {
          p = n - zero - p;
          int i = zero+1, j = zero+p;
          l = zero+2*p;
          for(;i<=j;++i,--l)
            //~ cerr << "a[" << l << "] += " << i << endl,
            upd(l, qry(i) - qry(i-1));
          zero += p;
          cur ^= 1;
        }
      }
    }else
    {
      int l, r;
      scanf("%d%d", &l, &r);
      if(cur == 0)
        //~ cerr << "qery on: " << zero + r << ' ' << zero + l << endl,
        printf("%d\n", qry(zero + r) - qry(zero + l));
      else
        //~ cerr << "query on: " << n - l << ' ' << n - r  << endl,
        printf("%d\n", qry(n - l) - qry(n - r));
    }
  }
  //~ for(int i=+1;i<=nn;++i)
      //~ cerr << qry(i) - qry(i-1) << " \n"[i == nn];

  return 0;
}
