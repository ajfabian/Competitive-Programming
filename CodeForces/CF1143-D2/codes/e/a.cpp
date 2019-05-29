#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 7;
#define ifor(i,st,ed) for(int i=(st);i<=(ed);++i)

int m, q, per[N], a[N], last[N], pre[N], jump[N][19], b[N];

int t[N][19],Log2[N];
void brmq()
{
  ifor(i,1,m)t[i][0]=b[i];
  int x = -1;
  ifor(i,1,N-1)
  {
    if(!(i&(i-1)))++x;
    Log2[i]=x;
  }
  for(int k=1;(1<<k)<=m;++k)
    for(int i=1;i+(1<<(k-1))<=m;++i)
      t[i][k] = max(t[i][k-1],t[i+(1<<(k-1))][k-1]);
}
int qry(int i,int j)
{
  int d=Log2[j-i+1];
  return max(t[i][d],t[j-(1<<d)+1][d]);
}

int main()
{
  int n;
  scanf("%d%d%d", &n, &m, &q);
  
  for(int i=1;i<=n;++i) scanf("%d", per + i);
  for(int i=2;i<=n;++i) pre[per[i]] = per[i-1];
  pre[per[1]] = per[n];
  
  for(int i=1;i<=m;++i)
  {
    scanf("%d", a + i);
    int x = last[pre[a[i]]];
    jump[i][0] = x;
    last[a[i]] = i;
  }
  
  for(int i=1;i<19;++i)
    for(int j=1;j<=m;++j)
      jump[j][i] = jump[jump[j][i-1]][i-1];
  
  
  for(int i=1;i<=m;++i)
  {
    int cur = i;
    for(int j=0;j<19 && cur;++j)
    {
      if((n-1) >> j & 1)
        cur = jump[cur][j];
    }
    
    b[i] = cur;
  }
  
  brmq();
  
  vector<int> ans;
  while(q--)
  {
    int l, r;
    scanf("%d%d", &l, &r);
    int mx = qry(l, r);
    if(l <= mx && mx <= r) ans.push_back(1);
    else ans.push_back(0);
  }
  for(int i: ans) printf("%d", i);
  printf("\n");
  
  return 0;
}
