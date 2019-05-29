#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  cin >> n;
  
  vector<int> a(n);
  for(int& i: a)
    cin >> i;
  
  int ansc = 1e9, tt=-1;
  
  for(int t = 1; t <= 1000;++t)
  {
    int cost = 0;
    for(int i: a)
      if(i > t) cost += i - (t+1);
      else if(i < t) cost += t-1 - i;
    
    if(ansc > cost)
    {
      ansc = cost;
      tt = t;
    }
  }
  
  cout << tt << ' ' << ansc << endl;
  return 0;
}
