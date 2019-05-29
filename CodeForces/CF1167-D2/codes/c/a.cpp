#include <bits/stdc++.h>
using namespace std;

const int N = 5e5+7;

int rt[N], rk[N];

int fs(int x)
{
  if(x != rt[x]) return rt[x] = fs(rt[x]);
  return x;
}

void js(int x, int y)
{
  x = fs(x);
  y = fs(y);
  if(x == y) return;
  if(rk[x] < rk[y]) swap(x ,y);
  rk[x] += rk[y];
  rt[y] = x;
}


int main()
{
  for(int i=1;i<N;++i) rt[i] = i, rk[i] = 1;
  
  int n, m;
  scanf("%d %d", &n, &m);
  for(int i=1;i<=m;++i)
  {
    int k;
    scanf("%d", &k);
    vector<int> group;
    while(k--)
    {
      int x;
      scanf("%d", &x);
      group.push_back(x);
    }
    
    if(group.empty()) continue;
    int my = fs(group.front());
    for(int i=1;i<(int)group.size();++i)
      js(my, group[i]);
  }
  
  for(int i=1;i<=n;++i)
  {
    printf("%d ", rk[fs(i)]);
  }
  printf("\n");
  
  
  return 0;
}
