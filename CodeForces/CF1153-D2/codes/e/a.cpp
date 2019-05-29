#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int qry(int x1, int y1, int x2, int y2)
{
  cout << "? " << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
  int ret;
  cin >> ret;
  if(ret == -1) exit(0);
  return ret;
}

int bsc(int r, int lo, int hi)
{
  if(hi - lo <= 1)
  {
    if(qry(r, 1, r, lo) & 1) return lo;
    return lo+1;
  }
  int m = lo + hi >> 1;
  if(qry(r, 1, r, m) & 1) return bsc(r, lo, m);
  return bsc(r, m+1, hi);
}

int bsr(int c, int lo, int hi)
{
  if(hi - lo <= 1)
  {
    if(qry(1, c, lo, c) & 1) return lo;
    return lo+1;
  }
  int m = lo + hi >> 1;
  if(qry(1, c, m, c) & 1) return bsr(c, lo, m);
  return bsr(c, m+1, hi);
}

int main()
{
  int n;
  cin >> n;
  
  int sum = 0;
  vector<int> rw(n+1);
  for(int i=1;i<n;++i)
  {
    rw[i] = qry(i, 1, i, n) % 2;
    sum = (sum + rw[i]) % 2;
  }
  rw[n] = sum;
  
  vector<int> ro;
  for(int i=1;i<=n;++i) if(rw[i] == 1) ro.push_back(i);
  
  if(!ro.empty())
  {
    int c0, c1;
    c0 = bsc(ro[0], 1, n);
    c1 = bsc(ro[1], 1, n);
    cout << "! " << ro[0] << ' ' << c0 << ' ' << ro[1] << ' ' << c1 << endl;
    return 0;
  }
  
  sum = 0;
  for(int i=1;i<n;++i)
  {
    rw[i] = qry(1, i, n, i) % 2;
    sum += rw[i];
  }
  rw[n] = sum;
  
  for(int i=1;i<=n;++i) if(rw[i] == 1) ro.push_back(i);
  
  int c0 = bsr(ro[0], 1, n);
  cout << "! " << c0 << ' ' << ro[0] << ' ' << c0 << ' ' << ro[1] << endl;
  
  return 0;
}
