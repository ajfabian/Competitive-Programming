#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, m, h;
  scanf("%d%d%d", &n, &m, &h);
  vector<int> a(m), b(n);
  for(int& i: a) scanf("%d", &i);
  for(int& i: b) scanf("%d", &i);
  
  for(int i=0;i<n;++i)
    for(int j=0;j<m;++j)
    {
      int x;
      scanf("%d", &x);
      if(x == 1)
        cout << min(a[j], b[i]) << " \n"[j == m-1];
      else cout << 0 << " \n"[j == m-1];
    }
  
  return 0;
}
