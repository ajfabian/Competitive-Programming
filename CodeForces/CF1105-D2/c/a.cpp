#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll mod = 1e9+7;

const int N = 2e5+7;

ll dp[N][3];

int calc(int l, int r, int k)
{
  int p = min(3, r);
  int ext = 0;
  while(l <= p)
  {
    if(l%3 == k) ++ext;
    ++l;
  }
  
  cerr << "l " << l << endl; 
  if(l <= 3 && l > r) return ext;
  int b = (r-k)/3;
  int a = (l-k + 3 - 1) / 3;
  cerr << a << ' ' << b << endl;
  
  return b - a + 1 + ext;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  int n, l, r;
  cin >> n >> l >> r;
  vector<ll>tot(3, 0);
  tot[0] = calc(l, r, 0);
  tot[1] = calc(l, r, 1);
  tot[2] = calc(l, r, 2);
  for(ll i: tot)
    cerr << i << ' ';
  cerr << endl;
  
  dp[0][0] = 1;
  for(int i=0;i<n;++i)
  {
    for(int r=0;r<3;++r)
    {
      for(int k=0;k<3;++k)
        dp[i+1][(r+k)%3] = (dp[i+1][(r+k)%3] + dp[i][r] * tot[k] % mod) % mod;
    }
  }
  
  cout << dp[n][0] << endl;
  
  return 0;
}
