#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, k;
  
  cin >> n >> k;
  
  vector<int> a(n);
  for(int& i: a) cin >> i;
  
  int ans = 0;
  
  for(int b=0;b<n;++b)
  {
    int e = 0;
    int s = 0;
    
    for(int i=0;i<n;++i)
    {
      if(abs(i - b) % k)
      {
        if(a[i] == -1) ++s;
        if(a[i] == 1) ++e;
      }
    }
    
    ans = max(ans, abs(e - s));
    //~ cerr << b << ' ' << e << ' ' << s << ' '  << abs(e - s) << endl;
  }
  
  cout << ans << endl;
  
  
  return 0;
}
