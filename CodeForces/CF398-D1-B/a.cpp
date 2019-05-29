/**
 * Idea: use dp
 * 
 * It's easy to notice that the actual cell that it's being painted doesn't
 * matter, just if it's row(column) is in the set of already painted cells
 * so let r and c be the number of rows and columns with at least one painted
 * cell then our state would be (r, c).
 * 
 * So we define a dp E(r, c) as the expected number of minutes before all
 * rows and colmumns has something painted.
 * 
 * So the transitions are:
 *  (r, c) -> (r+1, c)    p-bility = (n - r) * c / n ** 2
 *  (r, c) -> (r, c+1)    p-bility = r * (n - c) / n ** 2
 *  (r, c) -> (r+1, c+1)  p-bility = (n - r) * (n - c) / n ** 2
 *  (r, c) -> (r, c)      p-bility = r * c / n ** 2
 *  
 * After a little bit of hand work with the formula we get:
 * (here nn = n ** 2)
 * E(r, c) =
 *   (
 *     r * c / nn + 
 *     (n - r) * c / nn * (E(r+1, c) + 1) + 
 *     r * (n - c) / nn * (E(r, c+1) + 1) + 
 *     (n - r) * (n - c) / nn * (E(r+1, c+1) + 1)
 *   ) / (1.0 - r * c / nn);
 **/


#include <bits/stdc++.h>
using namespace std;

using ld = long double;

int n, m;
ld nn;
ld dp[2222][2222];
bool mk[2222][2222];

ld f(int r, int c)
{
  if(mk[r][c]) return dp[r][c];
  if(r == n && c == n) return mk[r][c] = 1, dp[r][c] = 0;
  
  dp[r][c] =
    (
      r * c / nn + 
      (r<n ? (n - r) * c / nn * (f(r+1, c) + 1) : 0) + 
      (c<n ? r * (n - c) / nn * (f(r, c+1) + 1) : 0) + 
      (r<n&&c<n ? (n - r) * (n - c) / nn * (f(r+1, c+1) + 1) : 0)
    ) / (1.0 - r * c / nn);
  
  mk[r][c] = 1;
  
  return dp[r][c];
}

int main()
{
  cin >> n >> m;
  nn = ((ld) n) * n;
  
  vector<int> r(n+1), c(n+1);
  for(int i=1;i<=m;++i)
  {
    int x, y;
    cin >> x >> y;
    r[x] = 1;
    c[y] = 1;
  }
  
  int rr = 0, cc = 0;
  for(int i=1;i<=n;++i)
  {
    if(r[i]) ++rr;
    if(c[i]) ++cc;
  }
  
  cout << fixed << setprecision(10) << f(rr, cc) << endl;
  
  return 0;
}
