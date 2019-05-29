#include <bits/stdc++.h>
using namespace std;

#define fr first
#define sc second
#define mp make_pair

const int N = 555;

int mat[N][N];

int dp[N][N][2], fon[N], foff[N];
pair<int, int> pp[N][N][2];

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  int n, m; cin >> n >> m;
  for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j)
      cin >> mat[i][j];
  
  if(n == 1)
  {
    for(int i=1;i<=m;++i) if(mat[1][i] > 0)
      return !(cout << "TAK\n" << i << endl);
    return !(cout << "NIE\n");
  }
  
  for(int k=0;k<=10;++k)
  {
    memset(pp, 0, sizeof pp);
    memset(fon, 0, sizeof fon);
    memset(foff, 0, sizeof foff);
    
    for(int j=1;j<=m;++j)
    {
      if(mat[1][j] >> k & 1) fon[1] = j;
      else foff[1] = j;
    }
    
    for(int i=2;i<=n;++i)
      for(int j=1;j<=m;++j)
      {
        int b = mat[i][j] >> k & 1;
        
        if(fon[i-1])
        {
          if(b) foff[i] = j, pp[i][j][0] = mp(fon[i-1], 1);
          else fon[i] = j, pp[i][j][1] = mp(fon[i-1], 1);
        }
        if(foff[i-1])
        {
          if(b) fon[i] = j, pp[i][j][1] = mp(foff[i-1], 0);
          else foff[i] = j, pp[i][j][0] = mp(foff[i-1], 0);
        }
      }
    
    if(fon[n])
    {
      cout << "TAK\n";
      vector<int> ans;
      pair<int, int> c = mp(fon[n], 1);
      int i = n;
      while(c.fr)
      {
        //~ cerr << c.fr << ' ' << c.sc << endl;
        ans.push_back(c.fr);
        c = pp[i--][c.fr][c.sc];
      }
      reverse(ans.begin(), ans.end());
      for(int j: ans) cout << j << ' ';
      cout << endl;
      return 0;
    }
  }
  
  cout << "NIE\n";
  
  return 0;
}
