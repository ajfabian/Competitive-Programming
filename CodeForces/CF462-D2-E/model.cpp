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
  
  zero=0;
  while(q--)
  {
    //~ for(int i=1;i<=n;++i)
      //~ cerr << qry(i) - qry(i-1) << " \n"[i == n];
    int t;
    scanf("%d", &t);
    if(t == 1)
    {
      int p;
      scanf("%d", &p);
      
      int i = zero+1, j = zero+p;
      int l = zero+2*p;
      
      //~ if(l > n)
      //~ {
        //~ p=0;
        //~ l = n;
        //~ while(i < l)
        //~ {
          //~ upd(l, qry(i) - qry(i-1));
          //~ ++p;
          //~ ++i;
          //~ --l;
        //~ }
        //~ if(i == l)
          //~ zero = l-1;
        //~ else zero = l;
      //~ }else
      //~ {
        for(;i<=j;++i,--l)
          //~ cerr << "a[" << l << "] += " << i << endl,
          upd(l, qry(i) - qry(i-1));
      //~ }
      
      zero += p;
    }else
    {
      int l, r;
      scanf("%d%d", &l, &r);
      //~ cerr << "query: " << zero + r << ' ' << zero + l << endl;
      printf("%d\n", qry(zero + r) - qry(zero + l));
    }
  }
  //~ for(int i=1;i<=n;++i)
      //~ cerr << qry(i) - qry(i-1) << " \n"[i == n];

  return 0;
}
