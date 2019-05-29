#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
ll a, b, B, m, r[55];

bool ok(int i, ll v)
{
  ll S = B;
  if(i == n)
  {
    S -= r[i];
    S += v;
    return S <= b; 
  }
  S -= r[i] << (n - i - 1);
  S += v << (n - i - 1);
  return S <= b; 
}

ll bs(ll lo, ll hi, int i)
{
  if(hi - lo <= 1)
  {
    for(ll j=hi;j>=lo;--j)
      if(ok(i, j)) return j;
    return lo-1;
  }
  
  ll m = lo + hi >> 1;
  if(ok(i, m)) return bs(m, hi, i);
  return bs(lo, m, i);
}

int main()
{
  int tt;
  scanf("%d", &tt);
  while(tt--)
  {
    scanf("%lld%lld%lld", &a, &b, &m);
    
    if(a == b)
    {
      printf("1 %lld\n", a);
      continue;
    }
    
    bool flag = false;
       
    for(int k=2;k<=50;++k)
    {
      n = k-1;
      
      for(int i=1;i<=n;++i) r[i] = 1;
      
      bool flag1 = true;
      ll sum = a;
      for(int i=1;i<=n && flag1;++i)
      {
        ll cur = sum + r[i];
        if(cur > b) flag1 = false;
        B = cur;
        sum += cur;
      }
      
      if(!flag1 || B > b) continue;
      
      for(int i=1;i<=n;++i)
      {
        ll bes = bs(1, m, i);
        if(i == n)
        {
          B -= r[i];
          B += bes;
        }else
        {
          B -= r[i] << (n - i - 1);
          B += bes << (n - i - 1);
        }
        r[i] = bes;
      }
        
      sum = a;
      vector<ll> vans{a};
      for(int i=1;i<=n;++i)
      {
        ll cur = sum + r[i];
        vans.push_back(cur);
        sum += cur;
      }
      
      if(vans.back() == b)
      {
        flag = true;
        printf("%d", (int)vans.size());
        for(ll x: vans) printf(" %lld", x);
        printf("\n");
        break;
      }
    }
    
    if(!flag) printf("-1\n");
  }
    
  return 0;
}
