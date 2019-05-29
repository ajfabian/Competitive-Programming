#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

const int N = 17;
const int M = 1e4+7;

int a[N][M];
int w[2][N][N];
int dp[1 << N][N][N];

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  int n, m;
  cin >> n >> m;
  
  for(int i = 0;i < n;++i)
    for(int j=1;j<=m;++j)
      cin >> a[i][j];
      
  if(n == 1)
  {
    int ans = 2e9+1;
    for(int i=1;i<m;++i)
      ans = min(ans, abs(a[0][i] - a[0][i+1]));
    cout << ans << endl;
    return 0;
  }
  
  for(int i=0;i<n;++i)
    for(int j=0;j<n;++j)
    {
      w[0][i][j] = 2e9+1;
      for(int k=1;k<=m;++k)
        w[0][i][j] = min(w[0][i][j], abs(a[i][k] - a[j][k]));
      w[1][i][j] = 2e9+1;
      for(int k=1;k<m;++k)
        w[1][i][j] = min(w[1][i][j], abs(a[i][k] - a[j][k+1]));
      
      if(i != j)
        dp[(1 << i) | (1 << j)][i][j] = dp[(1 << i) | (1 << j)][j][i] = w[0][i][j];
    }
  
  int nn = 1 << n;
  for(int s=0;s<nn;++s)
  {
    for(int i=0;i<n;++i) if(s>>i&1)
      for(int j=0;j<n;++j) if(s>>j&1)
        for(int p=0;p<n;++p) if(~s>>p&1)
        {
          dp[s | 1 << p][i][p] = max({dp[s | 1 << p][i][p], min(dp[s][i][j], w[0][j][p])});
          dp[s | 1 << p][p][j] = max({dp[s | 1 << p][p][j], min(dp[s][i][j], w[0][p][i])});
        }
  }
  
  
  
  int ans = 0;
  for(int i=0;i<n;++i)
    for(int j=0;j<n;++j)
    {
      
      ans = max(ans, min(dp[nn-1][i][j], w[1][j][i]));
    }
  
  
  cout << ans << endl;
  
  return 0;
}
