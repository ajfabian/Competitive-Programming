/*
 * CF1101-D12-D
 * Idea: centroid decomposition
 * SC: 2
 * TT: 10
 * CT: 45
 * lev: 5.5
 * Category: centroid decomposition, number theory
 * Interesting.
 * */

#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const int N = 2e5+7;

vector<int> g[N];
void eadd(int u, int v)
{
  g[u].push_back(v);
  g[v].push_back(u);
}

int lpf[N];
vector<int> primes;
void sieve(int n)
{
  for(int i=2;i<=n;++i)
  {
    if(!lpf[i])
    {
      lpf[i] = i;
      primes.push_back(i);
    }
    
    for(int p: primes)
    {
      if(1ll * i * p > 1ll * n) break;
      lpf[i * p] = p;
      if(i % p == 0)
      {
        break;
      }
    }
  }
}

int compact(int x)
{
  if(x == 1) return x;
  int res = 1;
  while(x > 1)
  {
    int p = lpf[x];
    //~ cerr <<x << ' ' << p << endl;
    res *= p;
    while(lpf[x] == p && x > 1) x/=p;
  }
  return res;
}


int ans = 1;

int sz[N],mc[N],p[N],q[N];
bool mk[N];
int gc(int st)
{
  int b=0,e=0;
  q[e++]=st, mc[st]=0, p[st]=-1, sz[st]=1;
  while(b<e)
  {
    int u=q[b++];
    for(auto v:  g[u])
    {
      if(p[u]==v||mk[v])continue;
      p[v]=u;
      mc[v]=0;
      sz[v]=1;
      q[e++]=v;
    }
  }
  for(int i=e-1;~i;--i)
  {
    int u=q[i];
    int bc=max(e-sz[u],mc[u]);
    if(2*bc<=e)
    {
      st=u;
      break;
    }
    sz[p[u]]+=sz[u];
    mc[p[u]]=max(mc[p[u]], sz[u]);
  }
  return st;
}

vector<int> used;
int lpath[N];
int val[N];

void updAns(int x, int d)
{
  x = compact(x);
  if(x == 1) return;
  
  while(x > 1)
  {
    int p = lpf[x];
    ans = max(ans, lpath[p] + d);
    x /= p;
  }
}

void updPaths(int x, int d)
{
  x = compact(x);
  if(x == 1) return;
  
  while(x > 1)
  {
    int p = lpf[x];
    if(lpath[p] == 0) used.push_back(p);
    lpath[p] = max(lpath[p], d);
    x /= p;
  }
}

int gcd(int x, int y)
{
  if(x == 1 || y == 1) return 1;
  int res = 1;
  while(lpf[x])
  {
    int p = lpf[x];
    if(y % p == 0) res *= p;
    x /= p;
  }
  return res;
}

void calc(int u, int p, int A, int dist = 1)
{
  A = gcd(A, val[u]);
  if(A == 1) return;
  updAns(A, dist);
  for(int v: g[u])
  {
    if(v == p || mk[v]) continue;
    
    calc(v, u, A, dist + 1);
  }
}

void upd(int u, int p, int A,int dist=2)
{
  A = gcd(A, val[u]);
  if(A == 1) return ;
  
  updPaths(A, dist);
  for(int v: g[u])
  {
    if(v == p || mk[v]) continue;
    
    upd(v, u, A, dist + 1);
  }
}

void solve(int r)
{
  if(val[r] == 1) return;
  updPaths(val[r], 1);
  for(int v: g[r])
  {
    if(mk[v]) continue;
    calc(v, r, val[r]);
    upd(v, r, val[r]);
  }
  
  for(int i: used)
    lpath[i] = 0;
  used.clear();
}

void dfs(int u=1)
{
  u = gc(u);
  mk[u] = true;
  
  solve(u);
  
  for(int v: g[u])
  {
    if(!mk[v]) dfs(v);
  }
}



int main()
{
  //~ ios_base::sync_with_stdio(false);
  //~ cin.tie(0),  cout.tie(0);
  
  sieve(N);
  
  int n;
  scanf("%d", &n);
  
  int mx = 0;
  for(int i=1;i<=n;++i)
  {
    scanf("%d", val + i);
    val[i] = compact(val[i]);
    mx = max(mx, val[i]);
    //~ cerr << val[i] << ' ';
  }
  
  if(mx == 1) return !(cout<<"0\n");
  //~ cerr << endl;
  //~ return 0;
  for(int i=1;i<n;++i)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    eadd(u, v);
  }
  
  dfs();
  
  cout << ans << endl;
  
  
  return 0;
}
