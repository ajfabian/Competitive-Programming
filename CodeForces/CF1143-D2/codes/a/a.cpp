#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  scanf("%d", &n);
  
  int tot[2];
  tot[0] = tot[1] = 0;
  vector<int> a(n);
  for(int& i: a)
  {
    scanf("%d", &i);
    ++tot[i];
  }
  
  int p[2], cnt = 0;
  p[0] = p[1] = 0;
  for(int i: a)
  {
    ++cnt;
    ++p[i];
    if(p[i] == tot[i])
      return !(cout << cnt << endl);
  }
  
  return 0;
}
