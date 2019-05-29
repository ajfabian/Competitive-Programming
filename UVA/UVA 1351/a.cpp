/**
 * Idea: use dp
 * 
 * Let dp(i, j) be the shortest string we can get (the answer to the problem).
 * 
 * Then we can try two things:
 *  1. Compress current string with a pattern of length k (k < j-i+1),
 *     and consider dp(i, i + k - 1) + 2 + ceil(log10(repeticiones)).
 *  2. Find a position k (k < j) and consider dp(i, k) + dp(k+1, j).
 * */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define BASE 31
const ll mod = 1e9+7;

ll pot[222];
int val(char x)
{
  return x - 'a' + 1;
}

struct HashedString
{
  int n;
  string s;
  vector<ll> hash;
  HashedString(string& s)
    : n(s.size()), s(s), hash(s.size())
  {
    hash[0] = val(s[0]);
    for(int i=1;i<n;++i)
      hash[i] = ( hash[i-1] * BASE % mod + val(s[i]) ) % mod;
  }
  
  ll getHash(int i, int j)
  {
    if(i == 0) return hash[j];
    return (hash[j] + mod - hash[i-1] * pot[j - i + 1] % mod) % mod;
  }
  
  bool ok(int i, int j, int k)
  {
    if((j - i + 1) % k || k >= j - i + 1) return false;
    
    ll H = getHash(i, i + k - 1);
    for(int x = i; x <= j; x += k)
    {
      ll H1 = getHash(x, x + k - 1);
      if(H != H1) return false;
    }
    return true;
  }
};

int dp[222][222];

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  pot[0] = 1;
  for(int i=1;i<222;++i) pot[i] = pot[i-1] * BASE % mod;
  
  int tt;
  cin >> tt;
  while(tt--)
  {
    string s;
    cin >> s;
    int n = s.size();
    HashedString hs(s);
    
    for(int j=0;j<n;++j)
    {
      for(int i=j;~i;--i)
      {
        dp[i][j] = j-i+1;
        for(int k=1,kk=j-i+1;k<=kk;++k)
        {
          if(hs.ok(i, j, k))
          {
            int tot = kk / k;
            dp[i][j] = min(dp[i][j], dp[i][i+k-1] + 2 + (int) to_string(tot).size());
          }
        }
        
        for(int k=i;k<j;++k)
          dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);
      }
    }
    
    cout << dp[0][n-1] << '\n';
  }
  
  return 0;
}
