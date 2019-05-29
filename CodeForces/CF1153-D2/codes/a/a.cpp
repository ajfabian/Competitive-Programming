#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, t, fs = 1e9, id=-1;
  scanf("%d%d", &n, &t);
  for(int i=1;i<=n;++i)
  {
    int s, d;
    scanf("%d%d", &s, &d);
    for(;s < t; s+=d);
    if(fs > s) fs = s, id = i;
  }
  cout << id << endl;
  return 0;
}
