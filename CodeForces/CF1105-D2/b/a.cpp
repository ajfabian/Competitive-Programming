#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, k;
  string s;
  cin >> n >> k >> s;
  
  vector<int> ans(256);
  
  char last = -1;int cum = 0;
  for(int i=0;i<n;++i)
  {
    char c = s[i];
    if(last == c)
    {
      ++cum;
    }else
    {
      if(~last)
        ans[last] += cum / k;
      cum = 1;
      last = c;
    }
    
  }
  ans[last] += cum / k;
  cout << * max_element(ans.begin(),  ans.end()) << endl;
  
  return 0;
}
