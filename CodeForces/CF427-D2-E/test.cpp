#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, m;
  cin >> n >> m;
  vector<int> x(n);
  for(int& i: x)
    cin >> i;
  
  int last =1e9;
  sort(x.begin(), x.end());
  for(int p = x.front(); p <= x.back();++p)
  {
    //~ cerr << p << endl;
    int pr = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i: x)
      pq.emplace(i);
    
    while(!pq.empty() && pq.top() < p)
    {
      int cnt = 0, cost = p - pq.top();
      while(!pq.empty() && pq.top() < p && cnt < m)
      {
        pq.pop();
        ++cnt;
      }
      pr += cost;
    }
    //~ cerr << "control1\n";
    
    while(!pq.empty() && pq.top() == p)
      pq.pop();
      
    //~ cerr << "control3\n";
    
    priority_queue<int> pq1;
    while(!pq.empty())
    {
      pq1.emplace(pq.top());
      pq.pop();
    }
    
    //~ cerr << "control4 " << pq1.size() << endl;
    
    while(!pq1.empty())
    {
      int cnt = 0, cost = pq1.top() - p;
      while(!pq1.empty() && pq1.top() > p && cnt < m)
      {
        pq1.pop();
        ++cnt;
      }
      pr += cost;
    }
    
    //~ cerr << "control2\n";
    
    cout << p << ' '<< 2 * pr << ' ';
    if(pr > last) cout << ">\n";
    else if(pr == last) cout << "=\n";
    else cout << "<\n";
    
    last = pr;
  }
  
  return 0;
}
