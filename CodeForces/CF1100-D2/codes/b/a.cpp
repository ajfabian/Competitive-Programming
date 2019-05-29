#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  int n, m;
  
  cin >> n >> m;
  
  set<int> s;
  vector<int> ss(n+1, 0);
  for(int i=1;i<=m;++i)
  {
    int x;
    cin >> x;
    s.insert(x);
    ++ss[x];
    
    if(s.size() == n)
    {
      cout << 1;
      vector<int> del;
      for(int j: s)
      {
        --ss[j];
        if(ss[j] == 0) del.push_back(j);
      }
      for(int j: del)
        s.erase(j);
    }else cout << 0;
  }
  
  cout << endl;
  
  return 0;
}
