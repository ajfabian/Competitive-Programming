#include <bits/stdc++.h>
using namespace std;

vector<int> failS, failT;

void buildFail(string& str, vector<int>& fail)
{
  int n = str.size();
  fail.resize(n);
  fail[0] = -1;
  for(int i=1,j=-1;i<n;fail[i] = ++j, ++i)
    while(j > -1 && str[j+1] != str[i])
      j = fail[j];
}

void printV(vector<int>& v)
{
  for(int i: v) cout << i << ' ';
  cout << endl;
}

int accS, accT, nxt[2][57][256];
string c, s, t;

int advance(int j, char c, string& p, vector<int>& fail)
{
  while(j > -1 && p[j + 1] != c) j = fail[j];
  return ++j;
}

const int inf = 1e9;

int dp[1007][57][57];
bool mk[1007][57][57];

int f(int i, int k1, int k2)
{
  if(mk[i][k1][k2]) return dp[i][k1][k2];
  if(i == (int)c.size()) return mk[i][k1][k2] = 1, dp[i][k1][k2] = 0;
  
  int res = -inf;

  if(c[i] == '*')
  {
    for(char l = 'a'; l <= 'z'; ++ l)
    {
      //~ int kk1 = advance(k1, l, s, failS);
      //~ int kk2 = advance(k2, l, t, failT);
      int kk1 = nxt[0][k1][l];
      int kk2 = nxt[1][k2][l];
      
      int extra = 0;
      if(kk1 == accS) ++extra, kk1 = failS[kk1];
      if(kk2 == accT) --extra, kk2 = failT[kk2];
      
      res = max(res, f(i + 1, kk1, kk2) + extra);      
    }
  }else
  {
    //~ int kk1 = advance(k1, c[i], s, failS);
    //~ int kk2 = advance(k2, c[i], t, failT);
    int kk1 = nxt[0][k1][c[i]];
    int kk2 = nxt[1][k2][c[i]];
      
    int extra = 0;
    if(kk1 == accS) ++extra, kk1 = failS[kk1];
    if(kk2 == accT) --extra, kk2 = failT[kk2];
    
    res = max(res, f(i + 1, kk1, kk2) + extra);
  }
  
  return mk[i][k1][k2] = 1, dp[i][k1][k2] = res;
}

int main()
{
  cin >> c >> s >> t;
  
  c = "$" + c;
  s = "$" + s; accS = s.size()-1;
  t = "$" + t; accT = t.size()-1;
  
  buildFail(s, failS);
  buildFail(t, failT);
  
  //~ printV(failS);
  //~ printV(failT);
  
  for(int i=0;i<=accS;++i)
    for(char j='a';j<='z';++j)
      nxt[0][i][j] = advance(i, j, s, failS);
  
  for(int i=0;i<=accT;++i)
    for(char j='a';j<='z';++j)
      nxt[1][i][j] = advance(i, j, t, failT);
  
  memset(mk, 0, sizeof mk);
  cout << f(1, 0, 0) << endl;
  
  return 0;
}
