#include <bits/stdc++.h>
using namespace std;

int dist(int a, int b)
{
  return min((b + 26 - a)%26, (a + 26- b)%26);
}

int solve(string& s, int i)
{
  vector<int> targ{'A' - 'A', 'C' - 'A', 'T' - 'A', 'G' - 'A'};
  int res = 0;
  for(int j=0;j<4;++j)
    res += dist(s[i+j]-'A', targ[j]);
  return res;
}

int main()
{
  int n;
  cin >> n;
  string s;
  cin >> s;
  
  int ans = 1e9;
  for(int i=0;i<=n-4;++i)ans = min(ans, solve(s, i));
  
  cout << ans << endl;
  
  return 0;
}
