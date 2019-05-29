#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = 1e6+7;

int H[N], L[N];
bool pok[N], sok[N];

bool ok(int l, int r)
{
  return pok[l-1] && sok[r+1] && H[l-1] <= L[r+1];
}

int bs(int lo, int hi, int l)
{
  if(hi - lo <= 1)
  {
    if(ok(l, lo)) return lo;
    if(ok(l, ++lo)) return lo;
    return ++lo;
  }
  
  int m = lo + hi  >> 1;
  if(ok(l, m)) return bs(lo, m, l);
  return bs(m, hi, l);
}

int v[N], used[N];

int main()
{
  int n, x;
  scanf("%d%d", &n, &x);
  
  for(int i=1;i<=n;++i)
  {
    scanf("%d", &v[i]);
    if(!L[v[i]]) L[v[i]] = i;
    H[v[i]] = i;
    used[v[i]] = 1;
  }
  
  L[x+1] = 1e9;
  for(int i=1;i<=x;++i) if(!H[i]) H[i] = H[i-1];
  for(int i=x;i;--i) if(!L[i]) L[i] = L[i+1];
  
  pok[0] = pok[1] = 1;
  for(int i=2;i<=x;++i)
  {
    if(!used[i])
      pok[i] = pok[i-1];
    else pok[i] = pok[i-1] && H[i-1] <= L[i];
  }
  
  sok[x+1] = sok[x] = 1;
  for(int i=x-1;i;--i)
  {
    if(!used[i])
      sok[i] = sok[i+1];
    else sok[i] = sok[i+1] && H[i] <= L[i+1];
  }
  
  ll ans = 0;
  
  for(int l = 1;l<=x;++l)
  {
    if(!pok[l-1]) break;
    int r = bs(l, x, l);
    ans += x - r + 1;
    //~ cerr << l << ' ' << r << endl;
  }
  
  cout << ans << endl;
  
  //~ ll tans = 0;
  
  //~ for(int i=1;i<=x;++i)
    //~ for(int j=i;j<=x;++j)
    //~ {
      //~ vector<int> ps1, ps2;
      //~ for(int k=1;k<=n;++k)
        //~ if(v[k] > j || v[k] < i)
          //~ ps1.push_back(v[k]),
          //~ ps2.push_back(v[k]);
      //~ sort(ps2.begin(), ps2.end());
      //~ tans += ps1 == ps2;
    //~ }
  
  //~ cerr << tans << endl;
  
  //~ assert(ans == tans);
  
  return 0;
}
