#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for(int& i: a) scanf("%d", &i);
  
  sort(a.begin(), a.end());
  a.resize(unique(a.begin(), a.end()) - a.begin());
  
  int ans = 0;
  for(int i: a)
  {
    if(i == 1) continue;
    int j=0;
    while(i*j <= a.back())
    {
      auto it = lower_bound(a.begin(), a.end(), i * (j+1));
      if(it!=a.begin())
      {
        it--;
        ans = max(ans, *it % i);
      }
      ++j;
    }
  }
  cout << ans << endl;
  
  return 0;
}
